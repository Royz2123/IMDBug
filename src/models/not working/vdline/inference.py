import os
import warnings

import numpy as np
import tensorflow as tf
from gensim.models import Doc2Vec
from tensorflow import keras

from src.models.vdline.preprocess import process_corpus

warnings.filterwarnings("ignore")


def calculate_average(line_list):
    list_of_scores = []
    for line in line_list:
        for score in line:
            list_of_scores.append(score)
    scores = np.array(list_of_scores)
    average_scores = np.average(scores)
    return average_scores


def predict(code):
    test_func = list(process_corpus(code, tokens_only=True))
    line_list = []

    # Load Models
    linevd_dir = os.path.join("models", "vdline")
    nlp_model = Doc2Vec.load(os.path.join(linevd_dir, 'line_vec_model'))
    class_model = keras.models.load_model(os.path.join(linevd_dir, 'classifier_model'))

    # Use models to convert lines of input file to vectors and classify
    for j in range(len(test_func)):
        inferred_vector = nlp_model.infer_vector(test_func[j])
        result = class_model.predict(tf.reshape(inferred_vector, shape=(1, 50)))
        line_list.append(result)
    all_scores = line_list
    vul_line = line_list.index(max(line_list))
    avg = calculate_average(all_scores)
    return all_scores, [avg], [avg]


# Process input file
def inference(codes):
    predictions = [predict(code) for code in codes]
    return predictions


if __name__ == '__main__':
    code = """// A C program to demonstrate buffer overflow
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    int main(int argc, char *argv[])
    {
    
    
           char buffer[5];
    
    
           if (argc < 2)
           {
                  printf("strcpy() NOT executed....\n");
                  printf("Syntax: %s <characters>\n", argv[0]);
                  exit(0);
           }
    
    
           strcpy(buffer, argv[1]);
           printf("buffer content= %s\n", buffer);
    
           printf("strcpy() executed...\n");
    
           return 0;
    }"""
    codes = [code]
    print(inference(codes))
