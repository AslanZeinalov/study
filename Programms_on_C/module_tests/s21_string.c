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

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2; 
}

char *s21_strcpy(char *dest, const char *src) {
    char *original_dest = dest; 

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; 

    return original_dest; 
}    
