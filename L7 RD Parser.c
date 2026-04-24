/*
Program → main() { declarations assign_stat }

declarations → data-type identifier-list ; declarations | ε

data-type → int | char

identifier-list → id | id , identifier-list

assign_stat → id = id ; | id = num ;*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[1000];
int pos =0, row =1, col =1;

void error(char *expected) {
    printf("Error at Row %d, Col %d: Expected '%s', found '%c'\n", row, col, expected, input[pos]);
    exit(1);
}

void match(char *t) {
    int len = strlen(t);
    if (strncmp(&input[pos], t, len) == 0) {
        for(int j=0; j<len; j++) {
            if(input[pos] == '\n') { 
                row++; 
                col = 1; 
            }
            else { 
                col++; 
            }
            pos++;
        }
        // Skip whitespace/newlines after a match
        while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
            if(input[pos] == '\n') { 
                row++; 
                col = 1; 
            }
            else { 
                col++; 
            }
            pos++;
        }
    } else {
        error(t);
    }
}
void Program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();

void Program(){
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    match("}");
    printf("Parsing successful \n");

}

void declarations(){
    if(strncmp(&input[pos], "int",3)==0 || strncmp(&input[pos],"char",4)==0){
        data_type();
        identifier_list();
        match(";");
        declarations();
    
    }
}

void data_type() {
    if (strncmp(&input[pos], "int", 3) == 0) match("int");
    else if (strncmp(&input[pos], "char", 4) == 0) match("char");
    else error("int or char");
}

void identifier_list(){
    match("id");
    if(input[pos]==','){
        match(",");
        identifier_list();
    }
}

void assign_stat(){
    match("id");
    match("=");
    if(strncmp(&input[pos],"id",2)==0){
        match("id");
    }
    else if(input[pos] > '0' && input[pos]<='9'){
        match("num");
    }
    else{
        error("id or num");
    }
    match(";");
}

int main(){
    printf("Enter Progam: \n");
    char line[100];
    while(fgets(line,sizeof(line),stdin)) strcat(input,line);
    Program();
    return 0;
}