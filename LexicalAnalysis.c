#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isKeyword(const char *lexeme){
    const char *keywords[] = { "auto",     "break",    "case",     "char", 
            "const",    "continue", "default",  "do", 
            "double",   "else",     "enum",     "extern", 
            "float",    "for",      "goto",     "if", 
            "int",      "long",     "register", "return", 
            "short",    "signed",   "sizeof",   "static", 
            "struct",   "switch",   "typedef",  "union", 
            "unsigned", "void",     "volatile", "while" };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for(int i = 0; i < num_keywords; i++){
        if(strcmp(lexeme, keywords[i]) == 0){
            return true;
        }
    }
    return false;
}

bool isIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    for (int i = 1; i < strlen(str); i++) {
        if (!isdigit(str[i]) && str[i] != '_') {
            return false;
        }
    }

    return true;
}

bool isOperator(const char *str){
    const char *operators[] = { "+", "-", "*", "/", "%", "==", "!=", "<=", ">=", "<", ">", "=", "+=", "-=", "*=", "/=", "%=", "&=","|=", "^=", "<<=", ">>=", "&", "|", "^", "~", "!","&&", "||", "++", "--", "++", "--"};
    int num_operators = sizeof(operators) / sizeof(operators[0]);
    for(int i = 0; i < num_operators; i++){
        if(strcmp(str, operators[i]) == 0){
            return true;
            }
    }
    return false;
}

bool isDelimeter(const char *str){
    const char *delimeters[] = {"(", ")", "{", "}", "[", "]",";", ",", ".", ":", " ", "\t", "\n"};
    int num_delimeters = sizeof(delimeters) / sizeof(delimeters[0]);
    for(int i = 0; i < num_delimeters; i++){
        if(strcmp(str, delimeters[i]) == 0){
            return true;
        }
    }
    return false;
}

bool isNumeric(const char *str){
    for(int i =0; i<strlen(str); i++){
        if(!isdigit(str[i])){
            return false;
            }
    }
    return true;
}

int main(){
    // printf("Enter the Lexeme:\n");
    // scanf("%s", lexeme);

    // if(isKeyword(lexeme)){
    //     printf("Keyword\n");
    // } else if(isIdentifier(lexeme)) {
    //     printf("Identifier\n");
    // }else{
    //     printf("Not a Keyword or Identifier\n");
    // }

    char lexeme[256];
    
    printf("Enter the filename: ");
    char filename[256];
    scanf("%s", filename);
    
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File not found\n");
        return 0;
    }

    printf("File opened successfully\n");

    while(fscanf(fp, "%s", lexeme) != EOF){
        printf("Lexeme: %s\n",lexeme);
        if(isKeyword(lexeme)){
            printf("'%s' is a Keyword\n", lexeme);
        } else if(isIdentifier(lexeme)) {
            printf("'%s' is an Identifier\n", lexeme);
        } else if(isNumeric(lexeme)){
            printf("%s  is a Number\n",lexeme);
        } else if(isOperator(lexeme)){
            printf("%s is an Operator\n",lexeme);
        } else if(isDelimeter(lexeme)){
            printf("%s is a Delimeter\n",lexeme);
        }else {
            printf("'%s' is other\n", lexeme);
        }
    }
    
    fclose(fp);
    return 0;
}
