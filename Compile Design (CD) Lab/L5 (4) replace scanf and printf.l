%{
int s=0, p=0;
%}
%%
"scanf" {s++; printf("READ");}
"printf" {p++; printf("WRITE");}
. {printf("%s", yytext);}
%%
int main() {
    yylex();
    fprintf(stderr, "\nScanf count: %d, Printf count: %d\n", s, p);
    return 0;
}
int yywrap() { return 1; }