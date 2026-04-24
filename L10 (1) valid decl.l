%{
    #include "decl.tab.h"
}

%%
"int"|"char"|"float"|"double" {return TYPE;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
"," {return ',';}
";" {return ';';}
[\t \n] {;}
. {return yytext[0];}
%%

int yywrap(){
    return 1;
}