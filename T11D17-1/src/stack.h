#ifndef STACK_H
#define STACK_H

#define SUCCESS 0
#define FAIL 1

typedef struct {
    int* data;
    int size;
    int top;
} stack;

stack* init();
int push(stack* stack, int value);
int pop(stack* stack, int* value);
void destroy(stack* stack);

#endif