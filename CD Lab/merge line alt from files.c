#include <stdio.h>

int main(int c, char *v[]) {
    FILE *f1 = fopen(v[1], "r"), *f2 = fopen(v[2], "r"), *f3 = fopen(v[3], "w");
    char a[100], b[100];

    while (fgets(a, 100, f1) || fgets(b, 100, f2)) {
        if (!feof(f1)) fputs(a, f3);
        if (!feof(f2)) fputs(b, f3);
    }

    fclose(f1); fclose(f2); fclose(f3);
}