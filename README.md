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
pip install language_data
pip install tree_sitter
```

You can also refer to `scripts/make_env.sh` for a more detailed description of the installation press.
In order to install the models, go to `scripts` and then run `download_models`. This will attempt to 
download all the supported models. 

## Running the code
Just go to `scripts` and run the `run.bat` script (which in turn runs the `imdbug_app.py` module, you can just run 
this directly yourself)
```
cd \path\to\IMDBug
cd scripts
run.bat
```

And you're done!