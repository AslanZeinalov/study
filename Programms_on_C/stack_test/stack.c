#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Result init(Stack *stack, int capacity) {
    stack->arr = (int*)malloc(capacity * sizeof(int));
    if (stack->arr == NULL) {
        return FAIL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return SUCCESS;
}

bool isEmpty(const Stack *stack) {
    return stack->top == -1;
}

bool isFull(const Stack *stack) {
    return stack->top == stack->capacity - 1;
}

Result push(Stack *stack, int value) {
    if (isFull(stack)) {
        return FAIL;
    }
    stack->arr[++stack->top] = value;
    return SUCCESS;
}

Result pop(Stack *stack, int *value) {
    if (isEmpty(stack)) {
        return FAIL;
    }
    *value = stack->arr[stack->top--];
    return SUCCESS;
}

Result destroy(Stack *stack) {
    if (stack->arr != NULL) {
        free(stack->arr);
        stack->arr = NULL;
    }
    stack->top = -1;
    stack->capacity = 0;
    return SUCCESS;
}
