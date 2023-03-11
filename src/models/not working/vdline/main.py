import numpy as np
import pandas as pd
import gensim
import os
import tensorflow as tf
from tensorflow import keras
from preprocess import process_corpus
from sklearn.model_selection import train_test_split

import warnings

warnings.filterwarnings("ignore")


# Function to take in a function and vulnerable line and remove vulnerable line
def remove_vulnerable_line(func, vul_line):
    if vul_line in func:
        output_func = func.replace(vul_line, "")
        return output_func
    else:
        return False


# Read in the pkl file as a dataframe
df = pd.read_pickle('vulnerable_sourcecode.pkl')
print(df.columns)

# Retrieve the function and line columns as lists
func_list = df["function"].tolist()
vul_line_list = df["line"].tolist()

# Reduce lists, getting the same number of vulnerable and non-vulnerable lines
print("Lists formed")
func_list = func_list[:50]
total_lines = 0
for i in range(len(func_list)):
    line_num = len(func_list[i].splitlines())
    total_lines += line_num

vul_line_list = vul_line_list[:total_lines - 10]
print("Lists reduced")

# Create shortened dataset
if not os.path.exists("training_data_short.c"):
    print("Creating new file of reduced training data for Doc2Vec")
    with open(r'training_data_short.c', 'w') as fp:
        for item in func_list:
            # write each item on a new line
            fp.write("%s\n" % item)

# Remove all vulnerable lines of code from the functions
new_func_list = []
for i in range(len(func_list)):
    new_func = remove_vulnerable_line(func_list[i], vul_line_list[i])
    if new_func:
        new_func_list.append(new_func)
    else:
        new_func_list.append(func_list[i])

# Isolate the reduced vulnerable and non-vulnerable lines into separate files
if not os.path.exists("vulnerable_lines_short.c"):
    print("Creating new file of reduced vulnerable lines")
    with open(r'vulnerable_lines_short.c', 'w') as fp:
        for item in vul_line_list:
            # write each item on a new line
            fp.write("%s\n" % item)

if not os.path.exists("nonvulnerable_funcs_short.c"):
    print("Creating new file of reduced non-vulnerable lines")
    with open(r'nonvulnerable_funcs_short.c', 'w') as fp:
        for item in new_func_list:
            # write each item on a new line
            fp.write("%s\n" % item)

# Process dataset for classifier
print("Processing Corpus")
train_corpus = list(process_corpus("training_data_short.c"))
non_vul_corpus = list(process_corpus("nonvulnerable_funcs_short.c", tokens_only=True))
vul_corpus = list(process_corpus("vulnerable_lines_short.c", tokens_only=True))

# Training the model
print("Creating Model")
model = gensim.models.doc2vec.Doc2Vec(vector_size=50, min_count=2, epochs=40)
print("Building Vocabulary")
model.build_vocab(train_corpus)
print("Training Model")
model.train(train_corpus, total_examples=model.corpus_count, epochs=model.epochs)
print("Model Trained")
model.save("line_vec_model")
print("Model saved")

if not os.path.exists("classifier_model"):
    # Output results in a format that can be passed to a classifier
    result_df = pd.DataFrame(columns=['Vector', 'Status'])
    for j in range(len(non_vul_corpus)):
        inferred_vector = model.infer_vector(non_vul_corpus[j])
        result_df = result_df.append({'Vector': inferred_vector, 'Status': 0}, ignore_index=True)
    print("Non-vulnerable vectors added to results")
    for n in range(len(vul_corpus)):
        inferred_vector = model.infer_vector(vul_corpus[n])
        result_df = result_df.append({'Vector': inferred_vector, 'Status': 1}, ignore_index=True)
    print("Vulnerable vectors added to results")

    # Split Dataframe
    Vec = result_df['Vector']
    Vul = result_df['Status']

    # Convert Vec and Vul to acceptable keras model format
    Vec = Vec.tolist()
    Vul = Vul.tolist()
    Vec = np.array(Vec)
    Vul = np.array(Vul)

    # Format data for training classifier
    # 70% for training, 30% for testing
    Vec_train, Vec_test, Vul_train, Vul_test = train_test_split(Vec, Vul, test_size=0.3, random_state=0, shuffle=1)

    # Build classifier model
    class_model = keras.Sequential([tf.keras.layers.Input(shape=(50,)),
                                    keras.layers.Dense(16, activation=tf.nn.relu),
                                    keras.layers.Dense(16, activation=tf.nn.relu),
                                    keras.layers.Dense(1, activation=tf.nn.sigmoid), ])

    # Compile the network
    class_model.compile(optimizer='adam',
                        loss='binary_crossentropy',
                        metrics=['accuracy', tf.keras.metrics.Precision(), tf.keras.metrics.Recall()])

    # Train and test the model
    class_model.fit(Vec_train, Vul_train, epochs=200, batch_size=1)
    test_loss, test_acc, test_prec, test_recall = class_model.evaluate(Vec_test, Vul_test)
    class_model.save("classifier_model")

    # Display the model's accuracy, precision, recall, and loss
    print('Test accuracy:', test_acc)
    print('Test precision:', test_prec)
    print('Test recall:', test_recall)
    print('Test loss:', test_loss)

    # Calculate and display the model's F1 score
    f1_score = 2 * (test_prec * test_recall) / (test_prec + test_recall)
    print('F1 score:', f1_score)
