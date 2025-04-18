#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h>  
#include <stdio.h>  

size_t s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *dest, const char *src);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_memcpy(void *dest, const void *src, size_t n);

#endif  // S21_STRING_H
