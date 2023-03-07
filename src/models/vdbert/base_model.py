from transformers import pipeline, AutoTokenizer, BertTokenizer
import torch
import numpy


class TextClassificationModel(object):
    def __init__(self, model_location: str):
        self.task = "text-classification"
        self.model_location = model_location

    def get_model_old(self):
        tokenizer = AutoTokenizer.from_pretrained(self.model_location)
        model = BertTokenizer.from_pretrained(self.model_location)
        return model, tokenizer

    def get_model(self):
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        return pipeline("text-classification",
                        model=self.model_location,
                        return_all_scores=True, device=device)

    def inference_old(self, model, tokenizer, texts: list):
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        inputs = tokenizer(texts, return_tensors="pt", truncation=True, padding='max_length')
        labels = torch.tensor([1]).unsqueeze(0)  # Batch size 1
        outputs = model(**inputs, labels=labels, device=device)
        logits = outputs.logits
        probs = torch.softmax(logits, dim=1)
        y_probs = probs.detach().cpu().numpy()
        y_preds = numpy.argmax(probs, axis=1)
        all_line_scores = numpy.zeros_like(y_preds)
        return all_line_scores, y_preds, y_probs

    def inference(self, model, texts: list):
        y_preds = model(texts)
        return [], y_preds, y_preds
