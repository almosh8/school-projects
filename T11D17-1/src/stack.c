#include "stack.h"

#include <stdlib.h>

stack* init() {
    stack* s = (stack*)malloc(sizeof(stack));
    if (s == NULL) {
        return NULL;
    }
    s->data = (int*)malloc(sizeof(int) * 10);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    s->size = 10;
    s->top = -1;
    return s;
}

int push(stack* stack, int value) {
    if (stack->top == stack->size - 1) {
        int* new_data = (int*)realloc(stack->data, sizeof(int) * (stack->size * 2));
        if (new_data == NULL) {
            return FAIL;
        }
        stack->data = new_data;
        stack->size *= 2;
    }
    stack->data[++stack->top] = value;
    return SUCCESS;
}

int pop(stack* stack, int* value) {
    if (stack->top == -1) {
        return FAIL;
    }
    *value = stack->data[stack->top--];
    return SUCCESS;
}

void destroy(stack* stack) {
    free(stack->data);
    free(stack);
}