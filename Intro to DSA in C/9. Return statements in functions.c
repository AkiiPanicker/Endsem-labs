#include <stdio.h>
#include <stdlib.h>

double cube(double num) {
    double result = num * num * num;
    return result;
}

int main() {
    double input_num;
    printf("Enter a number: ");
    scanf("%lf", &input_num);

    printf("Answer: %f", cube(input_num));
    return 0;
}
