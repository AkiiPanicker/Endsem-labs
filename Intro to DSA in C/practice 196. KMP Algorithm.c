#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute LPS (Longest Prefix Suffix) array
void computeLPSArray(char* pattern, int m, int* lps) {
    int len = 0, i = 1;
    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Searching Algorithm
void KMPSearch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    int* lps = (int*)malloc(m * sizeof(int)); //  Dynamic allocation
    computeLPSArray(pattern, m, lps);

    int i = 0, j = 0; // i → text, j → pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++, j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) 
                j = lps[j - 1];
            else 
                i++;
        }
    }

    free(lps); // Free allocated memory
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pattern);

    KMPSearch(text, pattern);
    return 0;
}
