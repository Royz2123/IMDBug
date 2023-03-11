from typing import List, Tuple

from src.models.base_model import BaseModel

from base_model import TextClassificationModel

MODEL_LOCATION = "Vulnerability-detection"


class VulnerabilityDetection(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class VDBertModel(BaseModel):
    MODEL_LABEL = "VDBert"
    MODEL_DETAIL = "A Finetuned Version of CodeBert for Vulnerability Detection"

    def __init__(self):
        super(VDBertModel, self).__init__()
        self.vdbert_object = VulnerabilityDetection()

    def load_model(self):
        self.model = self.vdbert_object.get_model()

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        score = self.vdbert_object.inference(self.model, funcs)

        # return all_line_scores, y_pred, y_pred
