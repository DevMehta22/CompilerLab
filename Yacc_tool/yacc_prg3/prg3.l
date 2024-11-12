%{
    #include "prg3.tab.h"
    #include <stdlib.h>
    extern int yylval;
%}

%%
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z]+           { return NAME; }
">="                { return GE; }
"<="                { return LE; }
"!="                { return NE; }
"=="                { return EQ; }
">"                 { return '>'; }
"<"                 { return '<'; }
"while"             { return WHILE; }
"do"                { return DO; }
[\t\n ]+            ; // Ignore whitespace
.                   { return yytext[0]; } // Return any other character as a token

%%

int yywrap() {
    return 1;
}
