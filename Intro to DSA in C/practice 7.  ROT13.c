#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char rot13(char ch) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return (ch - base + 13) % 26 + base;
    }
    return ch;
}

int main() {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = rot13(input[i]);
    }

    printf("ROT13 Encrypted: %s\n", input);


    return 0;
}
