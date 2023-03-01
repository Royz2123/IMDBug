from __future__ import absolute_import, division, print_function

import argparse
import logging
import os
from typing import Union, List, Dict, Any

import torch
import uvicorn
from fastapi import FastAPI
from pydantic import BaseModel
from tokenizers import Tokenizer
from transformers import (RobertaConfig, RobertaForSequenceClassification, RobertaTokenizer)

from imdbug_main import imdbug_test
from linevul_main import set_seed, TextDataset
from linevul_model import Model
from file_to_funcs.file_to_funcs import convert_file_to_funcs

logger = logging.getLogger(__name__)
app = FastAPI()

parser = argparse.ArgumentParser()

## parameters
parser.add_argument("--train_data_file", default=None, type=str, required=False,
                    help="The input training data file (a csv file).")
parser.add_argument("--output_dir", default=None, type=str, required=False,
                    help="The output directory where the model predictions and checkpoints will be written.")
parser.add_argument("--model_type", default="bert", type=str,
                    help="The model architecture to be fine-tuned.")
parser.add_argument("--block_size", default=-1, type=int,
                    help="Optional input sequence length after tokenization."
                         "The training dataset will be truncated in block of this size for training."
                         "Default to the model max input length for single sentence inputs (take into account special tokens).")
parser.add_argument("--eval_data_file", default=None, type=str,
                    help="An optional input evaluation data file to evaluate the perplexity on (a text file).")
parser.add_argument("--test_data_file", default=None, type=str,
                    help="An optional input evaluation data file to evaluate the perplexity on (a text file).")
parser.add_argument("--model_name", default="model.bin", type=str,
                    help="Saved model name.")
parser.add_argument("--model_name_or_path", default=None, type=str,
                    help="The model checkpoint for weights initialization.")
parser.add_argument("--config_name", default="", type=str,
                    help="Optional pretrained config name or path if not the same as model_name_or_path")
parser.add_argument("--use_non_pretrained_model", action='store_true', default=False,
                    help="Whether to use non-pretrained model.")
parser.add_argument("--tokenizer_name", default="", type=str,
                    help="Optional pretrained tokenizer name or path if not the same as model_name_or_path")
parser.add_argument("--code_length", default=256, type=int,
                    help="Optional Code input sequence length after tokenization.")

parser.add_argument("--do_train", action='store_true',
                    help="Whether to run training.")
parser.add_argument("--do_eval", action='store_true',
                    help="Whether to run eval on the dev set.")
parser.add_argument("--do_test", action='store_true',
                    help="Whether to run eval on the dev set.")

parser.add_argument("--evaluate_during_training", action='store_true',
                    help="Run evaluation during training at each logging step.")
parser.add_argument("--do_local_explanation", default=False, action='store_true',
                    help="Whether to do local explanation. ")
parser.add_argument("--reasoning_method", default=None, type=str,
                    help="Should be one of 'attention', 'shap', 'lime', 'lig'")

parser.add_argument("--train_batch_size", default=4, type=int,
                    help="Batch size per GPU/CPU for training.")
parser.add_argument("--eval_batch_size", default=4, type=int,
                    help="Batch size per GPU/CPU for evaluation.")
parser.add_argument('--gradient_accumulation_steps', type=int, default=1,
                    help="Number of updates steps to accumulate before performing a backward/update pass.")
parser.add_argument("--learning_rate", default=5e-5, type=float,
                    help="The initial learning rate for Adam.")
parser.add_argument("--weight_decay", default=0.0, type=float,
                    help="Weight deay if we apply some.")
parser.add_argument("--adam_epsilon", default=1e-8, type=float,
                    help="Epsilon for Adam optimizer.")
parser.add_argument("--max_grad_norm", default=1.0, type=float,
                    help="Max gradient norm.")
parser.add_argument("--max_steps", default=-1, type=int,
                    help="If > 0: set total number of training steps to perform. Override num_train_epochs.")
parser.add_argument("--warmup_steps", default=0, type=int,
                    help="Linear warmup over warmup_steps.")
parser.add_argument('--seed', type=int, default=42,
                    help="random seed for initialization")
parser.add_argument('--epochs', type=int, default=1,
                    help="training epochs")
# RQ2
parser.add_argument("--effort_at_top_k", default=0.2, type=float,
                    help="Effort@TopK%Recall: effort at catching top k percent of vulnerable lines")
parser.add_argument("--top_k_recall_by_lines", default=0.01, type=float,
                    help="Recall@TopK percent, sorted by line scores")
parser.add_argument("--top_k_recall_by_pred_prob", default=0.2, type=float,
                    help="Recall@TopK percent, sorted by prediction probabilities")

parser.add_argument("--do_sorting_by_line_scores", default=False, action='store_true',
                    help="Whether to do sorting by line scores.")
parser.add_argument("--do_sorting_by_pred_prob", default=False, action='store_true',
                    help="Whether to do sorting by prediction probabilities.")
# RQ3 - line-level evaluation
parser.add_argument('--top_k_constant', type=int, default=10,
                    help="Top-K Accuracy constant")
# num of attention heads
parser.add_argument('--num_attention_heads', type=int, default=12,
                    help="number of attention heads used in CodeBERT")
# raw predictions
parser.add_argument("--write_raw_preds", default=False, action='store_true',
                    help="Whether to write raw predictions on test data.")
# word-level tokenizer
parser.add_argument("--use_word_level_tokenizer", default=False, action='store_true',
                    help="Whether to use word-level tokenizer.")
# bpe non-pretrained tokenizer
parser.add_argument("--use_non_pretrained_tokenizer", default=False, action='store_true',
                    help="Whether to use non-pretrained bpe tokenizer.")
args = parser.parse_args()
# Setup CUDA, GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
args.n_gpu = torch.cuda.device_count()
args.device = device
# Setup logging
logging.basicConfig(format='%(asctime)s - %(levelname)s - %(name)s -   %(message)s', datefmt='%m/%d/%Y %H:%M:%S',
                    level=logging.INFO)
logger.warning("device: %s, n_gpu: %s", device, args.n_gpu, )

# Set seed
set_seed(args)
config = RobertaConfig.from_pretrained(args.config_name if args.config_name else args.model_name_or_path)
config.num_labels = 1
config.num_attention_heads = args.num_attention_heads
if args.use_word_level_tokenizer:
    print('using wordlevel tokenizer!')
    tokenizer = Tokenizer.from_file('./word_level_tokenizer/wordlevel.json')
elif args.use_non_pretrained_tokenizer:
    tokenizer = RobertaTokenizer(vocab_file="bpe_tokenizer/bpe_tokenizer-vocab.json",
                                 merges_file="bpe_tokenizer/bpe_tokenizer-merges.txt")
else:
    tokenizer = RobertaTokenizer.from_pretrained(args.tokenizer_name)
if args.use_non_pretrained_model:
    model = RobertaForSequenceClassification(config=config)
else:
    model = RobertaForSequenceClassification.from_pretrained(args.model_name_or_path, config=config,
                                                             ignore_mismatched_sizes=True)
model = Model(model, config, tokenizer, args)
checkpoint_prefix = f'checkpoint-best-f1/{args.model_name}'
output_dir = os.path.join(args.output_dir, '{}'.format(checkpoint_prefix))
model.load_state_dict(torch.load(output_dir, map_location=args.device))
model.to(args.device)


# Define input data model
class CodeInput(BaseModel):
    code: str


def prob_to_severity(prob: float) -> Union[int, None]:
    if 0.9 < prob <= 1.0:
        return 0
    elif 0.7 < prob <= 0.9:
        return 1
    else:
        return None


# Define route to handle POST requests
@app.post("/analyze_code")
async def analyze_code(input_data: CodeInput):
    # Convert code to list of functions
    splitted_code = convert_file_to_funcs(input_data.code)
    funcs = [func["function"] for func in splitted_code]
    start_indices = [func["start_line"] for func in splitted_code]

    # Predict each function
    best_threshold = 0.5
    infer_dataset = TextDataset(tokenizer, args, file_type='infer', funcs=funcs)
    y_preds, y_probs, all_line_scores = imdbug_test(args, model, tokenizer, infer_dataset,
                                                    best_threshold=best_threshold)

    # Create all line colors
    colors = list()
    for start_idx, y_pred, y_prob, line_scores in zip(start_indices, y_preds, y_probs, all_line_scores):
        if y_pred:
            colors.append({
                "line_index": start_idx,
                "probability": float(y_prob),
                "text": f"This function has a {round(float(y_prob) * 100, 2)}% of being exploitable"
            })
            line_code_colors: List[Dict[str, Any]] = [
                {
                    "line_index": start_idx + line_idx,
                    "probability": float(line_score)
                }
                for line_idx, line_score in enumerate(line_scores)
            ]

            # Remove first line since it will already be colored from the function
            line_code_colors = line_code_colors[1:]

            # Normalize line code scores to actual probabilities
            min_score = min(line_scores)
            max_score = max(line_scores)
            for line_code in line_code_colors:
                line_code["probability"] = (line_code["probability"] - min_score) / (max_score - min_score)
                line_code["text"] = f"This line has a {round(float(line_code['probability']) * 100, 2)}% " \
                                    f"chance of being the reason for this"

            # Add to line code colors
            colors += line_code_colors
        else:
            colors.append({
                "line_index": start_idx,
                "severity": 3,
                "text": f"This function looks fine (with {round(float(y_prob) * 100, 2)}% confidence)"
            })

    # Convert probability to severity
    filtered_colors = []
    for color in colors:
        if "severity" in color:
            filtered_colors.append(color)
        else:
            color["severity"] = prob_to_severity(color["probability"])
            if color["severity"] is not None:
                filtered_colors.append(color)

    logging.info(f"Returning line colors: {filtered_colors}")
    return filtered_colors


def main():
    if args.do_test:
        test_dataset = TextDataset(tokenizer, args, file_type='test')
        imdbug_test(args, model, tokenizer, test_dataset, best_threshold=0.5)


if __name__ == '__main__':
    # main()
    uvicorn.run(app, host='0.0.0.0', port=8080)
