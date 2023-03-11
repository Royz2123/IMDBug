import os
from typing import List, Tuple

from models.base_model import BaseModel
from models.code_bert.base_model import TextClassificationModel

MODEL_LOCATION = os.path.join(
    os.path.dirname(os.path.realpath(__file__)),
    "saved_models",
    "codebert-base-finetuned-detect-insecure-code"
)


class CodeBert(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class CodeBertModel(BaseModel):
    MODEL_LABEL = "CodeBert"
    MODEL_DETAIL = "A Finetuned Version of CodeBert Base for Insecure Code"

    def __init__(self):
        super(CodeBertModel, self).__init__()
        self.code_bert_object = CodeBert()

    def load_model(self):
        self.model = self.code_bert_object.get_model()

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List[List] or None, List, List]:
        self.validate_load()
        all_line_scores, y_pred, y_prob = self.code_bert_object.inference(self.model, funcs)
        y_pred, y_prob = CodeBertModel.convert_format(y_pred, y_prob)
        return None, y_pred, y_prob
