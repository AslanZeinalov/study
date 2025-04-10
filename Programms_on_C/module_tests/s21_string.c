#include "s21_string.h"

size_t s21_strlen(const char *str) {
    if (str == NULL) {
        return 0; 
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
