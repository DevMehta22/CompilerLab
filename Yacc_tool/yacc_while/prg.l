%{
#include "prg.tab.h"  
%}

%% 
"while"     { return WHILE; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"<"         { return '<'; }
">"         { return '>'; }
"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"="         { return '='; }
";"         { return ';'; }
[0-9]+      { return NUMBER; }   
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; } 
[ \n\t]+    ;                    
.           { return *yytext; }  

%% 

int yywrap() {
    return 1;
}
