%{
int v=0, c=0;
%}
%%
[aeiouAEIOU] {v++;}
[a-zA-Z] {c++;}
\n {return 0;}
. ;
%%
int main() {
    printf("Enter string: ");
    yylex();
    printf("Vowels: %d, Consonants: %d\n", v, c);
    return 0;
}
int yywrap() { return 1; }