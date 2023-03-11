from typing import List, Tuple

from src.models.base_model import BaseModel

from base_model import TextClassificationModel

MODEL_LOCATION = "codebert-base-buggy-token-classification"


class Buggy(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class BuggyModel(BaseModel):
    MODEL_LABEL = "BuggyClassification"
    MODEL_DETAIL = "A Token Classification Approach for Buggy Detection based-on CodeBert"

    def __init__(self):
        super(BuggyModel, self).__init__()
        self.buggy_object = Buggy()

    def load_model(self):
        self.model = self.buggy_object.get_model()

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        score = self.buggy_object.inference(self.model, funcs)

        # return all_line_scores, y_pred, y_pred
