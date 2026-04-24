#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Angels and Demons";
    char str2[50]; // Assuming a maximum length for the strings
    
    for (int j = 0; j < strlen(str1); j++) {
        str2[j] = str1[j];
    }
    
    str2[strlen(str1)] = '\0'; // Null-terminate the copied string
    
    printf("%s \n", str2); // Print the copied string
    
    return 0;
}
