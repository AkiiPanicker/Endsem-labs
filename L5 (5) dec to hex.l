%%
[0-9]+ { int d = atoi(yytext); printf("%X", d); }
.|\n { printf("%s", yytext); }
%%
int main() {
    yylex();
    return 0;
}
int yywrap() { return 1; }