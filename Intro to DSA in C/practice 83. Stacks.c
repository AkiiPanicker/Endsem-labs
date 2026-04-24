#include <stdio.h>
#include <stdlib.h>
#define N 5

int stack[N];
int top = -1;

void push(){
    int x;
    printf("Enter data: ");
    scanf("%d", &x);
    if(top == N-1){
        printf("Overflow\n");
    } else {
        top++;
        stack[top] = x;
        printf("Pushed %d onto the stack\n", x);
    }
}

void pop(){
    if(top == -1){
        printf("Underflow\n");
    } else {
        int item = stack[top];
        top--;
        printf("Popped %d from the stack\n", item);
    }
}

void peek(){
    if(top == -1){
        printf("Stack is empty\n");
    } else {
        printf("Top element: %d\n", stack[top]);
    }
}

void display(){
    if(top == -1){
        printf("Stack is empty\n");
    } else {
        printf("Stack elements: ");
        for(int i = top; i >= 0; i--){
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main(){
    int ch;
    do {
        printf("\nEnter choice: 1. Push 2. Pop 3. Peek 4. Display 0. Exit\n");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (ch != 0);
    
    return 0;
}
