%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    int character=0; 
    int words=0;
    int lines=0;
%}

%%

[\n]+      {lines++;}
[a-zA-Z]+  {words++; character+=strlen(yytext);}
[0-9]+     {character+=strlen(yytext);}
.          {}

%%

int main(){
    yyin = fopen("file.c","r");
    yylex();
    printf("Number of words: %d\n",words);
    printf("Number of lines: %d\n",lines);
    printf("Number of characters: %d\n",character);

    fclose(yyin);
    return 0;
}
