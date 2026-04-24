#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int count_triangular_numbers(int a, int b) {
    int count = 0;
    for (int n = 1; ; n++) {
        int triangular_number = n * (n + 1) / 2;
        if (triangular_number > b) break;
        if (triangular_number >= a && triangular_number <= b) count++;
    }
    return count;
}

int count_divisible_by_2_3_5(int a, int b) {
    int count = 0;
    for (int i = a; i <= b; i++) {
        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0) count++;
    }
    return count;
}

int count_set_bits(int n) {
    int count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

void query_type_1(int a, int b, int c) {
    int n = 1;
    while (true) {
        int result = a * n * n + b * n + c;
        if (!is_prime(result)) {
            printf("Query 1: Smallest non-prime number for a=%d, b=%d, c=%d is %d\n", a, b, c, result);
            break;
        }
        n++;
    }
}

void query_type_2(int a, int b) {
    int count = count_triangular_numbers(a, b);
    printf("Query 2: Count of triangular numbers in the range [%d, %d] is %d\n", a, b, count);
}

void query_type_3(int a, int b) {
    int count = count_divisible_by_2_3_5(a, b);
    printf("Query 3: Count of numbers divisible by 2, 3, or 5 in the range [%d, %d] is %d\n", a, b, count);
}

void query_type_4(int a, int b) {
    // Query type 4: Find 2 smallest numbers s1 and s2 with minimum and maximum set bits
    int s1 = a, s2 = a + 1;
    int min_bits1 = count_set_bits(a), min_bits2 = count_set_bits(a + 1);
    int max_bits1 = count_set_bits(a), max_bits2 = count_set_bits(a + 1);
    
    for (int i = a; i <= b; i++) {
        int bits = count_set_bits(i);
        
        // Update minimums
        if (bits < min_bits1) {
            s2 = s1;
            min_bits2 = min_bits1;
            s1 = i;
            min_bits1 = bits;
        } else if (bits < min_bits2) {
            s2 = i;
            min_bits2 = bits;
        }
        
        // Update maximums
        if (bits > max_bits1) {
            s2 = s1;
            max_bits2 = max_bits1;
            s1 = i;
            max_bits1 = bits;
        } else if (bits > max_bits2) {
            s2 = i;
            max_bits2 = bits;
        }
    }
    
    printf("Query 4: Smallest number with minimum set bits (s1): %d\n", s1);
    printf("Query 4: Smallest number with maximum set bits (s2): %d\n", s2);
}
int main() {
    int q;
    printf("Enter the number of queries (q): ");
    scanf("%d", &q);

    while (q--) {
        int query_type;
        printf("Enter query type (1, 2, 3, or 4): ");
        scanf("%d", &query_type);

        if (query_type == 1) {
            int a, b, c;
            printf("Enter values a, b, and c: ");
            scanf("%d %d %d", &a, &b, &c);
            query_type_1(a, b, c);
        } else if (query_type == 2) {
            int a, b;
            printf("Enter the range [a, b]: ");
            scanf("%d %d", &a, &b);
            query_type_2(a, b);
        } else if (query_type == 3) {
            int a, b;
            printf("Enter the range [a, b]: ");
            scanf("%d %d", &a, &b);
            query_type_3(a, b);
        } else if (query_type == 4) {
            int a, b;
            printf("Enter the range [a, b]: ");
            scanf("%d %d", &a, &b);
            query_type_4_updated(a, b);  
        }
    }

    return 0;
}
