#include <stdio.h>
#include <stdlib.h>
int main(){
    char color[20];
    char pluralNoun[20];
    char celebrityF[20];
    char celebrityL[20];

    printf("Enter a color:");
    scanf("%s", &color);
    printf("Enter a Plural Noun:");
    scanf("%s", &pluralNoun);
    printf("Enter a celebrity first name: ");
    scanf("%s", &celebrityF);
    printf("Enter a celebrity last name: ");
    scanf("%s", &celebrityL);

    printf("Roses are %s \n", color);
    printf("%s are blue \n", pluralNoun);
    printf("I love %s %s \n", celebrityF, celebrityL);

    return 0;
}

