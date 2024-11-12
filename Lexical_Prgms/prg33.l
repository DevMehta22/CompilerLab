%option noyywrap
%{
    #include <stdio.h>
    int total_tags;
    
%}
%%
"<"[^>]*">" {total_tags++; printf("HTML tag spotted %s\n",yytext);}
.           {}
%%

int main(){
    yyin = fopen("sample.html","r");
    yylex();
    printf("Total HTML tags: %d",total_tags);
    fclose(yyin);
    return 0;
}
