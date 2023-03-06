from __future__ import division, absolute_import, print_function

from typing import Union, List, Dict, Any

from pydantic import BaseModel


class CodeInput(BaseModel):
    code: str
    filename: str = "cpp"
    model_name: str = "LineVul"


def prob_to_severity(prob: float) -> Union[int, None]:
    if 0.9 < prob <= 1.0:
        return 0
    elif 0.7 < prob <= 0.9:
        return 1
    else:
        return None


async def get_filtered_colors(colors):
    filtered_colors = []
    for color in colors:
        if "severity" in color:
            filtered_colors.append(color)
        else:
            color["severity"] = prob_to_severity(color["probability"])
            if color["severity"] is not None:
                filtered_colors.append(color)
    return filtered_colors


async def get_colors(all_line_scores, start_indices, y_preds, y_probs):
    colors = list()
    for start_idx, y_pred, y_prob, line_scores in zip(start_indices, y_preds, y_probs, all_line_scores):
        if y_pred:
            colors.append({
                "line_index": start_idx,
                "probability": float(y_prob),
                "text": f"This function has a {round(float(y_prob) * 100, 2)}% of being exploitable"
            })
            line_code_colors: List[Dict[str, Any]] = [
                {
                    "line_index": start_idx + line_idx,
                    "probability": float(line_score)
                }
                for line_idx, line_score in enumerate(line_scores)
            ]

            # Remove first line since it will already be colored from the function
            line_code_colors = line_code_colors[1:]

            # Normalize line code scores to actual probabilities
            min_score = min(line_scores)
            max_score = max(line_scores)
            for line_code in line_code_colors:
                line_code["probability"] = (line_code["probability"] - min_score) / (max_score - min_score)
                line_code["text"] = f"This line has a {round(float(line_code['probability']) * 100, 2)}% " \
                                    f"chance of being the reason for this"

            # Add to line code colors
            colors += line_code_colors
        else:
            colors.append({
                "line_index": start_idx,
                "severity": 3,
                "text": f"This function looks fine (with {round((1 - float(y_prob)) * 100, 2)}% confidence)"
            })
    return colors
