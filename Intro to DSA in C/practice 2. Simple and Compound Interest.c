#include <stdio.h>
#include <stdlib.h>
#include <math.h>  

int main() {
    int choice;
    printf("1. To calculate Simple Interest \n 2. To calculate Compound Interest \n Enter a choice:");
    scanf("%d", &choice);  

    if (choice == 1) {
        double principal, roi, time;
        printf("Enter principal:");
        scanf("%lf", &principal);
        printf("Enter rate of interest:");
        scanf("%lf", &roi);
        printf("Enter time:");
        scanf("%lf", &time);
        double simple_interest = (principal * roi * time) / 100;
        double amount = principal + simple_interest;
        printf("The simple interest is: %lf\n", simple_interest);
        printf("The Amount is: %lf\n", amount);
    } else if (choice == 2) {
        double principal, roi, time;
        printf("Enter principal:");
        scanf("%lf", &principal);
        printf("Enter rate of interest:");
        scanf("%lf", &roi);
        printf("Enter time:");
        scanf("%lf", &time);
        double compound_interest = principal * (pow(1 + roi / 100, time));  // Use the pow function here
        double amount = principal + compound_interest;
        printf("The compound interest is: %lf\n", compound_interest);
        printf("The Amount is: %lf\n", amount);
    } else {
        printf("Invalid choice, Enter 1 or 2");
    }

    return 0;
}
