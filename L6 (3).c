#include <stdio.h>
#include <stdlib.h>

char *input;
void S(), A(), B();

void match(char expected) {
    if (*input == expected) input++;
    else { printf("Error\n"); exit(1); }
}

void S() { match('a'); A(); match('c'); B(); match('e'); }

void A() {
    if (*input == 'b') match('b');
    else if (*input == 'A') { match('A'); match('b'); } // Based on A->Ab|b
}

void B() { match('d'); }

int main() {
    char buf[100];
    scanf("%s", buf);
    input = buf;
    S();
    if (*input == '\0') printf("Success\n");
    return 0;
}