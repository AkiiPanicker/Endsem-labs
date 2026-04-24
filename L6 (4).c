#include <stdio.h>
#include <stdlib.h>

char *input;
void S(), L(), L_prime();

void match(char expected) {
    if (*input == expected) input++;
    else { printf("Error\n"); exit(1); }
}

void S() {
    if (*input == '(') { 
        match('('); 
        L(); 
        match(')'); 
    }
    else if (*input == 'a') match('a');
}

void L() { 
    S(); 
    L_prime(); 
}

void L_prime() {
    if (*input == ',') { 
        match(','); 
        S(); 
        L_prime(); 
    }
}

int main() {
    char buf[100];
    scanf("%s", buf);
    input = buf;
    S();
    if (*input == '\0') printf("Success\n");
    return 0;
}