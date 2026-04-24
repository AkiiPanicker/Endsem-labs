#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate Z-array
void computeZArray(char* str, int* Z, int n) {
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right)
            Z[i] = (right - i + 1 < Z[i - left]) ? right - i + 1 : Z[i - left];

        while (i + Z[i] < n && str[Z[i]] == str[i + Z[i]])
            Z[i]++;

        if (i + Z[i] - 1 > right)
            left = i, right = i + Z[i] - 1;
    }
}

// Z Algorithm for pattern searching
void ZSearch(char* text, char* pattern) {
    int n = strlen(text), m = strlen(pattern);
    int concatLen = m + n + 1;
    
    char* concat = (char*)malloc((concatLen + 1) * sizeof(char)); // Dynamic allocation
    sprintf(concat, "%s$%s", pattern, text); // Pattern + "$" + Text

    int* Z = (int*)malloc((concatLen + 1) * sizeof(int)); //  Dynamic allocation
    memset(Z, 0, (concatLen + 1) * sizeof(int));

    computeZArray(concat, Z, concatLen);

    // Print occurrences of pattern in text
    for (int i = m + 1; i < concatLen; i++) {
        if (Z[i] == m)
            printf("Pattern found at index %d\n", i - m - 1);
    }

    free(Z);
    free(concat);
}

int main() {
    char text[1000], pattern[1000];

    printf("Enter text: ");
    scanf("%s", text);
    printf("Enter pattern: ");
    scanf("%s", pattern);

    ZSearch(text, pattern);
    return 0;
}
