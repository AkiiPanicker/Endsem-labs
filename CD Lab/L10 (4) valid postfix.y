%{
#include <stdio.h>
#include <math.h>
int yylex();
void yyerror(char *s);
%}
%token NUM
%%
input: /* empty */ | input line;
line: '\n' | exp '\n' { printf("Valid Postfix. Result: %d\n", $1); };
exp: NUM { $$ = $1; }
   | exp exp '+' { $$ = $1 + $2; }
   | exp exp '-' { $$ = $1 - $2; }
   | exp exp '*' { $$ = $1 * $2; }
   | exp exp '/' { $$ = $1 / $2; }
   | exp exp '^' { $$ = pow($1, $2); }
   ;
%%
void yyerror(char *s) { printf("Invalid Postfix\n"); }
int main() { yyparse(); return 0; }