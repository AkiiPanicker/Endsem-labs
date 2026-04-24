//Local Symbol Table

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char sym[50][50];
int n=0;
int main(){
    FILE *fp;
    char c,word[50];
    int i=0, inside=0;
    fp=fopen("input.c","r");
    while((c=fgetc(fp))!=EOF){
        if(c=='{') inside =1;
        if(c=='}') inside = 0;
        if(inside && isalpha(c)){
            word[i++]=c;
            while(isalnum(c=fgetc(fp)))
                word[i++] = c;
            word[i] = '\0';
            i=0;
            strcpy(sym[n++],word);
        }
    }
    printf("Local Symbol Table : \n" );
    for(int i=0;i<n;i++)
        printf("%d %s\n",i+1,sym[i]);
}