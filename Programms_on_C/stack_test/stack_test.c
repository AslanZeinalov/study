// stack_test.c (значительно изменен)
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Helper function to print test results
void print_test_result(const char *test_name, Result actual_result, Result expected_result,
                       int actual_value, int expected_value) {
    printf("Test: %s\n", test_name);
    printf("  Expected Result: %s\n", (expected_result == SUCCESS) ? "SUCCESS" : "FAIL");
    printf("  Actual Result:   %s\n", (actual_result == SUCCESS) ? "SUCCESS" : "FAIL");

    if (expected_value != -999) { // -999 is a sentinel value for no expected value
        printf("  Expected Value:  %d\n", expected_value);
        printf("  Actual Value:    %d\n", actual_value);
    }

    if (actual_result == expected_result && (expected_value == -999 || actual_value == expected_value)) {
        printf("  Result: PASS\n");
    } else {
        printf("  Result: FAIL\n");
    }
    printf("\n");
}


int main() {
    Stack stack;
    int capacity = 3;
    Result result;
    int popped_value;

    // Initialize the stack
    printf("--- Initialize Stack Test ---\n");
    result = init(&stack, capacity);
    print_test_result("init", result, SUCCESS, -999, -999); // No value to check

    // Test push
    printf("--- Push Tests ---\n");
    result = push(&stack, 10);
    print_test_result("push 10", result, SUCCESS, -999, -999);

    result = push(&stack, 20);
    print_test_result("push 20", result, SUCCESS, -999, -999);

    result = push(&stack, 30);
    print_test_result("push 30", result, SUCCESS, -999, -999);

    // Test stack overflow
    result = push(&stack, 40);
    print_test_result("push 40 (overflow)", result, FAIL, -999, -999);

    // Test pop
    printf("--- Pop Tests ---\n");
    result = pop(&stack, &popped_value);
    print_test_result("pop (1)", result, SUCCESS, popped_value, 30);

    result = pop(&stack, &popped_value);
    print_test_result("pop (2)", result, SUCCESS, popped_value, 20);

    result = pop(&stack, &popped_value);
    print_test_result("pop (3)", result, SUCCESS, popped_value, 10);

    // Test stack underflow
    result = pop(&stack, &popped_value);
    print_test_result("pop (underflow)", result, FAIL, -999, -999); // No specific value

    // Destroy the stack
    printf("--- Destroy Stack Test ---\n");
    result = destroy(&stack);
    print_test_result("destroy", result, SUCCESS, -999, -999); // No value to check

    return 0;
}
