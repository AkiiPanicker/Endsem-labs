#include <stdio.h>

int main() {
    char line[1000];
    int wordCount = 0;
    int isWord = 0; 

    printf("Enter a line of text: ");
    fgets(line, sizeof(line), stdin);

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t') {
            isWord = 0; 
        } else if (isWord == 0) {
            isWord = 1; 
            wordCount++; 
        }
    }

    printf("Number of words in the line: %d\n", wordCount);

    return 0;
}
