%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex(void);
%}

%token NAME NUMBER

%left '-' '+'
%left '*' '/'
%right '^'
%nonassoc UMINUS

%%
statement:  NAME '=' expression
      |     expression       { printf("= %d\n", $1); }
      ;
expression: expression '+' expression { $$ = $1 + $3; }
          | expression '-' expression { $$ = $1 - $3; }
          | expression '*' expression { $$ = $1 * $3; }
          | expression '/' expression 
                { 
                    if ($3 == 0)
                        yyerror("divide by zero");
                    else
                        $$ = $1 / $3; 
                }
          | expression '^' expression {$$ = pow($1,$3);}
          | '-' expression   %prec UMINUS   { $$ = -$2; }
          | '(' expression ')' { $$ = $2; }
          | NUMBER             { $$ = $1; }
          ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an expression: ");
    return yyparse();
}
