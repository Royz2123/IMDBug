from __future__ import absolute_import, division, print_function

import logging
import os

import uvicorn
from fastapi import FastAPI

from common.log_util import LogHTTPException, setup_logging, CustomFormatter, pretty_log
from file_to_funcs.file_to_funcs import convert_file_to_funcs
from inference_utils import CodeInput, get_filtered_colors, get_colors
from models.linevul.imdbug_main import predict_on_function
from models.linevul.linvul_api_utils import get_linvul_args, get_linevul_model
from models.vulberta.inference_utils import get_vulberta_args, get_vulberta_model, infer

app = FastAPI()
loaded_models = dict()


@app.get("/")
async def alive():
    pretty_log("\nReturning alive status")
    return "I'm alive!"


@app.get("/get_model_names")
async def get_model_names():
    pretty_log("\nReturning model names")

    # Add linevul mode
    model_names = [{"label": 'Linevul', "detail": "A Transformer-based Line-Level Vulnerability Prediction Approach"}]

    # Add vulbeta models
    vulberta_models_path = 'models/vulberta/saved_models'
    if os.path.exists(vulberta_models_path):
        vulberta_models = [
            m for m in os.listdir(vulberta_models_path)
            if os.path.isdir(os.path.join(vulberta_models_path, m))
            and 'MACOSX' not in m and 'VB' in m
        ]
        vulberta_models = [
            {"label": model_name, "detail": "A variant of the VulBerta model"}
            for model_name in vulberta_models
        ]
        model_names.extend(vulberta_models)

    # Return all model names
    return model_names


@app.post("/analyze_example")
async def analyze_example():
    pretty_log("\nReturning analyzing example")
    return [
        {
            "line_index": 0,
            "severity": 0,
            "text": f"This is an error example (sup ido)"
        },
        {
            "line_index": 1,
            "severity": 1,
            "text": f"This is a warning example"
        },
        {
            "line_index": 2,
            "severity": 2,
            "text": f"This is an info example"
        },
        {
            "line_index": 3,
            "severity": 3,
            "text": f"This is an hint example"
        }
    ]


# Define route to handle POST requests
@app.post("/analyze_code")
async def analyze_code(input_data: CodeInput):
    pretty_log("\nStarting code analysis")
    model_selected = input_data.model_name

    # Load model
    await load_model(model_selected)
    model_context = loaded_models[model_selected]
    args = model_context["args"]
    model = model_context["model"]
    tokenizer = model_context["tokenizer"]

    # Convert code to list of functions
    split_code = convert_file_to_funcs(input_data.code, tree_type=input_data.filename.split(".")[-1])
    funcs = [func["function"] for func in split_code]
    start_indices = [func["start_line"] for func in split_code]

    if len(funcs) == 0:
        raise LogHTTPException(500, "No functions found in code! Returning ...")

    # Predict each function
    if model_selected == 'linevul':
        all_line_scores, y_preds, y_probs = await predict_on_function(args, funcs, model, tokenizer)
    elif 'VB' in model_selected:
        all_line_scores, y_preds, y_probs = infer(model, tokenizer, funcs, args)
    else:
        raise LogHTTPException(500, f"Model {model_selected} not supported")

    # Create all line colors
    colors = await get_colors(all_line_scores, start_indices, y_preds, y_probs)

    # Convert probability to severity
    filtered_colors = await get_filtered_colors(colors)

    logging.info(f"Returning line colors: {filtered_colors}")
    return filtered_colors


async def load_model(model_selected):
    global loaded_models
    if model_selected not in loaded_models:
        logging.info(f"\t\tModel {model_selected} was not found in loaded models, attempting to load ...")
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
        logging.info("\t\tLoaded model successfully")


if __name__ == '__main__':
    setup_logging()
    uvicorn.run(app, host='0.0.0.0', port=8080, log_config=None)
