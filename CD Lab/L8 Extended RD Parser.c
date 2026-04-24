#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[5000];
int pos = 0, row = 1, col = 1;

void error(char *expected) {
    printf("\nError at Row %d, Col %d: Expected '%s', found '%c'\n", row, col, expected, input[pos]);
    exit(1);
}

void match(char *t) {
    int len = strlen(t);
    if (strncmp(&input[pos], t, len) == 0) {
        for(int j = 0; j < len; j++) {
            if(input[pos] == '\n') { row++; col = 1; }
            else { col++; }
            pos++;
        }
        while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
            if(input[pos] == '\n') { row++; col = 1; }
            else { col++; }
            pos++;
        }
    } else { error(t); }
}

// Prototypes
void Program(); void declarations(); void data_type(); void identifier_list();
void statement_list(); void statement(); void assign_stat();
void expn(); void eprime(); void simple_expn(); void seprime();
void term(); void tprime(); void factor(); void decision_stat();

void Program() {
    match("main"); match("("); match(")"); match("{");
    declarations();
    statement_list();
    match("}");
    printf("\nParsing Successful!\n");
}

void declarations() {
    if (strncmp(&input[pos], "int", 3) == 0 || strncmp(&input[pos], "char", 4) == 0) {
        data_type();
        identifier_list();
        match(";");
        declarations();
    }
}

void data_type() {
    if (strncmp(&input[pos], "int", 3) == 0) match("int");
    else if (strncmp(&input[pos], "char", 4) == 0) match("char");
}

void identifier_list() {
    match("id");
    if (input[pos] == '[') {
        match("["); match("num"); match("]");
    }
    if (input[pos] == ',') {
        match(",");
        identifier_list();
    }
}

void statement_list() {
    if (input[pos] != '}' && input[pos] != '\0') {
        statement();
        statement_list();
    }
}

void statement() {
    if (strncmp(&input[pos], "if", 2) == 0) decision_stat();
    else {
        assign_stat();
        match(";");
    }
}

void assign_stat() {
    match("id"); match("=");
    expn();
}

void expn() {
    simple_expn();
    eprime();
}

void eprime() {
    char *relops[] = {"==", "!=", "<=", ">=", "<", ">"};
    for(int i=0; i<6; i++) {
        if(strncmp(&input[pos], relops[i], strlen(relops[i])) == 0) {
            match(relops[i]);
            simple_expn();
            return;
        }
    }
}

void simple_expn() {
    term();
    seprime();
}

void seprime() {
    if (input[pos] == '+' || input[pos] == '-') {
        match(input[pos] == '+' ? "+" : "-");
        term();
        seprime();
    }
}

void term() {
    factor();
    tprime();
}

void tprime() {
    if (input[pos] == '*' || input[pos] == '/' || input[pos] == '%') {
        if(input[pos] == '*') match("*");
        else if(input[pos] == '/') match("/");
        else match("%");
        factor();
        tprime();
    }
}

void factor() {
    if (strncmp(&input[pos], "id", 2) == 0) match("id");
    else if (input[pos] >= '0' && input[pos] <= '9') match("num");
    else error("id or num");
}

void decision_stat() {
    match("if"); match("(");
    expn();
    match(")"); match("{");
    statement_list();
    match("}");
}

int main() {
    printf("Enter code (End with Ctrl+D):\n");
    char line[256];
    while(fgets(line, sizeof(line), stdin)) strcat(input, line);
    
    // Initial skip of whitespace
    int start = 0;
    while(input[start] == ' ' || input[start] == '\n') start++;
    pos = start;

    Program();
    return 0;
}