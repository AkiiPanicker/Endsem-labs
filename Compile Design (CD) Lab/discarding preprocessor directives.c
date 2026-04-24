//Discard Preprocessor Directives

#include <stdio.h>
int main(){
    FILE *fp1, *fp2;
    char c;
    fp1=fopen("input.c","r");
    fp2=fopen("output.c","w");
    while((c=fgetc(fp1))!=EOF){
        if(c=='#'){
            while((c=fgetc(fp1))!='\n');
        }
        else{
            fputc(c,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
}
