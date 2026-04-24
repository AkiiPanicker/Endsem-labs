#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100

int main() {
    char words[MAX_WORDS][50]; // Assuming each word has a maximum length of 49 characters
    int n, i, j;

    printf("Enter the number of words (n): ");
    scanf("%d", &n);

    if (n > MAX_WORDS) {
        printf("Error: Too many words. Maximum allowed: %d\n", MAX_WORDS);
        return 1;
    }

    // Input words
    for (i = 0; i < n; i++) {
        printf("Enter word %d: ", i + 1);
        scanf("%s", words[i]);
    }

    // Sort the words in alphabetical order
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                // Swap words[i] and words[j]
                char temp[50];
                strcpy(temp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
            }
        }
    }

    // Display the words in alphabetical order
    printf("Words in alphabetical order:\n");
    for (i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}
