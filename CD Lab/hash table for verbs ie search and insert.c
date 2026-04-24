#include <stdio.h>
#include <string.h>

#define SIZE 10
char table[SIZE][20];

int hash(char *s) {
    int h = 0;
    for (int i = 0; s[i]; i++) h += s[i];
    return h % SIZE;
}

int search(char *key) {
    int h = hash(key);
    if (strcmp(table[h], key) == 0) return h;
    return -1;
}

void insert(char *str) {
    if (search(str) != -1) return;
    int h = hash(str);
    strcpy(table[h], str);
}

int isVerb(char *w) {
    int l = strlen(w);
    return (l > 2 && (!strcmp(w+l-3,"ing") || !strcmp(w+l-2,"ed")));
}

int main() {
    char s[200], *t;
    fgets(s, 200, stdin);

    t = strtok(s, " ,.\n");
    while (t) {
        if (isVerb(t)) insert(t);
        t = strtok(NULL, " ,.\n");
    }

    for (int i = 0; i < SIZE; i++)
        if (strlen(table[i])) printf("%d: %s\n", i, table[i]);
}