//if its lowercase to uppercase just change +32 into -32 OR (= c - ('a' - 'A'))
#include <stdio.h>
#include <stdlib.h>
int main() {
    char c;

    printf("Enter a character in uppercase: ");
    scanf("%c", &c);

    if (c >= 'A' && c <= 'Z') {
        char lowercase = c + ('a' - 'A'); //you can use +32 also 
        printf("The character in lowercase: %c\n", lowercase);
    } else {
        printf("Input is not an uppercase letter.\n");
    }

    return 0;
}
