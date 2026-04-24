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

    int pos, element;
    printf("Enter index where element is to be inserted: ");
    scanf("%d", &pos);
    printf("Enter element to be inserted: ");
    scanf("%d", &element);

    for (int j = n; j >= pos; j--) {
        arr[j] = arr[j - 1];
    }
    
    arr[pos - 1] = element;
    n = n + 1;

    printf("Updated array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
