#include <stdio.h>
#define MAX 100

void subsetsum(int arr[], int n, int index, int currsum, int target, int subset[], int subsetsize){
    if(currsum == target){
        printf("Subset Found: ");
        for(int i = 0; i < subsetsize; i++){
            printf("%d ", subset[i]); // Add space for readability
        }
        printf("\n");
        return;
    }

    if(index >= n || currsum > target){ // Fix off-by-one
        return;
    }

    // include arr[index]
    subset[subsetsize] = arr[index];
    subsetsum(arr, n, index + 1, currsum + arr[index], target, subset, subsetsize + 1);

    // exclude arr[index]
    subsetsum(arr, n, index + 1, currsum, target, subset, subsetsize);
}

int main(){
    int arr[MAX], n , target;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter target sum: ");
    scanf("%d", &target);

    int subset[MAX]; // To hold current subset
    printf("Subsets with sum %d are:\n", target);
    subsetsum(arr, n, 0, 0, target, subset, 0);

    return 0;
}
