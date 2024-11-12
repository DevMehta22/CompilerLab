%{
    #include "prg2.tab.h"
    extern int yylval;      
%}

%%
[0-9]+      {yylval = atoi(yytext); return NUMBER;}
[a-zA-Z]*   {return NAME;}
[\t\n]      ;
.           { return yytext[0]; }

%%

int yywrap(){
    return 1;
}