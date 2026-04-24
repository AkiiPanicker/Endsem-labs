//Replace Blanks and Tabs with Single Space

#include <stdio.h>
int main(){
    FILE *fp1, *fp2;
    char c, prev =' ';
    fp1=fopen("input.c","r");
    fp2=fopen("output.c","w");
    while((c=fgetc(fp1))!=EOF){
        if(c==' '|| c=='\t'){
            if(prev!=' '){
                fputc(' ',fp2);
                prev=' ';
            }
        }
        else{
            fputc(c,fp2);
            prev = c;
        }
    }
    fclose(fp1);
    fclose(fp2);

}