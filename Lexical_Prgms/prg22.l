%option noyywrap
%{
#include<stdio.h>
%}
%%
[a-zA-Z_][a-zA-Z0-9_]* {printf("%s has length %zu\n",yytext,yyleng);}
-?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {printf("%s has length %zu\n",yytext,yyleng);}
%%
int main(){
    yylex();
    return 0;
}