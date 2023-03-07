from __future__ import absolute_import, division, print_function

import logging
import os

import uvicorn
from fastapi import FastAPI

from common.log_util import LogHTTPException, setup_logging, CustomFormatter, pretty_log, TITLE_LEVEL
from file_to_funcs.file_to_funcs import convert_file_to_funcs
from inference_utils import CodeInput, get_filtered_colors, get_colors
from models.base_model import BaseModel
from models.linevul.imdbug_main import predict_on_function
from models.linevul.linvul_api_utils import get_linveul_args, get_linevul_model
from models.vulberta.inference_utils import get_vulberta_args, get_vulberta_model, infer
import glob
from importlib import __import__

app = FastAPI()
setup_logging()
pretty_log("Initalizing IMDbug app\n", TITLE_LEVEL)

# A mapping between model labels and the corresponding model
module_names = glob.glob(os.path.join("models", "*", "model.py"))
loaded_modules = [__import__(module_name.replace("\\", ".")[:-3]) for module_name in module_names]
models = {cls.MODEL_LABEL: cls() for cls in BaseModel.__subclasses__()}
logging.info(f"Supported models: {list(models.keys())}")


@app.get("/")
async def alive():
    pretty_log("\nReturning alive status")
    return "I'm alive!"


@app.get("/get_model_names")
async def get_model_names():
    global models
    pretty_log("\nReturning model options")
    return [model.get_model_options() for model in models.values()]

    # Add vulbeta models
    # vulberta_models_path = 'models/vulberta/saved_models'
    # if os.path.exists(vulberta_models_path):
    #     vulberta_models = [
    #         m for m in os.listdir(vulberta_models_path)
    #         if os.path.isdir(os.path.join(vulberta_models_path, m))
    #            and 'MACOSX' not in m and 'VB' in m
    #     ]
    #     vulberta_models = [
    #         {"label": model_name, "detail": "A variant of the VulBerta model"}
    #         for model_name in vulberta_models
    #     ]
    #     model_names.extend(vulberta_models)


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
def analyze_code(input_data: CodeInput):
    global models

    # Get selected model
    selected_model_label = input_data.model_label
    pretty_log(f"\nStarting code analysis for {selected_model_label}")

    # Make sure selected model exists
    if selected_model_label not in models:
        raise LogHTTPException(500, f"Unsupported model label: {selected_model_label}")
    selected_model: BaseModel = models[selected_model_label]

    # Convert code to list of functions
    file_type = input_data.file_name.split(".")[-1]
    split_code = convert_file_to_funcs(input_data.code, tree_type=file_type)
    funcs = [func["function"] for func in split_code]
    start_indices = [func["start_line"] for func in split_code]

    # Make sure some functions were found
    if len(funcs) == 0:
        raise LogHTTPException(500, "No functions found in code! Returning ...")

    # Predict each function
    all_line_scores, y_preds, y_probs = selected_model.infer(funcs, file_type)

    # elif 'VB' in model_selected:
    # all_line_scores, y_preds, y_probs = infer(model, tokenizer, funcs, args)

    # Create all line colors
    colors = get_colors(all_line_scores, start_indices, y_preds, y_probs)

    # Convert probability to severity
    filtered_colors = get_filtered_colors(colors)

    logging.info(f"Returning line colors: {filtered_colors}")
    return filtered_colors


# async def load_model(model_selected):
#     global loaded_models
#     if model_selected not in loaded_models:
#         logging.info(f"\t\tModel {model_selected} was not found in loaded models, attempting to load ...")
#         if model_selected == 'LineVul':
#             args = get_linveul_args()
#             model, tokenizer = get_linevul_model(args)
#         elif 'VB' in model_selected:
#             args = get_vulberta_args(model_selected)
#             model, tokenizer = get_vulberta_model(args)
#         else:
#             raise LogHTTPException(500, f"Model {model_selected} not supported")
#         loaded_models[model_selected] = {
#             "args": args,
#             "model": model,
#             "tokenizer": tokenizer
#         }
#         logging.info("\t\tLoaded model successfully")


if __name__ == '__main__':
    uvicorn.run(app, host='0.0.0.0', port=8080, log_config=None)
