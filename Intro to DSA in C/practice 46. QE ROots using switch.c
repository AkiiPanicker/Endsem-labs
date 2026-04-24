
#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    printf("Enter the coefficients of the quadratic equation [a, b, c]: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    double discriminant = b * b - 4 * a * c;

    int check_disc = (discriminant > 0) ? 1 : ((discriminant == 0) ? 0 : -1);

    switch (check_disc) {
        case 1:
            printf("Two real and distinct roots:\n");
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            printf("Root 1 = %.2lf\n", root1);
            printf("Root 2 = %.2lf\n", root2);
            break;
        case 0:
            printf("One real root:\n");
            double root = -b / (2 * a);
            printf("Root = %.2lf\n", root);
            break;
        case -1:
            printf("Complex roots:\n");
            double realPart = -b / (2 * a);
            double imaginaryPart = sqrt(-discriminant) / (2 * a);
            printf("Root 1 = %.2lf + %.2lfi\n", realPart, imaginaryPart);
            printf("Root 2 = %.2lf - %.2lfi\n", realPart, imaginaryPart);
            break;
    }

    return 0;
}
