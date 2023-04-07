import tensorflow as tf
from gensim.models import Doc2Vec
from tensorflow import keras
from preprocess import process_corpus
import warnings
import numpy as np

warnings.filterwarnings("ignore")

# Process input file
print("Begin")
test_func = list(process_corpus("test.c", tokens_only=True))
print("Function processed")
line_list = []

# Load Models
print("Loading models")
nlp_model = Doc2Vec.load("line_vec_model")
class_model = keras.models.load_model("classifier_model")
print("Models loaded")

# Use models to convert lines of input file to vectors and classify
for j in range(len(test_func)):
    inferred_vector = nlp_model.infer_vector(test_func[j])
    print(test_func[j])
    result = class_model.predict(tf.reshape(inferred_vector, shape=(1, 50)))
    print(result)
    line_list.append(result)


def calculate_average():
    list_of_scores = []
    for line in line_list:
        for score in line:
            list_of_scores.append(score)
    scores = np.array(list_of_scores)
    average_scores = np.average(scores)
    return average_scores


average_scores = calculate_average()
if average_scores > 0.4:
    vul_line = line_list.index(max(line_list))
    print(
        "The most vulnerable line is predicted to be",
        vul_line,
        "out of",
        len(line_list),
    )
else:
    print("Probably safe code")
