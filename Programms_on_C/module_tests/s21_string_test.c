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

void s21_strcpy_test() {
    
    char dest1[20] = "";
    char src1[] = "Hello, world!";
    char expected1[20] = "Hello, world!"; 

    s21_strcpy(dest1, src1);

    printf("Strcpy Test 1: Normal string\n");
    printf("  Input: src = \"%s\"\n", src1);
    printf("  Expected: \"%s\"\n", expected1);
    printf("  Actual:   \"%s\"\n", dest1);

    if (s21_strcmp(dest1, expected1) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    char dest2[10] = "initial";
    char src2[] = "";
    char expected2[10] = ""; 

    s21_strcpy(dest2, src2);

    printf("Strcpy Test 2: Empty string\n");
    printf("  Input: src = \"\"\n");
    printf("  Expected: \"%s\"\n", expected2);
    printf("  Actual:   \"%s\"\n", dest2);

    if (s21_strcmp(dest2, expected2) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    char dest3[20] = "";
    char src3[] = "123abc456!@#";
    char expected3[20] = "123abc456!@#";

    s21_strcpy(dest3, src3);

    printf("Strcpy Test 3: String with numbers and symbols\n");
    printf("  Input: src = \"%s\"\n", src3);
    printf("  Expected: \"%s\"\n", expected3);
    printf("  Actual:   \"%s\"\n", dest3);

    if (s21_strcmp(dest3, expected3) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    printf("Strcpy Test 4: Memory overlap\n");
    printf("  NOTE: Memory overlap behavior is undefined. Check manually if the result is acceptable.\n");

}

void s21_strcat_test() {
   
    char dest1[30] = "Hello, ";
    char src1[] = "world!";
    char expected1[30] = "Hello, world!";

    s21_strcat(dest1, src1);

    printf("Strcat Test 1: Normal concatenation\n");
    printf("  Input: dest = \"%s\", src = \"%s\"\n", "Hello, ", src1);
    printf("  Expected: \"%s\"\n", expected1);
    printf("  Actual:   \"%s\"\n", dest1);

    if (s21_strcmp(dest1, expected1) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    char dest2[20] = "";
    char src2[] = "Hello";
    char expected2[20] = "Hello";

    s21_strcat(dest2, src2);

    printf("Strcat Test 2: Concatenating to an empty string\n");
    printf("  Input: dest = \"\", src = \"%s\"\n", src2);
    printf("  Expected: \"%s\"\n", expected2);
    printf("  Actual:   \"%s\"\n", dest2);

    if (s21_strcmp(dest2, expected2) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    char dest3[20] = "World";
    char src3[] = "";
    char expected3[20] = "World";

    s21_strcat(dest3, src3);

    printf("Strcat Test 3: Concatenating an empty string\n");
    printf("  Input: dest = \"%s\", src = \"\"\n", dest3);
    printf("  Expected: \"%s\"\n", expected3);
    printf("  Actual:   \"%s\"\n", dest3);

    if (s21_strcmp(dest3, expected3) != 0) {
        printf("  Result: %s\n", FAIL);
    } else {
        printf("  Result: %s\n", SUCCESS);
    }
    printf("\n");

    printf("Strcat Test 4: Overlap - not tested due to undefined behavior\n");
    printf("  WARNING: Overlapping destination and source is undefined behavior.\n");

}

int main() {
    s21_strlen_test();
    s21_strcmp_test();
    s21_strcpy_test();
    s21_strcat_test();

    return 0;
}
