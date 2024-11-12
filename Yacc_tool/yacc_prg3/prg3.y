%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token WHILE DO
%token NUMBER NAME
%token GE LE NE EQ
%left '>' '<' GE LE NE EQ

%%
S: WHILE CE DO E               { printf("Evaluating while loop\n"); }
 ;

CE: CE '>' CE                  { $$ = $1 > $3; }
  | CE '<' CE                  { $$ = $1 < $3; }
  | CE GE CE                   { $$ = $1 >= $3; }
  | CE LE CE                   { $$ = $1 <= $3; }
  | CE NE CE                   { $$ = $1 != $3; }
  | CE EQ CE                   { $$ = $1 == $3; }
  | NUMBER                     { $$ = $1; }
 ;

E: NUMBER                      { $$ = $1; }
 ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an expression: ");
    return yyparse();
}
