%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

%token IF ID NUM RELOP
%%

if_stmt : IF '(' cond ')' '{' '}' {printf("Valid If statement \n); exit(0);};
cond : ID RELOP ID | ID RELOP NUM;
%%
void yyerror(char *s) {printf("Invalid If statement \n"); exit(0);}
int main() { yyparse(); return 0;}