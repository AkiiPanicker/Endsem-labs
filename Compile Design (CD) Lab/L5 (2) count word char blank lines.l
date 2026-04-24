%{
int w=0, c=0, b=0, l=0;
%}
%%
\n {l++; c++;}
" " {b++; c++;}
[^\t\n ]+ {w++; c += yyleng;}
. {c++;}
%%
int main() {
    yylex();
    printf("Lines: %d\nWords: %d\nBlanks: %d\nChars: %d\n", l, w, b, c);
    return 0;
}
int yywrap() { return 1; }