import logging
from typing import Dict, List, Tuple


class BaseModel(object):
    MODEL_LABEL = "BaseModel"
    MODEL_DETAIL = "This is the base detection model"

    def __init__(self):
        self.model = None
        self.tokenizer = None
        self.loaded: bool = False

    @classmethod
    def get_model_options(cls) -> Dict[str, str]:
        return {
            "label": cls.MODEL_LABEL,
            "detail": cls.MODEL_DETAIL
        }

    def validate_load(self) -> None:
        if not self.loaded:
            logging.info("\t\tModel hasn't been loaded yet, loading now...")
            self.load_model()
            self.loaded = True
            logging.info("\t\tModel loaded successfully")

    def load_model(self) -> None:
        raise NotImplementedError("Method load_model is not implemented")

    @staticmethod
    def convert_format(y_pred: List, y_prob: List) -> Tuple[List, List]:
        y_pred = [1 if pred["label"] == "LABEL_1" else 0 for pred in y_pred]
        y_prob = [prob["score"] if prob["label"] == "LABEL_1" else 1 - prob["score"] for prob in y_prob]
        return y_pred, y_prob

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List[List] or None, List, List]:
        raise NotImplementedError("Method infer is not implemented")
