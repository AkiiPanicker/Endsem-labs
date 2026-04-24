#include <stdio.h>
#include <string.h>

void stringmatch(char pattern[], char string[]) {
    int n = strlen(string); 
    int m = strlen(pattern); 

    for (int i = 0; i <= n - m; i++) { 
        int j;
        for (j = 0; j < m; j++) { 
            if (string[i + j] != pattern[j]) {
                break;  
            }
        }
        if (j == m) {  
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    char string[100], pattern[100];

    printf("Enter the main string: ");
    scanf("%s", string);
    printf("Enter the pattern to search: ");
    scanf("%s", pattern);

    stringmatch(pattern, string);  

    return 0;
}
