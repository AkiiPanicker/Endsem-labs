#include <stdio.h>
#include <stdlib.h>

char *input;
void S(), T(), T_prime();

void match(char expected) {
    if (*input == expected) input++;
    else { printf("Error\n"); exit(1); }
}

void S() {
    if (*input == 'a') match('a');
    else if (*input == '>') match('>');
    else if (*input == '(') { match('('); T(); match(')'); }
    else { printf("Error\n"); exit(1); }
}

void T() { 
    S(); 
    T_prime(); 
}

void T_prime() {
    if (*input == ',') { 
        match(','); 
        S(); 
        T_prime(); 
    }
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