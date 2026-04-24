#include <stdio.h>

int compareStrings(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) {
            return -1;
        } else if (a[i] > b[i]) {
            return 1;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (a[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

void copyString(char destination[], const char source[]) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}


void swapStrings(char array[][100], int i, int j) {
    char temp[100];
    copyString(temp, array[i]);
    copyString(array[i], array[j]);
    copyString(array[j], temp);
}

int main() {
    int numWords;

    printf("Enter the number of words: ");
    scanf("%d", &numWords);

    char words[numWords][100];

    int i;
    for (i = 0; i < numWords; i++) {
        printf("Enter word %d: ", i + 1);
        scanf("%s", words[i]);
    }

    for (i = 0; i < numWords - 1; i++) {
        int j;
        for (j = 0; j < numWords - i - 1; j++) {
            if (compareStrings(words[j], words[j + 1]) > 0) {
                swapStrings(words, j, j + 1);
            }
        }
    }

    printf("Sorted words:\n");
    for (i = 0; i < numWords; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}