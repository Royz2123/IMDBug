from __future__ import absolute_import, division, print_function

import logging
import os
from typing import List, Any, Dict

import uvicorn
from fastapi import FastAPI

from file_to_funcs.file_to_funcs import convert_file_to_funcs
from imdbug_main import imdbug_test
from inference_utils import CodeInput, get_filtered_colors, get_colors
from linevul_main import TextDataset
from linvul_api_utils import get_linvul_args, get_linevul_model
from vulberta.inference_utils import get_vulberta_args, get_vulberta_model, infer

app = FastAPI()
loaded_models = dict()


@app.get("/get_model_names")
async def get_model_names():
    model_names = ['linevul']
    vulberta_models_path = '../vulberta/models'
    vulberta_models = [m for m in os.listdir(vulberta_models_path) if
                       os.path.isdir(os.path.join(vulberta_models_path, m)) and 'MACOSX' not in m and 'VB' in m]
    model_names.extend(vulberta_models)
    return model_names


# Define route to handle POST requests
@app.post("/analyze_code")
async def analyze_code(input_data: CodeInput):
    model_selected = input_data.model_name

    # Load model
    await load_model(model_selected)
    model_context = loaded_models[model_selected]
    args = model_context["args"]
    model = model_context["model"]
    tokenizer = model_context["tokenizer"]

    # Convert code to list of functions
    splitted_code: List = convert_file_to_funcs(input_data.code, tree_type=input_data.filename.split(".")[-1])
    funcs = [func["function"] for func in splitted_code]
    start_indices = [func["start_line"] for func in splitted_code]

    # Predict each function
    if model_selected == 'linevul':
        all_line_scores, y_preds, y_probs = await predict_on_function(args, funcs, model, tokenizer)
    elif 'VB' in model_selected:
        all_line_scores, y_preds, y_probs = infer(model, tokenizer, funcs, args)
    else:
        raise ValueError(f"Model {model_selected} not supported")

    # Create all line colors
    colors = await get_colors(all_line_scores, start_indices, y_preds, y_probs)

    # Convert probability to severity
    filtered_colors = await get_filtered_colors(colors)

    logging.info(f"Returning line colors: {filtered_colors}")
    return filtered_colors


async def load_model(model_selected):
    global loaded_models
    if model_selected not in loaded_models:
        # Get model
        if model_selected == 'linevul':
            args = get_linvul_args()
            model, tokenizer = get_linevul_model(args)
        elif 'VB' in model_selected:
            args = get_vulberta_args(model_selected)
            model, tokenizer = get_vulberta_model(args)
        else:
            raise ValueError(f"Model {model_selected} not supported")
        loaded_models[model_selected] = {
            "args": args,
            "model": model,
            "tokenizer": tokenizer
        }


async def predict_on_function(args, funcs, model, tokenizer):
    infer_dataset = TextDataset(tokenizer, args, file_type='infer', funcs=funcs)
    y_preds, y_probs, all_line_scores = imdbug_test(args, model, tokenizer, infer_dataset,
                                                    best_threshold=args.best_threshold)
    return all_line_scores, y_preds, y_probs


if __name__ == '__main__':
    uvicorn.run(app, host='0.0.0.0', port=8080)
