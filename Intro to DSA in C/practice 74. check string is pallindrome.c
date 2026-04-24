#include <stdio.h>
#include <string.h>

int main() {
    char string[1000];
    int i = 0;
    char rev_string[1000];

    printf("Enter a string: ");
    gets(string);

    printf("String is: ");
    puts(string);

    int a = strlen(string);

    while (string[i] != '\0') {
        rev_string[i] = string[a - 1];
        i++;
        a--;
    }

    rev_string[i] = '\0';  

    i = 0;

    while (string[i] != '\0') {
        if (rev_string[i] != string[i]) {
            printf("String is not a palindrome\n");
            return 0;
        }
        i++;
    }

    printf("String is a palindrome\n");

    return 0;
}
