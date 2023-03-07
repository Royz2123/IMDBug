cd ..
git lfs install

echo "Downloading models"

:: echo "\tDownloading Vulberta models"
:: cd src/models/vulberta
:: if not exist "saved_models/" mkdir "saved_models/"
:: cd saved_models/
:: wget --no-check-certificate -O finetuning_models.zip "https://onedrive.live.com/download?cid=15E206B36A9C8AE7&resid=15E206B36A9C8AE7%21300803&authkey=AIj7B7HPzR0lljI"
:: unzip finetuning_models.zip
:: cd ../../../../

:: echo "\tDownloading Linevul model"
:: cd src/model/linevul
:: if not exist "saved_models/" mkdir "saved_models/"
:: cd saved_models/
:: if not exist "checkpoint-best-f1/" mkdir "checkpoint-best-f1/"
:: cd checkpoint-best-f1/
:: gdown https://drive.google.com/uc?id=1oodyQqRb9jEcvLMVVKILmu8qHyNwd-zH
:: cd ../../../../../

echo "\tDownloading vdbert model"
cd src/models/vdbert
if not exist "saved_models/" mkdir "saved_models/"
cd saved_models/
git clone https://huggingface.co/Zaib/Vulnerability-detection
cd ../../../../

echo "\tDownloading code_bert model"
cd src/models/code_bert
if not exist "saved_models/" mkdir "saved_models/"
cd saved_models/
git clone https://huggingface.co/mrm8488/codebert-base-finetuned-detect-insecure-code
cd ../../../../

echo "\tDownloading buggy_classification model"
cd src/models/buggy_classification
if not exist "saved_models/" mkdir "saved_models/"
cd saved_models/
git clone https://huggingface.co/alexjercan/codebert-base-buggy-token-classification
cd ../../../../

echo "\tDownloading defect_detection model"
cd src/models/defect_detection
if not exist "saved_models/" mkdir "saved_models/"
cd saved_models/
git clone https://huggingface.co/mrm8488/codebert2codebert-finetuned-code-defect-detection
cd ../../../../

echo "\tDownloading llvm model"
cd src/models/llvm
if not exist "saved_models/" mkdir "saved_models/"
cd saved_models/
git clone https://huggingface.co/iyaja/codebert-llvm-ic-v0
cd ../../../../