#include <stdio.h>

int main() {
    int n; // The size of the square grid
    printf("Enter the size of the square grid: ");
    scanf("%d", &n);

    int grid[n][n]; // Create a square grid of size n x n
    int num = 1;    // Initialize the starting number

    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (num <= n * n) {
        // Move from left to right along the top row
        for (int i = left; i <= right; i++) {
            grid[top][i] = num++;
        }
        top++;

        // Move from top to bottom along the rightmost column
        for (int i = top; i <= bottom; i++) {
            grid[i][right] = num++;
        }
        right--;

        // Move from right to left along the bottom row
        for (int i = right; i >= left; i--) {
            grid[bottom][i] = num++;
        }
        bottom--;

        // Move from bottom to top along the leftmost column
        for (int i = bottom; i >= top; i--) {
            grid[i][left] = num++;
        }
        left++;
    }

    // Print the grid
    printf("Generated Grid:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}
