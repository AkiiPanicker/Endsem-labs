#include <stdio.h>

int main() {
    char str1[] = "Hello, ";
    char str2[] = "world!";
    char result[100]; 
    
    int i, j;

    // Copy the characters from the first string
    for (i = 0; str1[i] != '\0'; i++) {
        result[i] = str1[i];
    }

    // Output : result = "Hello, "

    // Concatenate the characters from the second string
    for (j = 0; str2[j] != '\0'; j++) {
        result[i + j] = str2[j];
    }
    
    // Add null terminator at the end of the concatenated string
    result[i + j] = '\0';

    printf("Concatenated string: %s\n", result);

    return 0;
}
