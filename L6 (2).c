#include <stdio.h>
#include <stdlib.h>

char *input;
void S(), U(), V(), W();

void match(char expected) {
    if (*input == expected) input++;
    else { printf("Error\n"); exit(1); }
}

void S() { 
    U(); 
    V(); 
    W(); 
}

void U() {
    if (*input == '(') { 
        match('('); 
        S(); 
        match(')');
     }
    else if (*input == 'a') { 
        match('a'); 
        S(); 
        match('b'); 
    }
    else if (*input == 'd') match('d');
}

void V() {
    if (*input == 'a') { match('a'); V(); }
}

void W() {
    if (*input == 'c') { match('c'); W(); }
}

int main() {
    char buf[100];
    scanf("%s", buf);
    input = buf;
    S();
    if (*input == '\0') printf("Success\n");
    else printf("Error\n");
    return 0;
}