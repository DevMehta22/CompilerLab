%option noyywrap
%{
#include<stdio.h>
int blank_spaces = 0;
int tabs = 0;
int new_lines = 0;
%}
%%

" "|"\n"|"\t" {
    if (yytext[0] == ' ') blank_spaces++;
    else if (yytext[0] == '\t') tabs++;
    else if (yytext[0] == '\n') new_lines++;

    }
%%
int main(){
    yylex();
    printf("No. of blank spaces:%d",blank_spaces);
    printf("\nNo. of tabs:%d",tabs);
    printf("\nNo. of new lines:%d:",new_lines);
    return 0;
}