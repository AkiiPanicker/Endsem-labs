#include <stdio.h>
#include <string.h>

void Sort(char str[], int length) {
    int i, j;
    char temp;

    for (i = 0; i < length - 1; i++) {
        for (j = 0; j < length - i - 1; j++) {
            if (str[j] > str[j + 1]) {

                temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main() {
    char String[100];
    printf("Enter a string: ");
    scanf("%s", String);
    int length = strlen(String);
    Sort(String, length);
    printf("Sorted string: %s\n", String);

    return 0;
}
