//Identify keywords, identifiers, numbers, strings and special 

int isKeyword(char s[]){
    char *kw[] = {"int","float","char","if","else","while","return","for"};
    for(int i=0; i<8; i++){
        if(!strcmp(s,kw[i])) return 1;
    return 0;
    }
}
int main(){
    char s[100];
    printf("Enter token: ");
    scanf("%s",s);

    if(iskeyword(s))
        printf("Keyword \n");
    else if(isdigits(s[0]))
        printf("Numeric Constant \n");
    else if(s[0]=='"')
        printf("String Literal \n");
    else if(isalpha(s[0]))
        printf("Identifier \n");
    else
        printf("Special Symbol \n");
}