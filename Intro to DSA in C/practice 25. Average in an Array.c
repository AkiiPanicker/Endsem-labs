#include <stdio.h>
int main()
{
    int size, i;
    printf("Enter size of the array: ");
    scanf("%d",&size);
    int arr[size];
    printf("Enter array elements\n");
    for(i=0;i<size;i++)
    scanf("%d",&arr[i]);
    int sum=0,avg;
    for(i=0;i<size;i++)
    sum+=arr[i];
    printf("Sum of the array is: %d \n",sum);
    avg=sum/size;
    printf("Average of the array is: %d",avg);
}
