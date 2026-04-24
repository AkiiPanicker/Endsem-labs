#include <stdio.h>

int main() {
    char inputString[100]; 
    int length = 0;
    int i = 0;

    printf("Enter a string: ");
    scanf("%s", inputString);

    while (inputString[i] != '\0') {
        length++;
        i++;
    }

    printf("Length of the string: %d\n", length);

    return 0;
}
