%option noyywrap
%{
// Identify KW and identifiers
int kw_count=0;
int id_count=0;
int num_count=0;
%}
%%
int|float|switch        {printf("%s is KW \n",yytext); kw_count++;}
[a-zA-Z][a-zA-Z0-9]*    {printf("%s is Identifier\n",yytext); id_count++;}
[0-9][0-9]*             {printf("%s is number\n",yytext); num_count++;}
%%
int main()
{
    yylex(); 
    printf("kw_count: %d\n",kw_count);
    printf("id_count_count: %d\n",id_count);
    printf("num_count: %d\n",num_count); 
    return 0;
}