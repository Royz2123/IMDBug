# VDLine
Line-level source code vulnerability detection project using Doc2Vec and binary classification

# File Descriptions
dataset_scraper.py: Scraper program used to extract dataset from GitHub repositories and combine them into vulnerable_sourcecode.pkl
                    Initially used on a previous version of VDLine and is now outdated. Including for record purposes.
                    
preprocess.py: Python file used to hold the function used to tokenize and otherwise preprocess a code file.
               Depending on input parameters, output can be used to test or train the Doc2Vec model
               
main.py: Main python file used to train and evaluate the Doc2Vec model and binary classification model

vul_detector.py: Python script using saved Doc2Vec and classifier models to predict vulnerability probabilities for each line of the code file passed into it

one_function.c: Single c function contained in a file. Included for simple testing of vul_detector.py

vulnerable_sourcecode.pkl: Entire labeled dataset of C source code functions captured by the scraper. Includes funcitons from FFmpeg, ImageMagick, OpenSSL, Linux-Kernel,                            and PHP-src

# Running the Project

1. Install all libraries and relevant dependencies contained within the preprocess, main, and vul_detector files.

2. Run the main.py file first to build and save the Doc2Vec and binary classification models

3. Run the vul_detector.py file for a quick demonstration of the models working to classify each line in an input file of code
   - This file will run on one_function.c by default
   - In order to test with different code, modification of one_function.c or the upload of a new .c file into the project directory is necessary
