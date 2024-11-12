%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototypes
void yyerror(const char *s);
int yylex(void);
%}

/* Define tokens */
%token NUMBER
%token PLUS MINUS TIMES DIVIDE POWER
%token LPAREN RPAREN

%union {
    int num; 
}


%type <num> expr e t f p



%%
input:
    
    | input line
    ;

line:
      '\n'                        
    | expr '\n'     { printf("= %d\n", $1); }
    ;

// Expression rules
expr:
      e
    ;

e:
      e PLUS t      { $$ = $1 + $3; }
    | e MINUS t     { $$ = $1 - $3; }
    | t             { $$ = $1; }
    ;

t:
      t TIMES f     { $$ = $1 * $3; }
    | t DIVIDE f    { 
                        if ($3 == 0) {
                            yyerror("Error: Division by zero");
                            YYERROR;
                        }
                        else {
                            $$ = $1 / $3; 
                        }
                    }
    | f             { $$ = $1; }
    ;

f:
      f POWER p     { $$ = (int)pow($1, $3); }
    | p             { $$ = $1; }
    ;

p:
      MINUS p       { $$ = -$2; }
    | LPAREN e RPAREN { $$ = $2; }
    | NUMBER        { $$ = $1; }
    ;

%%

// Error Handling
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

// Main Function
int main(void) {
    printf("Enter expressions to calculate (Ctrl+D to quit):\n");
    return yyparse();
}
