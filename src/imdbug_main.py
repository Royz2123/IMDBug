from __future__ import absolute_import, division, print_function

import logging
from typing import List, Tuple, Dict, Union

import numpy as np
import torch
from captum.attr import LayerIntegratedGradients, DeepLift, DeepLiftShap, GradientShap, Saliency
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score
from torch import Tensor
from torch.utils.data import DataLoader, SequentialSampler
from tqdm import tqdm

from linevul_main import clean_special_token_values, get_word_att_scores, create_ref_input_ids, summarize_attributions, \
    clean_word_attr_scores, write_raw_preds_csv, TextDataset

logger = logging.getLogger(__name__)


def imdbug_test(args, model, tokenizer, test_dataset: TextDataset, best_threshold=0.5):
    # build dataloader
    test_sampler = SequentialSampler(test_dataset)
    test_dataloader = DataLoader(test_dataset, sampler=test_sampler, batch_size=args.eval_batch_size, num_workers=0)

    # Create model
    if args.n_gpu > 1:
        model = torch.nn.DataParallel(model)

        # Eval!
    logger.info("***** Running Test *****")
    logger.info("  Num examples = %d", len(test_dataset))
    logger.info("  Batch size = %d", args.eval_batch_size)
    eval_loss = 0.0
    nb_eval_steps = 0
    model.eval()
    logits = []
    y_trues = []
    for batch in test_dataloader:
        (inputs_ids, labels) = [x.to(args.device) for x in batch]
        with torch.no_grad():
            lm_loss, logit = model(input_ids=inputs_ids, labels=labels)
            eval_loss += lm_loss.mean().item()
            logits.append(logit.cpu().numpy())
            y_trues.append(labels.cpu().numpy())
        nb_eval_steps += 1
    # calculate scores
    logits = np.concatenate(logits, 0)
    y_trues = np.concatenate(y_trues, 0)
    y_probs = logits[:, 1]
    y_preds = logits[:, 1] > best_threshold
    acc = accuracy_score(y_trues, y_preds)
    recall = recall_score(y_trues, y_preds)
    precision = precision_score(y_trues, y_preds)
    f1 = f1_score(y_trues, y_preds)
    result = {
        "test_accuracy": float(acc),
        "test_recall": float(recall),
        "test_precision": float(precision),
        "test_f1": float(f1),
        "test_threshold": best_threshold,
    }

    logger.info("***** Test results *****")
    for key in sorted(result.keys()):
        logger.info("  %s = %s", key, str(round(result[key], 4)))

    # Return line scores
    logits = [l[1] for l in logits]

    # write raw predictions if needed
    if args.write_raw_preds:
        write_raw_preds_csv(args, y_preds)

    # define reasoning method
    if args.reasoning_method == "all":
        all_reasoning_method = ["attention", "lig", "saliency", "deeplift", "deeplift_shap", "gradient_shap"]
        all_reasoning_method = ["attention", "saliency", "deeplift", "deeplift_shap", "gradient_shap"]
        all_reasoning_method = ["saliency"]
    else:
        all_reasoning_method = [args.reasoning_method]

    all_line_scores = list()
    if args.do_sorting_by_line_scores:
        for reasoning_method in all_reasoning_method:
            dataloader = DataLoader(test_dataset, sampler=test_sampler, batch_size=1, num_workers=0)
            progress_bar = tqdm(dataloader, total=len(dataloader))
            for idx, curr_function in enumerate(progress_bar):
                if logits[idx] > best_threshold:
                    curr_lines, curr_line_scores = get_line_scores(
                        tokenizer,
                        model,
                        curr_function,
                        args,
                        reasoning_method
                    )
                else:
                    curr_line_scores = list()
                all_line_scores.append(curr_line_scores)
    return y_preds, y_probs, all_line_scores


def compute_line_score_from_att(word_att_scores: list) -> Tuple[List[str], List[Union[Tensor, int]]]:
    # word_att_scores -> [[token, att_value], [token, att_value], ...]
    separator = ["Ċ", " Ċ"]
    double_seps = ["ĊĊ", " ĊĊ"]
    # to return
    all_lines_score = []
    all_lines = []
    score_sum = 0
    line_idx = 0
    line = ""
    for i in range(len(word_att_scores)):
        curr_word, curr_score = word_att_scores[i]

        # Summarize if meet line separator or finish code
        if (curr_word in separator + double_seps) or (i == (len(word_att_scores) - 1)):
            score_sum += curr_score
            all_lines_score.append(score_sum)
            all_lines.append(line)
            if curr_word in double_seps:
                all_lines_score.append(0)
                all_lines.append('')
            line = ""
            score_sum = 0
            line_idx += 1

        # Otherwise accumulate score
        else:
            line += curr_word
            score_sum += curr_score
    return all_lines, all_lines_score


def get_line_scores(tokenizer, model, mini_batch, args, reasoning_method: str) -> Dict[str, float]:
    # function for captum LIG.
    def predict(input_ids):
        return model(input_ids=input_ids)[0]

    def lig_forward(input_ids):
        logits = model(input_ids=input_ids)[0]
        y_pred = 1  # for positive attribution, y_pred = 0 for negative attribution
        pred_prob = logits[y_pred].unsqueeze(-1)
        return pred_prob

    (input_ids, labels) = mini_batch
    ids = input_ids[0].detach().tolist()
    all_tokens = tokenizer.convert_ids_to_tokens(ids)
    all_tokens = [token.replace("Ġ", "") for token in all_tokens]
    # all_tokens = [token.replace("ĉ", "Ċ") for token in all_tokens]

    # Find per line scores
    if reasoning_method == "attention":
        # attentions: a tuple with of one Tensor with 4D shape (batch_size, num_heads, sequence_length, sequence_length)
        input_ids = input_ids.to(args.device)
        prob, attentions = model(input_ids=input_ids, output_attentions=True)

        # Take from tuple then take out mini-batch attention values
        attentions = attentions[0][0]
        attention = None
        for i in range(len(attentions)):
            layer_attention = attentions[i]
            layer_attention = sum(layer_attention)
            if attention is None:
                attention = layer_attention
            else:
                attention += layer_attention

        # clean att score for <s> and </s>
        attention = clean_special_token_values(attention, padding=True)
        word_att_scores = get_word_att_scores(all_tokens=all_tokens, att_scores=attention)

    elif reasoning_method == "lig":
        ref_token_id, sep_token_id, cls_token_id = tokenizer.pad_token_id, tokenizer.sep_token_id, tokenizer.cls_token_id
        ref_input_ids = create_ref_input_ids(input_ids, ref_token_id, sep_token_id, cls_token_id)

        # send data to device
        input_ids = input_ids.to(args.device)
        ref_input_ids = ref_input_ids.to(args.device)
        lig = LayerIntegratedGradients(lig_forward, model.encoder.roberta.embeddings)
        attributions, delta = lig.attribute(inputs=input_ids,
                                            baselines=ref_input_ids,
                                            internal_batch_size=32,
                                            return_convergence_delta=True)
        score = predict(input_ids)
        attributions_sum = summarize_attributions(attributions)
        attr_scores = attributions_sum.tolist()
        # each token should have one score
        assert len(all_tokens) == len(attr_scores)

        # store tokens and attr scores together in a list of tuple [(token, attr_score)]
        word_att_scores = get_word_att_scores(all_tokens=all_tokens, att_scores=attr_scores)
        word_att_scores = clean_word_attr_scores(word_attr_scores=word_att_scores)

    elif reasoning_method in ["deeplift", "deeplift_shap", "gradient_shap", "saliency"]:
        # send data to device
        input_ids = input_ids.to(args.device)
        input_embed = model.encoder.roberta.embeddings(input_ids).to(args.device)
        if reasoning_method == "deeplift":
            # baselines = torch.randn(1, 512, 768, requires_grad=True).to(args.device)
            baselines = torch.zeros(1, 512, 768, requires_grad=True).to(args.device)
            reasoning_model = DeepLift(model)
        elif reasoning_method == "deeplift_shap":
            # baselines = torch.randn(16, 512, 768, requires_grad=True).to(args.device)
            baselines = torch.zeros(16, 512, 768, requires_grad=True).to(args.device)
            reasoning_model = DeepLiftShap(model)
        elif reasoning_method == "gradient_shap":
            # baselines = torch.randn(16, 512, 768, requires_grad=True).to(args.device)
            baselines = torch.zeros(16, 512, 768, requires_grad=True).to(args.device)
            reasoning_model = GradientShap(model)
        elif reasoning_method == "saliency":
            baselines = None
            reasoning_model = Saliency(model)
        else:
            raise Exception(f"Unrecognized reasoning method: {reasoning_method}")

        # attributions -> [1, 512, 768]
        if reasoning_method == "saliency":
            attributions = reasoning_model.attribute(input_embed, target=1)
        else:
            attributions = reasoning_model.attribute(input_embed, baselines=baselines, target=1)

        attributions_sum = summarize_attributions(attributions)
        attr_scores = attributions_sum.tolist()
        # each token should have one score
        assert len(all_tokens) == len(attr_scores)
        # store tokens and attr scores together in a list of tuple [(token, attr_score)]
        word_att_scores = get_word_att_scores(all_tokens=all_tokens, att_scores=attr_scores)
        # remove <s>, </s>, <unk>, <pad>
        word_att_scores = clean_word_attr_scores(word_attr_scores=word_att_scores)

    else:
        raise Exception(f"Unrecognized reasoning method: {reasoning_method}")

    # Create mapping between lines and scores
    all_lines, all_lines_score = compute_line_score_from_att(word_att_scores)
    all_lines_score = [
        float(score.detach().numpy()) if type(score) not in [float, int] else score
        for score in all_lines_score
    ]
    return all_lines, all_lines_score
