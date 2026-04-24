#include <stdio.h>
typedef struct {
    double real;
    double imag;
} Complex;

Complex multiplyComplex(Complex num1, Complex num2) {
    Complex result;
    result.real = (num1.real * num2.real) - (num1.imag * num2.imag);
    result.imag = (num1.real * num2.imag) + (num1.imag * num2.real);
    return result;
}
int main() {
    Complex num1, num2;

    printf("Enter the real and imaginary parts of the first complex number: ");
    scanf("%lf %lf", &num1.real, &num1.imag);

    printf("Enter the real and imaginary parts of the second complex number: ");
    scanf("%lf %lf", &num2.real, &num2.imag);

    Complex product = multiplyComplex(num1, num2);

    if (product.imag >= 0) {
        printf("Product: %.2f + %.2fi\n", product.real, product.imag);
    } else {
        printf("Product: %.2f - %.2fi\n", product.real, -product.imag);
    }

    return 0;
}

