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
#include <string.h>
//stack type definition 
typedef struct Stack {
    char** symbols;
    int top;
} Stack;


//function declarations
Stack* createStack();
void push(Stack* stack, char* str);
char* pop(Stack* stack);
char* printStack(Stack* stack);
int reduce(Stack* stack);
void removeWhitespace(Stack* stack);

//program constants
const int REDUCTION_MATCHED = 0;
const int NO_REDUCTION_MATCHED = 1;

int main() {
    ///get user input
    char buffer[100];
    int index = 0;

    printf("Enter an Expression: \n");
    fgets(buffer, sizeof(buffer), stdin);

    //create the stack
    Stack* stack = createStack();

    //shift-reduce cycle
    char temp[2];
    while(buffer[index]) {
        //SHIFT CYCLE
        //turn character into a string
        temp[0] = buffer[index];
        temp[1] = '\0';
        push(stack, temp);
        printf("Shift: %s", printStack(stack));

        //REDUCE CYCLE
        while(reduce(stack) == REDUCTION_MATCHED){
            printf("Reduce: %s", printStack(stack));
        }

        index++;
    }
    return 0;
}

Stack* createStack() {
    //allocate memory for the stack struct
    Stack* stack = (Stack*) malloc(sizeof(Stack));

    //allocate memory for the stack 2d array of symbols
    stack -> symbols = (char**) malloc(100 * sizeof(char*));
    for(int i = 0; i<100; i++) {
        stack -> symbols[i] = (char*) calloc(10, sizeof(char));
    }

    //initialize top to be -1
    stack -> top = -1;
    
    return stack;
}

char* printStack(Stack* stack) {
    char* returnstr = "";
    for(int i = 0; i<= stack -> top; i++) {
        strcat(returnstr, stack -> symbols[i]);
        strcat(returnstr, " ");
    }

    strcat(returnstr, "\n");
    return returnstr;
}

void push(Stack* stack, char* str) {
    //condition added to ignore whitespaces
    if(str != " ") {
        stack -> symbols[++stack -> top] = str;
    }
}

char* pop(Stack* stack) {
    int temp = stack -> top;
    stack -> top--;
    return stack -> symbols[temp];
}

/*
    This function goes through the rules, and if a rule applies, it pops symbols from 
    the stack, replaces them with LHS and returns REDUCTION_MATCHED, otherwise, it returns
    NO_REDUCTION_MATCHED
*/
int reduce(Stack* stack) {
        //RULE 1: E -> E + E
        if(stack -> top >= 2 &&
          (stack -> symbols[stack -> top] == "E") &&
          (stack -> symbols[stack -> top - 1] == "+") &&
          (stack -> symbols[stack -> top - 2] == "E")) {
            //remove the symbols from the stack
            pop(stack);
            pop(stack);
            pop(stack);

            //replace them with the LHS of the rule
            push(stack, "E");
            return REDUCTION_MATCHED;
        } 
        //RULE 2: E -> E * E
        else if(stack -> top >= 2 &&
          (stack -> symbols[stack -> top] == "E") &&
          (stack -> symbols[stack -> top - 1] == "*") &&
          (stack -> symbols[stack -> top - 2] == "E")) {
            //remove the symbols from the stack
            pop(stack);
            pop(stack);
            pop(stack);

            //replace them wth the LHS of the rule
            push(stack, "E");
            return REDUCTION_MATCHED;
        }
        //RULE 3: E -> id
        else if(stack -> top >= 0 &&
        (stack -> symbols[stack -> top][0] >= 'a') &&
        (stack -> symbols[stack -> top][0] <= 'z')) {
            //remove the symbols from the stack
            pop(stack);

            //replace them with the LHS of the rule
            push(stack, "E");
            return REDUCTION_MATCHED;
        }
        //RULE 4: E -> (E)
        else if(stack -> top >= 2 && 
               (stack -> symbols[stack -> top] == ")") &&
               (stack -> symbols[stack -> top - 1] == "E") &&
               (stack -> symbols[stack -> top - 2] == "(")) {
                    //remove the symbols from the stack
                    pop(stack);
                    pop(stack);
                    pop(stack);

                    //replace them with the LHS of the rule
                    push(stack, "E");
                    return REDUCTION_MATCHED;
        }
    
    return NO_REDUCTION_MATCHED;
}
