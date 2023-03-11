from typing import List, Tuple

from src.models.base_model import BaseModel
from src.models.vdline.inference import inference


class VDLineModel(BaseModel):
    MODEL_LABEL = "VDLine"
    MODEL_DETAIL = "Line-level Source Code Vulnerability Detection"

    def __init__(self):
        super(VDLineModel, self).__init__()

        # Set loaded to true since model doesn't require any loading
        self.loaded = True

    def load_model(self) -> None:
        pass

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        # Y_pred -  The average of all line scores.
        # You can change to the max value line (that can be found in the predict function).
        all_line_scores, y_pred, y_pred = inference(funcs)

        return all_line_scores, y_pred, y_pred
