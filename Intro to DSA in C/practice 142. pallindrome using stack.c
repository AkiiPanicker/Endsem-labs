#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100 // Maximum size of the stack

typedef struct {
    char arr[MAX];
    int top;
} Stack;

// Function to initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, char value) {
    if (stack->top < MAX - 1) {
        stack->arr[++stack->top] = value;
    } else {
        printf("Stack Overflow: Unable to push %c\n", value);
    }
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->top--];
    } else {
        printf("Stack Underflow: Unable to pop\n");
        return '\0'; // Return null character if stack is empty
    }
}

// Function to check if a string is a palindrome using stack
bool isPalindrome(const char* str) {
    Stack stack;
    initStack(&stack);
    
    int length = strlen(str);
    
    // Push all characters onto the stack
    for (int i = 0; i < length; i++) {
        push(&stack, str[i]);
    }

    // Compare characters from the stack with the original string
    for (int i = 0; i < length; i++) {
        if (pop(&stack) != str[i]) {
            return false; // Not a palindrome
        }
    }

    return true; // It is a palindrome
}

// Main function
int main() {
    char str[MAX];

    // Input string
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character from the input string
    str[strcspn(str, "\n")] = 0;

    // Check if the string is a palindrome
    if (isPalindrome(str)) {
        printf("'%s' is a palindrome.\n", str);
    } else {
        printf("'%s' is not a palindrome.\n", str);
    }

    return 0;
}
