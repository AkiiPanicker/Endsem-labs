#include <stdio.h>

int isSubsetSum(int arr[], int n, int sum) {
    if (sum == 0) return 1;  
    if (n == 0) return 0;    

    if (arr[n - 1] > sum) {
        return isSubsetSum(arr, n - 1, sum);
    }

    return isSubsetSum(arr, n - 1, sum) || 
           isSubsetSum(arr, n - 1, sum - arr[n - 1]);
}

int canPartition(int arr[], int n) {
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    if (sum % 2 != 0) {
        return 0;
    }

    return isSubsetSum(arr, n, sum / 2);
}

int main() {
    int n;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (canPartition(arr, n)) {
        printf("Yes, the array can be partitioned into two subsets with equal sum.\n");
    } else {
        printf("No, the array cannot be partitioned into two subsets with equal sum.\n");
    }

    return 0;
}
