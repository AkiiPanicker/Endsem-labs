//Global Symbol Table Program

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char sym[50][50];
int n=0;

int search(char s[]){
    for(int i=0;i<n;i++){
        if(!strcmp(sym[i],s)==0) return 1;
    return 0;
    }
}

int main(){
    FILE *fp;
    char c,word[50];
    int i=0;

    fp=fopen("input.c","r");
    while((c=fgetc(fp)!=EOF)){
        if(isalpha(c)){
            word[i++]=c;
            while(isalnum(c=fgetc(fp)))
                word[i++] = c;
            word[i] = '\0';
            i=0;
            if(!search(word)){
                strcpy(sym[n++],word);
            }
        }
    }
    printf("Global Symbol Table\n");
    for(int i=0;i<n;i++)
        printf("%d %s\n",i+1,sym[i]);
}