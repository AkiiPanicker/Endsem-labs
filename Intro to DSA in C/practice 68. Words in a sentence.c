#include <stdio.h>
#include <string.h>

int main() {
    char sentence[1000];
    int i = 0;
    int count = 0;
    int is_word = 0;

    printf("Enter a string: ");
    gets(sentence);

    printf("String is: ");
    puts(sentence);

    while (sentence[i] != '\0') {
        // Check if the current character is not a space, newline, or tab
        while (sentence[i] != ' ' && sentence[i] != '\n' && sentence[i] != '\t' && sentence[i] != '\0') {
            is_word = 1;
            i++;
        }

        // Skip to the end of the current word
        while (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
            i++;
        }

        // If a word was found, increment the count
        if (is_word) {
            count++;
            is_word = 0; // Reset for the next word
        }
    }

    printf("Number of words in a sentence is: %d\n", count);

    return 0;
}
