//Simple Lexical Analyzer

#include <stdio.h>
#include <ctype.h>

FILE *fp;
int line=1;
void getNextToken(){
    char c;
    while((c=fgetc(fp))!=EOF){
        if (c=='\n') line++;
        else if(isalpha(c)){
            printf("Line %d: Identifier\n",line);
            while(isalnum(c=fgetc(fp)));
        }
        else if(isdigit(c)){
            printf("Line %d : Number\n",line);
            while(isdigit(fgetc(fp)));
        }
        else if(c=="+"||c=="-"||c=="*"||c=="/"){
            printf("Line %d: Operator\n",line);
        }
        else if(c=='('||c==')'||c=='{'||c=='}'||c==';'){
            printf("Line %d: Special Symbol \n",line);
        }

    }
}

int main(){
    fp=fopen("input.c","r");
    if(!fp){
        prinf("File not found\n");
        return 0;
    }
    getNextToken();
    fclose(fp);
}