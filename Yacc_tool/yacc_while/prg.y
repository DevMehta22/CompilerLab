%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token WHILE ID NUMBER
%token EQ NE LE GE

%% 

program:
    WHILE_LOOP
    ;

WHILE_LOOP:
    WHILE '(' condition ')' '{' statement_list '}'
    {
        printf("Parsed a while loop\n");
    }
    ;

condition:
    ID '<' NUMBER
    | ID '>' NUMBER
    | ID LE NUMBER
    | ID GE NUMBER
    | ID EQ NUMBER
    | ID NE NUMBER
    ;

statement_list:
    statement_list statement
    |
    ;

statement:
    ID '=' E ';'
    ;

E:
    T
    | E '+' T
    | E '-' T
    ;

T:
    F
    | T '*' F
    | T '/' F
    ;

F:
    ID
    | NUMBER
    | '(' E ')'
    ;

%% 

int main() {
    printf("Enter a while loop:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
