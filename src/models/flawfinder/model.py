from typing import List, Tuple

from models.base_model import BaseModel
from models.flawfinder.flawfinder import flawfind


class FlawFinderModel(BaseModel):
    MODEL_LABEL = "FlawFinder"
    MODEL_DETAIL = "A Classic Static Analyzer for Vulnerability Prediction"

    def __init__(self):
        super(FlawFinderModel, self).__init__()

        # Set loaded to true since model doesn't require any loading
        self.loaded = True

    def load_model(self) -> None:
        pass

    def infer(self, funcs: List[str], file_type: str = None) -> Tuple[List, List, List]:
        all_predictions = [flawfind(code, file_type) for code in funcs]

        # Get individual line scores
        all_line_scores = []
        y_pred = []
        for prediction in all_predictions:
            # Set prediction
            y_pred.append(int(prediction[1]["score"]))

            # Set line scores
            if not len(prediction[0]):
                all_line_scores.append([])
            else:
                curr_line_scores = [""] * (
                    int(max(prediction[0], key=lambda x: int(x["line"]))["line"])
                )
                for line_score in prediction[0]:
                    curr_line_scores[int(line_score["line"]) - 1] = line_score[
                        "description"
                    ]
                all_line_scores.append(curr_line_scores)

        return all_line_scores, y_pred, y_pred
