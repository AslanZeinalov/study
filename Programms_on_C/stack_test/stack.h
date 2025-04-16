#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;

typedef enum {
    SUCCESS,
    FAIL
} Result;

Result init(Stack *stack, int capacity);
Result push(Stack *stack, int value);
Result pop(Stack *stack, int *value);
Result destroy(Stack *stack);
bool isEmpty(const Stack *stack);
bool isFull(const Stack *stack);

#endif // STACK_H
