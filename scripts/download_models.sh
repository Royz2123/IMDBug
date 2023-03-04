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
