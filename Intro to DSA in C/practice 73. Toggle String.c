#include <stdio.h>
#include <string.h>

int main() {
    char sentence[1000];
    int i = 0;

    printf("Enter a string: ");
    gets(sentence);

    printf("String is: ");
    puts(sentence);

    while (sentence[i] != '\0') {
        if (sentence[i] >= 'a' && sentence[i] <= 'z') {
            sentence[i] = sentence[i] - 32;
        } else if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
            sentence[i] = sentence[i] + 32;
        }

        i++;
    }

    printf("Toggled string is: ");
    puts(sentence);

    return 0;
}
