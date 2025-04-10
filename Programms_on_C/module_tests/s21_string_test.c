#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

#define SUCCESS "SUCCESS"
#define FAIL "FAIL"

void s21_strlen_test() {
    const char *inputs[] = {
        "Hello, world!",
        "",
        "A very long string to test the function.",
        "\n",
        "12345"
    };

    size_t expected_lengths[] = {
        13,
        0,
        38,
        1,
        5
    };

    int num_tests = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_tests; ++i) {
        const char *input = inputs[i];
        size_t expected = expected_lengths[i];
        size_t actual = s21_strlen(input);

        printf("Test %d:\n", i + 1);
        printf("  Input: \"%s\"\n", input);
        printf("  Expected: %zu\n", expected);
        printf("  Actual: %zu\n", actual);

        if (actual == expected) {
            printf("  Result: %s\n\n", SUCCESS);
        } else {
            printf("  Result: %s\n\n", FAIL);
        }
    }
}

int main() {
    s21_strlen_test();
    return 0;
}
