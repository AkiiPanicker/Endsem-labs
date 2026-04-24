%{
int pi=0, ni=0, pf=0, nf=0;
%}
%%
\+?[0-9]+ {pi++;}
-[0-9]+ {ni++;}
\+?[0-9]*\.[0-9]+ {pf++;}
-[0-9]*\.[0-9]+ {nf++;}
\n {return 0;}
. ;
%%
int main() {
    yylex();
    printf("Pos Int: %d\nNeg Int: %d\nPos Float: %d\nNeg Float: %d\n", pi, ni, pf, nf);
    return 0;
}
int yywrap() { return 1; }