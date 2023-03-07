cd ..
echo "Downloading models"

echo "\tDownloading Vulberta models"
cd src/models/vulberta/models
wget --no-check-certificate -O finetuning_models.zip "https://onedrive.live.com/download?cid=15E206B36A9C8AE7&resid=15E206B36A9C8AE7%21300803&authkey=AIj7B7HPzR0lljI"
unzip finetuning_models.zip
cd ../../../../

echo "\tDownloading Linevul model"
cd src/model/linevul/saved_models/checkpoint-best-f1
gdown https://drive.google.com/uc?id=1oodyQqRb9jEcvLMVVKILmu8qHyNwd-zH
cd ../../../../../


echo "\tDownloading vdbert model"
cd src/models/vdbert/Vulnerability-detection
git lfs install
git clone https://huggingface.co/Zaib/Vulnerability-detection
cd ../../../../../

echo "\tDownloading code_bert model"
cd src/models/code_bert/codebert-base-finetuned-detect-insecure-code
git lfs install
git clone https://huggingface.co/mrm8488/codebert-base-finetuned-detect-insecure-code
cd ../../../../../

echo "\tDownloading buggy_classification model"
cd src/models/buggy_classification/codebert-base-buggy-token-classification
git lfs install
git clone https://huggingface.co/alexjercan/codebert-base-buggy-token-classification
cd ../../../../../

echo "\tDownloading defect_detection model"
cd src/models/defect_detection/codebert2codebert-finetuned-code-defect-detection
git lfs install
git clone https://huggingface.co/mrm8488/codebert2codebert-finetuned-code-defect-detection
cd ../../../../../

echo "\tDownloading llvm model"
cd src/models/llvm/codebert-llvm-ic-v0
git lfs install
git clone https://huggingface.co/iyaja/codebert-llvm-ic-v0
cd ../../../../../