import os
from typing import List, Tuple

from models.base_model import BaseModel
from models.vdbert.base_model import TextClassificationModel

MODEL_LOCATION = os.path.join(
    os.path.dirname(os.path.realpath(__file__)),
    "saved_models",
    "Vulnerability-detection"
)


class VulnerabilityDetection(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class VDBertModel(object):
    MODEL_LABEL = "VDBert"
    MODEL_DETAIL = "A Finetuned Version of CodeBert for Vulnerability Detection"

    def __init__(self):
        super(VDBertModel, self).__init__()
        self.vdbert_object = VulnerabilityDetection()

    def load_model(self):
        self.model = self.vdbert_object.get_model()

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List[List] or None, List, List]:
        self.validate_load()
        all_line_scores, y_pred, y_prob = self.vdbert_object.inference(self.model, funcs)
        y_pred, y_prob = VDBertModel.convert_format(y_pred, y_prob)
        return None, y_pred, y_prob
