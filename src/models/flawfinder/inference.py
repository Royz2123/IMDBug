from models.flawfinder.flawfinder import flawfind


def inference(codes, extension):
    fix_extension = f".{extension}"
    all_predictions = [flawfind(code, fix_extension) for code in codes]
    return all_predictions


if __name__ == '__main__':
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
    codes = [code]
    extensions = ".c"
    all_line_scores, y_preds, y_probs = inference(codes, extensions)[0]
    print(all_line_scores)
    print(y_preds)
    print(y_probs)
