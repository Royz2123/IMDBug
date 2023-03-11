import os
from typing import List, Tuple

from models.base_model import BaseModel
from models.defect_detection.base_model import TextClassificationModel

MODEL_LOCATION = os.path.join(
    os.path.dirname(os.path.realpath(__file__)),
    "saved_models",
    "codebert2codebert-finetuned-code-defect-detection"
)


class DefectDetection(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class DefectDetectionModel(BaseModel):
    MODEL_LABEL = "DefectDetection"
    MODEL_DETAIL = "A Finetuned Version of CodeBert for Code Defect Detection"

    def __init__(self):
        super(DefectDetectionModel, self).__init__()
        self.detect_object = DefectDetection()

    def load_model(self):
        self.model = self.detect_object.get_model()

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List[List] or None, List, List]:
        self.validate_load()
        all_line_scores, y_pred, y_prob = self.detect_object.inference(self.model, funcs)
        y_pred, y_prob = DefectDetectionModel.convert_format(y_pred, y_prob)
        return None, y_pred, y_prob
