import os.path
from typing import List, Tuple

from models.base_model import BaseModel
from models.buggy_classification.base_model import TextClassificationModel

MODEL_LOCATION = os.path.join(
    os.path.dirname(os.path.realpath(__file__)),
    "saved_models",
    "codebert-base-buggy-token-classification",
)


class Buggy(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class BuggyModel(BaseModel):
    MODEL_LABEL = "BuggyClassification"
    MODEL_DETAIL = (
        "A Token Classification Approach for Buggy Detection based-on CodeBert"
    )

    def __init__(self):
        super(BuggyModel, self).__init__()
        self.buggy_object = Buggy()

    def load_model(self):
        self.model = self.buggy_object.get_model()

    def infer(
        self, funcs: List[str], file_type: str = None
    ) -> Tuple[List[List] or None, List, List]:
        self.validate_load()
        all_line_scores, y_pred, y_prob = self.buggy_object.inference(self.model, funcs)
        y_pred, y_prob = BuggyModel.convert_format(y_pred, y_prob)
        return None, y_pred, y_prob
