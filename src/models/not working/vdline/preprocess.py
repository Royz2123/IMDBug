import gensim
import sctokenizer


# Function to open a file, put it in readable format, tokenize it, and tag each line
def process_corpus(fname, tokens_only=False):
    print("Tokenizing file")
    tokens = sctokenizer.tokenize_str(fname, lang='c')
    print("File tokenized")
    # Form a dictionary with one key for every occupied line of the code file
    line_tokens = {}
    for i in range(len(tokens)):
        curr_line = tokens[i].line
        if i == 0:
            line_tokens[curr_line] = []
        else:
            if curr_line == tokens[i - 1].line:
                continue
            else:
                line_tokens[curr_line] = []

    # Populate dictionary with token values
    for i in range(len(tokens)):
        curr_line = tokens[i].line
        val = tokens[i].token_value
        line_tokens[curr_line].append(val)

    # Iterate through the dictionary and use values as lines to tag for Doc2Vec
    for key in line_tokens:
        if tokens_only:
            yield line_tokens[key]
        else:
            # For training data, add tags
            yield gensim.models.doc2vec.TaggedDocument(line_tokens[key], [key])
