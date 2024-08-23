#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int test_push() {
    stack* stack = init();
    if (stack == NULL) {
        return FAIL;
    }

    if (push(stack, 1) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (push(stack, 2) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (push(stack, 3) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }

    destroy(stack);
    return SUCCESS;
}

int test_pop() {
    stack* stack = init();
    if (stack == NULL) {
        return FAIL;
    }

    if (push(stack, 1) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (push(stack, 2) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (push(stack, 3) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }

    int value;
    if (pop(stack, &value) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (value != 3) {
        destroy(stack);
        return FAIL;
    }

    if (pop(stack, &value) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (value != 2) {
        destroy(stack);
        return FAIL;
    }

    if (pop(stack, &value) != SUCCESS) {
        destroy(stack);
        return FAIL;
    }
    if (value != 1) {
        destroy(stack);
        return FAIL;
    }

    if (pop(stack, &value) == SUCCESS) {
        destroy(stack);
        return FAIL;
    }

    destroy(stack);
    return SUCCESS;
}

int main() {
    printf("test_push: %s\n", test_push() == SUCCESS ? "ok" : "fail");
    printf("test_pop: %s\n", test_pop() == SUCCESS ? "ok" : "fail");
    return 0;
}