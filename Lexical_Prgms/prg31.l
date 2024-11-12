%option noyywrap
%{
    #include <stdio.h>
%}

%%
"//".*                          {;}
\/\*([^*]|\*+[^/])*\*+\/        {;}
.|\n                            { fprintf(yyout,"%s",yytext); }

%%

int main(){
    yyin = fopen("file.c","r");
    yyout = fopen("output.txt","w");
    yylex();
    fclose(yyin);
    fclose(yyout);
    return 0;
}
