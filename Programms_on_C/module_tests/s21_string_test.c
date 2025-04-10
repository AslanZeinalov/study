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

void s21_strcmp_test() {
    const char *str1_inputs[] = {
        "Hello", "Hello", "World", "", "Hello", "Hello!", "Short",
        "A very long string", "SamePrefix1", "", "NonEmpty"
    };

    const char *str2_inputs[] = {
        "Hello", "World", "Hello", "", "Hello!", "Hello", "A very long string",
        "Short", "SamePrefix2", "NonEmpty", ""
    };

    int expected_results[] = {
        0, -15, 15, 0, -1, 1, 18, -18, -1, -78, 78
    };

    int num_tests = sizeof(str1_inputs) / sizeof(str1_inputs[0]);

    for (int i = 0; i < num_tests; ++i) {
        int actual = s21_strcmp(str1_inputs[i], str2_inputs[i]);

        printf("Strcmp Test %d:\n", i + 1);
        printf("  str1: \"%s\"\n", str1_inputs[i]);
        printf("  str2: \"%s\"\n", str2_inputs[i]);
        printf("  Expected: %d\n", expected_results[i]);
        printf("  Actual: %d\n", actual);

        if ((actual > 0 && expected_results[i] > 0) ||
            (actual < 0 && expected_results[i] < 0) ||
            (actual == 0 && expected_results[i] == 0)) {
            printf("  Result: %s\n\n", SUCCESS);
        } else {
            printf("  Result: %s\n\n", FAIL);
        }
    }
}

int main() {
    s21_strlen_test();
    s21_strcmp_test();
    return 0;
}
