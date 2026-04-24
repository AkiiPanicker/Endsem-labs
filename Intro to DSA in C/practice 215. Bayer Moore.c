#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

void bad_char_heuristic(char *pattern, int m, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

void boyer_moore_search(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int badChar[NO_OF_CHARS];

    bad_char_heuristic(pattern, m, badChar);

    int s = 0;  // s is the shift of the pattern over the text
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        
        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badChar[(int)text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[(int)text[s + j]]);
        }
    }
}

int main() {
    char text[] = "ABAAABCDABCABCDABDE";
    char pattern[] = "ABCD";
    
    boyer_moore_search(text, pattern);

    return 0;
}
