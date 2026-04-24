#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index;
    int rank[2];  // Ranks for sorting
} Suffix;

// Comparator function for qsort
int cmp(const void *a, const void *b) {
    Suffix *s1 = (Suffix *)a;
    Suffix *s2 = (Suffix *)b;
    return (s1->rank[0] == s2->rank[0]) ? 
           (s1->rank[1] - s2->rank[1]) : (s1->rank[0] - s2->rank[0]);
}

// Function to build suffix array
int* buildSuffixArray(char *txt, int n) {
    Suffix *suffixes = (Suffix *)malloc(n * sizeof(Suffix));
    int *suffixArr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = (i + 1 < n) ? (txt[i + 1] - 'a') : -1;
    }

    // Sort suffixes based on first 2 characters
    qsort(suffixes, n, sizeof(Suffix), cmp);

    int *ind = (int *)malloc(n * sizeof(int)); // To store indices
    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0, prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        // Assigning new ranks
        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        // Assign next rank based on previous ranks
        for (int i = 0; i < n; i++) {
            int nextIdx = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextIdx < n) ? suffixes[ind[nextIdx]].rank[0] : -1;
        }

        // Sort again based on first k characters
        qsort(suffixes, n, sizeof(Suffix), cmp);
    }

    // Store result in suffix array
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    free(suffixes);
    free(ind);
    return suffixArr;
}

// Function to print suffix array
void printSuffixArray(int *suffixArr, int n) {
    printf("Suffix Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", suffixArr[i]);
    printf("\n");
}

// Main function
int main() {
    char txt[1000];
    printf("Enter the string: ");
    scanf("%s", txt);

    int n = strlen(txt);
    int *suffixArr = buildSuffixArray(txt, n);

    printSuffixArray(suffixArr, n);
    
    free(suffixArr);
    return 0;
}