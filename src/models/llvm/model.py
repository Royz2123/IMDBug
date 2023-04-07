import os
from typing import List, Tuple

from models.base_model import BaseModel
from models.llvm.base_model import TextClassificationModel

MODEL_LOCATION = os.path.join(
    os.path.dirname(os.path.realpath(__file__)), "saved_models", "codebert-llvm-ic-v0"
)


class LLVM(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


class LlvmModel(BaseModel):
    MODEL_LABEL = "LLVM"
    MODEL_DETAIL = "A Static Single Assignment (SSA) based representation for Vulnerability Detection"

    def __init__(self):
        super(LlvmModel, self).__init__()
        self.llvm_object = LLVM()

    def load_model(self):
        self.model = self.llvm_object.get_model()

    def infer(
        self, funcs: List[str], file_type: str = None
    ) -> Tuple[List[List] or None, List, List]:
        self.validate_load()
        all_line_scores, y_pred, y_prob = self.llvm_object.inference(self.model, funcs)
        y_pred, y_prob = LlvmModel.convert_format(y_pred, y_prob)
        return None, y_pred, y_prob
