from typing import List, Dict, Any, Tuple

from models.base_model import BaseModel
from models.linevul.imdbug_main import predict_on_function
from models.linevul.linvul_api_utils import get_linveul_args, get_linevul_model


class LineVulModel(BaseModel):
    MODEL_LABEL = "LineVul"
    MODEL_DETAIL = "A Transformer-based Line-Level Vulnerability Prediction Approach"

    def __init__(self):
        super(LineVulModel, self).__init__()
        self.args = get_linveul_args()

    def load_model(self):
        self.model, self.tokenizer = get_linevul_model(self.args)

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        self.validate_load()
        return predict_on_function(self.args, funcs, self.model, self.tokenizer)
