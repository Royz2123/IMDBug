from typing import List, Tuple

from src.models.base_model import BaseModel

from base_model import TextClassificationModel

MODEL_LOCATION = "codebert-base-finetuned-detect-insecure-code"


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

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        score = self.code_bert_object.inference(self.model, funcs)

        # return all_line_scores, y_pred, y_pred
