#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack {
    int *array;
    int top, maxSize, size;
} Stack;

Stack *newStack(int maxSize);
bool isFull(Stack *Stack);
bool isEmpty(Stack *Stack);
void push(int valor, Stack *Stack);
int pop(Stack *Stack);
void display(Stack *Stack);

int main() {
    Stack *Stack = newStack(15);
    for(int i = 0; i < 10; i++)
        push(i, Stack);
    for(int i = 0; i < 3; i++)
        pop(Stack);
    display(Stack);
    return 0;
}

Stack *newStack(int maxSize) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->array = (int *) malloc(maxSize * sizeof(int));
    stack->top = -1;
    stack->maxSize = maxSize;
    stack->size = 0;
    return stack;
}

bool isFull(Stack *Stack) {
    return Stack->size == Stack->maxSize;
}

bool isEmpty(Stack *Stack) {
    return Stack->size == 0;
}

void push(int valor, Stack *Stack) {
    if(!isFull(Stack)) {
        Stack->array[++Stack->top] = valor;
        Stack->size++;
    } else {
        printf("Stack is full!");
    }
}

int pop(Stack *Stack) {
    if(!isEmpty(Stack)) {
        Stack->top--;
        Stack->size--;
    } else {
        printf("Stack is empty!");
    }
}

void display(Stack *Stack){
    if(!isEmpty(Stack)) {
        for(int i = 0; i <= Stack->top; i++)
            printf("%d ", i);
        printf("\n");
    } else {
        printf("Stack is empty!");
    }
}