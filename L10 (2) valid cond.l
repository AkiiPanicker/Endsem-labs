%{
#include "if_check.tab.h"
%}
%%
"if"                { return IF; }
[a-zA-Z]+           { return ID; }
[0-9]+              { return NUM; }
"=="|"!="|"<="|">=" { return RELOP; }
[ \t\n]             { ; }
.                   { return yytext[0]; }
%%
int yywrap() { return 1; }