%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(char *s);
%}

%token TYPE ID 
%%

start: TYPE list ';' { printf("Valid Declaration \n"); exit(0);};
list: ID | ID ',' list;
%%

void yyerror(char *s){printf("Invalid Declaration \n"); exit(0);};
int main(){yyparse(); return 0;}


Execution:
bison -d decl.y && flex decl.l && gcc decl.tab.c lex.yy.c -o decl