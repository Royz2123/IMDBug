cd ..
conda create -n vulberta
conda activate vulberta
conda install ipykernel
pip install torch pandas numpy scikit-learn transformers clang
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
sudo add-apt-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main"
sudo apt update
sudo apt install llvm-14-dev
sudo apt-get update
sudo apt-get install python-clang
sudo apt install clang
env CLANG_LIBRARY_PATH=$(llvm-config-14 --libdir)
pip install uvicorn
pip install fastapi
pip install captum
pip install tree_sitter