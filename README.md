# IMDBug
Mission Statement: Given a source code repository in C++/C, indicate areas that have a higher probability to contain a vulnerability

This repo contains: 
- Modified implementations of the `LineVul` model
- A Fastapi server for model inference
- A VSCode extension that communicates with the server (not yet)

## Sever Installation
Server installation might be a bit tricky. 

```
git clone https://github.com/Royz2123/IMDBug.git
cd IMDBug
```

The project runs on `Python3`, and is dependent on:
```
pip install gdown
pip install transformers
pip install captum
pip install torch
pip install numpy
pip install tqdm
pip install pickle
pip install sklearn
pip install pandas
pip install tokenizers
```

And install the model like so:
```
cd linevul
cd saved_models
cd checkpoint-best-f1
gdown https://drive.google.com/uc?id=1oodyQqRb9jEcvLMVVKILmu8qHyNwd-zH
cd ../../..
```

If doesn't work, check out: https://github.com/awsm-research/LineVul

## Running the code
Just run the `run.bat` script (which in turn runs the `imdbug_api.py` module)
```
cd \path\to\IMDBug
run.bat
```