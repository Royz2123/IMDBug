from src.models.llvm.base_model import TextClassificationModel

MODEL_LOCATION = "codebert-llvm-ic-v0"


class LLVM(TextClassificationModel):
    def __init__(self):
        super().__init__(MODEL_LOCATION)


if __name__ == "__main__":
    v = LLVM()
    model = v.get_model()
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
    texts = [code]
    res = v.inference(model, texts)
    print(res)
