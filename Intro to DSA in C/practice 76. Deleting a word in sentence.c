#include <stdio.h>
#include <string.h>

int main() {
    char sentence[1000], word[1000];
    int i = 0, j;

    printf("Enter a sentence: ");
    gets(sentence);

    printf("Sentence is: ");
    puts(sentence);

    printf("Enter word to delete: ");
    gets(word);

    while (sentence[i] != '\0') {
        int match = 1;

        for (j = 0; word[j] != '\0'; j++) {
            if (sentence[i + j] != word[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            // Skip the word by moving characters to the left
            j = 0;
            while (sentence[i + j] != '\0') {
                sentence[i + j] = sentence[i + j + strlen(word)];
                j++;
            }
        } else {
            i++;
        }
    }

    printf("Resulting sentence after deleting the word: %s\n", sentence);

    return 0;
}
