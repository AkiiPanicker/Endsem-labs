%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
st: exp { printf("Result: %d\n", $1); };
exp: exp '+' exp { $$ = $1 + $3; }
   | exp '-' exp { $$ = $1 - $3; }
   | exp '*' exp { $$ = $1 * $3; }
   | exp '/' exp { if($3==0) yyerror("Div by 0"); else $$ = $1 / $3; }
   | NUM { $$ = $1; };
%%
void yyerror(char *s) { printf("Error: %s\n", s); }
int main() { yyparse(); return 0; }