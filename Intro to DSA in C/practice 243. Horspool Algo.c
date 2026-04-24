#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 256 // ASCII characters

int shiftTable[MAX];

// Preprocess: Create the shift table
void buildShiftTable(char pattern[], int m) {
    for (int i = 0; i < MAX; i++)
        shiftTable[i] = m;  // Default shift = pattern length

    for (int i = 0; i < m - 1; i++)
        shiftTable[(unsigned char)pattern[i]] = m - 1 - i;
}

// Horspool's search function
int horspoolSearch(char text[], char pattern[], int* comparisons, int* foundAt) {
    int n = strlen(text);
    int m = strlen(pattern);
    *comparisons = 0;

    int i = m - 1;

    while (i < n) {
        int k = 0;

        // Compare pattern right to left
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
            (*comparisons)++;
        }

        // Full match found
        if (k == m) {
            *foundAt = i - m + 1;
            return 1; // Found
        }

        // Count the comparison even if first character fails
        if (k == 0) (*comparisons)++;

        i += shiftTable[(unsigned char)text[i]];
    }

    return 0; // Not found
}

int main() {
    char text[1000], pattern[100];
    int comparisons = 0, foundAt = -1;

    printf("Enter the text: ");
    gets(text);  // For simplicity; use fgets in real code.

    printf("Enter the pattern: ");
    gets(pattern);

    buildShiftTable(pattern, strlen(pattern));

    if (horspoolSearch(text, pattern, &comparisons, &foundAt)) {
        printf("\n✅ Pattern found at index %d", foundAt);
        printf("\n🔢 Number of key comparisons (successful): %d\n", comparisons);
    } else {
        printf("\n❌ Pattern not found.");
        printf("\n🔢 Number of key comparisons (unsuccessful): %d\n", comparisons);
    }

    return 0;
}
