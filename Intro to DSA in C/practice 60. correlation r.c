#include <stdio.h>
#include <math.h>

int main() {
    // Given data points (x, y)
    double x[] = {34.22, 39.87, 41.85, 43.23, 40.06, 53.29, 53.29, 54.14, 49.12, 40.71, 55.15};
    double y[] = {102.43, 100.93, 97.43, 97.81, 98.32, 98.32, 100.71, 97.08, 91.59, 94.85, 94.65};
    int n = 11; // Number of data points (corrected to the actual number of data points)

    // Initialize sums
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;
    double sum_x_squared = 0.0;
    double sum_y_squared = 0.0;

    // Calculate sums
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x_squared += x[i] * x[i];
        sum_y_squared += y[i] * y[i];
    }

    // Calculate the correlation coefficient (r)
    double numerator = (n * sum_xy) - (sum_x * sum_y);
    double denominator1 = sqrt((n * sum_x_squared) - (sum_x * sum_x));
    double denominator2 = sqrt((n * sum_y_squared) - (sum_y * sum_y));
    double r = numerator / (denominator1 * denominator2);

    // Print the correlation coefficient
    printf("Correlation coefficient (r) = %.6lf\n", r);

    return 0;
}
