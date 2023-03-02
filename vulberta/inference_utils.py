from __future__ import division, absolute_import, print_function

import argparse
import os
import random
import re
from typing import List

import numpy as np
import torch
from clang import cindex
from tokenizers import NormalizedString, PreTokenizedString
from tokenizers import Tokenizer
from tokenizers import normalizers
from tokenizers import processors
from tokenizers.models import BPE
from tokenizers.normalizers import StripAccents, Replace
from tokenizers.pre_tokenizers import PreTokenizer
from tokenizers.processors import TemplateProcessing
from transformers import RobertaForSequenceClassification


def get_vulberta_args(vulberta_model_name):
    args = argparse.ArgumentParser()
    args.vulberta_model_name = vulberta_model_name

    # Set default device (GPU or CPU)
    args.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    # Deterministic/reproducible flags

    seedlist = [42, 834, 692, 489, 901, 408, 819, 808, 531, 166]

    seed = seedlist[0]
    os.environ['PYTHONHASHSEED'] = str(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    np.random.seed(seed)
    random.seed(seed)
    torch.backends.cudnn.enabled = True
    torch.backends.cudnn.deterministic = True
    torch.backends.cudnn.benchmark = False
    return args


def get_vulberta_model(args):
    # Custom tokenizer
    # Load pre-trained tokenizers
    vocab, merges = BPE.read_file(vocab="../vulberta/tokenizer/drapgh-vocab.json",
                                  merges="../vulberta/tokenizer/drapgh-merges.txt")
    my_tokenizer = Tokenizer(BPE(vocab, merges, unk_token="<unk>"))

    my_tokenizer.normalizer = normalizers.Sequence([StripAccents(), Replace(" ", "Ä")])
    my_tokenizer.pre_tokenizer = PreTokenizer.custom(MyTokenizer())
    my_tokenizer.post_processor = processors.ByteLevel(trim_offsets=False)
    my_tokenizer.post_processor = TemplateProcessing(
        single="<s> $A </s>",
        special_tokens=[
            ("<s>", 0),
            ("<pad>", 1),
            ("</s>", 2),
            ("<unk>", 3),
            ("<mask>", 4)
        ]
    )

    my_tokenizer.enable_truncation(max_length=1024)
    my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=None,
                                pad_to_multiple_of=None)

    model = RobertaForSequenceClassification.from_pretrained(
        f'../vulberta/models/{args.vulberta_model_name}')
    model.to(args.device)
    model.eval()

    return model, my_tokenizer


@torch.no_grad()
def infer(model, my_tokenizer, code_list, args):
    cleaned_code = [cleaner(code) for code in code_list]
    test_encodings = my_tokenizer.encode_batch(cleaned_code)
    test_encodings = process_encodings(test_encodings)

    input_ids = torch.LongTensor(test_encodings['input_ids']).to(args.device)
    attention_mask = torch.Tensor(test_encodings['attention_mask']).to(args.device)
    outputs = model(input_ids, attention_mask=attention_mask)
    logits = outputs.logits
    probs = torch.softmax(logits, dim=1)
    y_preds = np.argmax(probs.detach().cpu().numpy(), axis=1)
    y_probs = probs.detach().cpu().numpy()[np.arange(len(y_preds)), y_preds]
    all_line_scores = [np.zeros_like(y_preds) for _ in range(len(code_list))]
    return all_line_scores, y_preds, y_probs


class MyTokenizer:
    cidx = cindex.Index.create()

    def clang_split(self, i: int, normalized_string: NormalizedString) -> List[NormalizedString]:
        # Tokkenize using clang
        tok = []
        tu = self.cidx.parse('tmp.c',
                             args=[''],
                             unsaved_files=[('tmp.c', str(normalized_string.original))],
                             options=0)
        for t in tu.get_tokens(extent=tu.cursor.extent):
            spelling = t.spelling.strip()

            if spelling == '':
                continue

            # Keyword no need

            # Punctuations no need

            # Literal all to BPE

            # spelling = spelling.replace(' ', '')
            tok.append(NormalizedString(spelling))

        return (tok)

    def pre_tokenize(self, pretok: PreTokenizedString):
        pretok.split(self.clang_split)


def process_encodings(encodings):
    input_ids = []
    attention_mask = []
    for enc in encodings:
        input_ids.append(enc.ids)
        attention_mask.append(enc.attention_mask)
    return {'input_ids': input_ids, 'attention_mask': attention_mask}


def cleaner(code):
    # Remove code comments
    pat = re.compile(r'(/\*([^*]|(\*+[^*/]))*\*+/)|(//.*)')
    code = re.sub(pat, '', code)
    code = re.sub('\n', '', code)
    code = re.sub('\t', '', code)
    return (code)
