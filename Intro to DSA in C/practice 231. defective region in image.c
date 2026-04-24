#include <stdio.h>

#define N 8  // Size of the image (Assume 8x8 for simplicity)

// Sample Image with 1s (Non-defective) and 0s (Defective)
int image[N][N] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// Function to check if all elements in the submatrix are the same
int isUniform(int x, int y, int size, int value) {
    for (int i = x; i < x + size; i++)
        for (int j = y; j < y + size; j++)
            if (image[i][j] != value)
                return 0;
    return 1;
}

// Function to find defective regions using divide and conquer
void findDefectiveRegion(int x, int y, int size) {
    if (size == 0)
        return;

    // If the entire region is defective (all 0s)
    if (isUniform(x, y, size, 0)) {
        printf("Defective region found at (%d, %d) with size %d x %d\n", x, y, size, size);
        return;
    }

    // If the entire region is non-defective (all 1s), ignore it
    if (isUniform(x, y, size, 1))
        return;

    // Divide into four quadrants
    int half = size / 2;
    findDefectiveRegion(x, y, half);         // Top-left
    findDefectiveRegion(x, y + half, half);  // Top-right
    findDefectiveRegion(x + half, y, half);  // Bottom-left
    findDefectiveRegion(x + half, y + half, half); // Bottom-right
}

int main() {
    printf("Finding defective regions...\n");
    findDefectiveRegion(0, 0, N);
    return 0;
}
