from typing import List, Tuple

from src.models.base_model import BaseModel

from base_model import TextClassificationModel

MODEL_LOCATION = "codebert-llvm-ic-v0"


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

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        score = self.llvm_object.inference(self.model, funcs)

        # return all_line_scores, y_pred, y_pred
