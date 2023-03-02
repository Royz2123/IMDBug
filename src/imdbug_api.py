from __future__ import absolute_import, division, print_function

import logging
from typing import List

import uvicorn
from fastapi import FastAPI

from file_to_funcs.file_to_funcs import convert_file_to_funcs
from imdbug_main import imdbug_test
from inference_utils import CodeInput, get_filtered_colors, get_colors
from linevul_main import TextDataset
from linvul_api_utils import get_linvul_args, get_linevul_model
from vulberta.inference_utils import get_vulberta_args, get_vulberta_model, infer

app = FastAPI()

# Define input data model
class CodeInput(BaseModel):
    filename: str = "cpp"
    code: str
    # TODO MOVE

# Define route to handle POST requests
@app.post("/analyze_code")
async def analyze_code(input_data: CodeInput):
    # Convert code to list of functions
    splitted_code: List = convert_file_to_funcs(input_data.code, tree_type=input_data.filename.split(".")[-1])
    global args, model, tokenizer
    funcs = [func["function"] for func in splitted_code]
    start_indices = [func["start_line"] for func in splitted_code]

    # Predict each function
    if args.MODEL == 'linvul':
        all_line_scores, y_preds, y_probs = await predict_on_function(args, funcs, model, tokenizer)
    elif args.MODEL == 'vulberta':
        all_line_scores, y_preds, y_probs = infer(model, tokenizer, funcs, args)
    else:
        raise ValueError(f"Model {args.MODEL} not supported")

    # Create all line colors
    colors = await get_colors(all_line_scores, start_indices, y_preds, y_probs)

    # Convert probability to severity
    filtered_colors = await get_filtered_colors(colors)

    logging.info(f"Returning line colors: {filtered_colors}")
    return filtered_colors


async def predict_on_function(args, funcs, model, tokenizer):
    infer_dataset = TextDataset(tokenizer, args, file_type='infer', funcs=funcs)
    y_preds, y_probs, all_line_scores = imdbug_test(args, model, tokenizer, infer_dataset,
                                                    best_threshold=args.best_threshold)
    return all_line_scores, y_preds, y_probs


def main():
    global args, model, tokenizer
    if args.do_test:
        model, tokenizer = get_linevul_model(args)
        test_dataset = TextDataset(tokenizer, args, file_type='test')
        imdbug_test(args, model, tokenizer, test_dataset, best_threshold=args.best_threshold)


if __name__ == '__main__':
    # main()

    model_selected = 'linvul'  # 'linvul' or 'vulberta'
    # model_selected = 'vulberta'  # 'linvul' or 'vulberta'
    # Get model
    if model_selected == 'linvul':
        args = get_linvul_args()
        model, tokenizer = get_linevul_model(args)
    elif model_selected == 'vulberta':
        vulberta_name = 'd2a'  # currently only mlp is supported
        args = get_vulberta_args(vulberta_name)
        model, tokenizer = get_vulberta_model(args)
    else:
        raise ValueError(f"Model {model_selected} not supported")
    args.MODEL = model_selected

    uvicorn.run(app, host='0.0.0.0', port=8080)
