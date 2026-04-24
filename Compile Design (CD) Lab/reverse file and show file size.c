#include <stdio.h>

int main(int c, char *v[]) {
    FILE *f1 = fopen(v[1], "r"), *f2 = fopen(v[2], "w");
    fseek(f1, 0, 2);
    long size = ftell(f1);

    for (long i = size - 1; i >= 0; i--) {
        fseek(f1, i, 0);
        fputc(fgetc(f1), f2);
    }

    fclose(f1); fclose(f2);
    printf("Size=%ld bytes\n", size);
}