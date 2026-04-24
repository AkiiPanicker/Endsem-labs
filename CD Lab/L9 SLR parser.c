/*
state 0 : i am at beggining expecting an expression
state 5 : i just saw an id I am waiting to see if next char is + or * or end of string

you see id push it go to state 5

If you input id + id:S
tep 1: Start at State 0. Input is id. The table says: "Shift id and go to State 5."S
tep 2: In State 5, the next input is +. The table says: "I can't shift a + after an id, so Reduce." You turn id into F.
Step 3: You are back at State 0 (the state below the $F$ you just created). You look up the "GoTo" for F at State 0. It tells you to go to State 3.
Step 4: In State 3, you reduce F to T.
Step 5: In State 0, you look up GoTo for T. It tells you to go to State 2.*/

/*
/*
Grammar:
1. E -> E+T
2. E -> T
3. T -> T*F
4. T -> F
5. F -> (E)
6. F -> id
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

void print_stack() {
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
}

int main() {
    char input[100], action[20];
    printf("Enter input string (e.g., id+id*id$): ");
    scanf("%s", input);

    push('$');
    push('0'); // Starts the parser in State 0, which is the "Ready to begin" state.

    printf("\nStack\t\tInput\t\tAction\n");

    int i=0;
    while(1){
        print_stack();
        printf("\t\t%s\t\t", input+i);

        char state = stack[top]; // Current State (always top of stack)
        char symbol = input[i]; // Current lookahead symbol from input

        /*If we are in State 0 and see an i (the start of id):

        Push 'i': Put the symbol on the stack.

        Push '5': Put the state number on the stack to remember we are in State 5.

        i += 2: We consume the two characters i and d by moving the input pointer forward.*/

        if(state == '0' && symbol == 'i'){
            push('i');
            push('5');
            i+=2;
            printf('Shift s5\n');
        }

        /*
        State 5's only job is to turn an id into a Factor.

        pop(); pop();: We remove the state number ('5') and the symbol ('i').

        push('F'): We replace them with the non-terminal F.*/
        else if(state == '5'){
            pop();
            pop();
            push('F');
            printf("Reduce F->id \n");
        }

        /*After a reduction, the stack top is a symbol (F), not a state number.

        The parser looks underneath the F (which is State 0) and says:
        "If I'm in State 0 and I see an F, the table tells me to move to State 3."*/

        else if(state == '0' && stack[top] == 'F'){
            push('3');
            printf("Goto 3 \n");
        }

        //Reduce F to T and T to E
        else if(stack[top]=='F' || (state == '3')){
            pop();
            pop();
            push('T');
            printf("Reduce T->F\n");
        }

        //Same stuff done prev  reducing T to E
        else if (state == '0' && stack[top] == 'T') {
            push('2');
            printf("GOTO 2\n");
        } 
        else if (state == '2' && symbol == '$') {
            pop(); 
            pop(); 
            push('E');
            printf("Reduce E->T\n");

        }

        else if(state == '0' && stack[top] == 'E'){
            push('1');
            printf("GOTO 1\n");
        }

        //If the parser reaches State 1 and the input is empty ($), 
        //the string is mathematically valid according to your grammar. The loop breaks, and the program finishes.
        else if(state == '1' && symbol == '$'){
            printf("Accept \n");
            break;
        }

        else {
            printf("Error/Unsupported Step\n");
            break;
        }
    }
    return 0;
}