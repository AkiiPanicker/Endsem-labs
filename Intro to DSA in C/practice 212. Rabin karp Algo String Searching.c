#include <stdio.h>
#include <string.h>

#define d 256  // Number of characters in the input alphabet (ASCII)

void rabinKarpSearch(char *text, char *pattern, int q) {
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for text
    int h = 1;

    // Step 1: Calculate the value of h = d^(m-1) % q
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Step 2: Calculate the hash value of the pattern and the first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Step 3: Slide the pattern over the text
    for (i = 0; i <= n - m; i++) {
        // Check if the hash values match
        if (p == t) {
            // If hash values match, check for actual match
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            // If a match is found
            if (j == m) {
                printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate the hash value for the next window of text
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // If t is negative, convert it to positive
            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

int main() {
    char text[100], pattern[100];
    int q = 101;  // A prime number for hashing

    // Input the text and pattern
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;  // Remove the newline character if any

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0;  // Remove the newline character if any

    // Call the Rabin-Karp search function
    rabinKarpSearch(text, pattern, q);

    return 0;
}
