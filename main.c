/*
    This is a simple shift-reduce compiler that accepts the following rules:
    E -> E + E
    E -> E * E
    E -> id 
    E -> (E)

    This compiler should ignore all whitespace

    How it will be implemented:
        1- Create a stack that will hold the symbols
        2- Create a shift function that adds symbols to the stack
        3- Create a reduce function that removes symbols from the stack and replaces that with the left hand side
*/
//including necessary libraries
#include <stdio.h>
#include <stdlib.h>

//stack type definition 
typedef struct Stack {
    char** symbols;
    int top;
} Stack;


//function declarations
Stack* createStack();
void push(Stack* stack, char* str);
char* pop(Stack* stack);
void reduce(Stack* stack);

int main() {

    return 0;
}

Stack* createStack() {
    //allocate memory for the stack struct
    Stack* stack = (Stack*) malloc(sizeof(Stack));

    //allocate memory for the stack 2d array of symbols
    stack -> symbols = (char**) malloc(100 * sizeof(char*));
    for(int i = 0; i<100; i++) {
        stack -> symbols[i] = (char*) malloc(10 * sizeof(char));
    }

    //initialize top to be -1
    stack -> top = -1;
    
    return stack;
}

void push(Stack* stack, char* str) {
    stack -> symbols[++stack -> top] = str;
}

char* pop(Stack* stack) {
    int temp = stack -> top;
    stack -> top--;
    return stack -> symbols[temp];
}