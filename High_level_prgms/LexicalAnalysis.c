#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool Keywords(const char *lexeme){
    const char *keywords[] = { 
        "const",    "continue", "default",  "do", 
        "float",    "for",      "goto",     "if", 
        "auto",     "break",    "case",     "char", 
        "int",      "long",     "register", "return",    
        "double",   "else",     "enum",     "extern",
        "unsigned", "void",     "volatile", "while"   
        "short",    "signed",   "sizeof",   "static", 
        "struct",   "switch",   "typedef",  "union", 
             };

    for(int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++){
        if(strcmp(lexeme, keywords[i]) == 0){
            return true;
        }
    }
    return false;
}

bool Identifiers(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    for (int i = 1; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }

    return true;
}

bool Operators(const char *str){
    const char *operators[] = { "+", "-", "*", "/", "%", "==", "!=", "<=", ">=", "<", ">", "=", "+=", "-=", "*=", "/=", "%=", "&=","|=", "^=", "<<=", ">>=", "&", "|", "^", "~", "!","&&", "||", "++", "--", "++", "--"};
    int num_operators = sizeof(operators) / sizeof(operators[0]);
    for(int i = 0; i < num_operators; i++){
        if(strcmp(str, operators[i]) == 0){
            return true;
            }
    }
    return false;
}

bool Delimeters(const char *str){
    const char *delimeters[] = {"(", ")", "{", "}", "[", "]",";", ",", ".", ":", " ", "\t", "\n"};
    int num_delimeters = sizeof(delimeters) / sizeof(delimeters[0]);
    for(int i = 0; i < num_delimeters; i++){
        if(strcmp(str, delimeters[i]) == 0){
            return true;
        }
    }
    return false;
}

bool StringLiterals(const char *str){
    if(str[0] != '"' || str[strlen(str) - 1] != '"'){
        return false;
        }
    if(strlen(str)<2){
        return false;
    }
    return true;
}

bool Numbers(const char *str){
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

    // if(Keywords(lexeme)){
    //     printf("Keyword\n");
    // } else if(Identifiers(lexeme)) {
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
        if(Keywords(lexeme)){
            printf("'%s' is a Keyword\n", lexeme);
        } else if(Identifiers(lexeme)) {
            printf("'%s' is an Identifier\n", lexeme);
        } else if(Numbers(lexeme)){
            printf("%s  is a Number\n",lexeme);
        } else if(Operators(lexeme)){
            printf("%s is an Operator\n",lexeme);
        } else if(Delimeters(lexeme)){
            printf("%s is a Delimeter\n",lexeme);
        } else if(StringLiterals(lexeme)){
            printf("%s is a String Literal\n",lexeme);
        }
        else {
            printf("'%s' is other\n", lexeme);
        }
    }
    
    fclose(fp);
    return 0;
}
