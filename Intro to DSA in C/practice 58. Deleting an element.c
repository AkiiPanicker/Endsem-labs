#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {
        printf("Enter element: ");
        scanf("%d", &arr[i]);
    }

    int pos;
    printf("Enter position to be deleted:");
    scanf("%d", &pos);

    if (pos < 1 || pos > n) {
        printf("Invalid position. Position should be between 1 and %d.\n", n);
    } 
    else 
    {

        for (int i = pos - 1; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }

        n = n - 1;

        printf("Updated array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", arr[i]);
        }
    }

    return 0;
}
