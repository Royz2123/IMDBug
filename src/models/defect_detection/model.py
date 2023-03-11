from typing import List, Tuple

from src.models.base_model import BaseModel

from base_model import TextClassificationModel

MODEL_LOCATION = "codebert2codebert-finetuned-code-defect-detection"


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

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        score = self.detect_object.inference(self.model, funcs)

        # return all_line_scores, y_pred, y_pred
