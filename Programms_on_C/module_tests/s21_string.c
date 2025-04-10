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

char *s21_strcat(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    char *original_dest = dest;

   while (*dest != '\0') {
        dest++;
    }

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return original_dest;
}

char *s21_strchr(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }

    if (c == '\0') {
        return (char *)str;
    }

    return NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return NULL;
    }

    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL;
}

static char *s21_strtok_static_next_token = NULL;

char *s21_strtok(char *str, const char *delim) {
    char *token_start;
    const char *d;

    if (str == NULL) {
        str = s21_strtok_static_next_token;
        if (str == NULL) {
            return NULL;
        }
    }

    while (*str != '\0') {
        for (d = delim; *d != '\0'; d++) {
            if (*str == *d) {
                break;
            }
        }
        if (*d == '\0') {
            break;
        }
        str++;
    }

    if (*str == '\0') {
        s21_strtok_static_next_token = NULL;
        return NULL;
    }

    token_start = str;

    while (*str != '\0') {
        for (d = delim; *d != '\0'; d++) {
            if (*str == *d) {
                *str = '\0';
                s21_strtok_static_next_token = str + 1;
                return token_start;
            }
        }
        str++;
    }

    s21_strtok_static_next_token = NULL;
    return token_start;
}
