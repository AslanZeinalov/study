#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"

void format_text(int width, const char *text) {
    int word_count = 0;
    char **words = NULL;
    char *token = NULL;
    char *str = NULL;
    size_t len = s21_strlen(text);
    char *text_copy = (char *)malloc((len + 1) * sizeof(char));
    if (text_copy == NULL) {
        printf("n/a\n");
        return;
    }
    s21_strcpy(text_copy, text);
    str = text_copy;
    token = s21_strtok(str, " ");
    while (token != NULL) {
        word_count++;
        words = (char **)realloc(words, word_count * sizeof(char *));
        if (words == NULL) {
            printf("n/a\n");
            free(text_copy);
            return;
        }
        words[word_count - 1] = token;
        token = s21_strtok(NULL, " ");
    }

    if (words == NULL) {
        printf("n/a\n");
        free(text_copy);
        return;
    }

    int line_length = 0;
    int word_index = 0;
    char *line = (char *)malloc((width + 1) * sizeof(char));
    if (line == NULL) {
        printf("n/a\n");
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        free(text_copy);
        return;
    }

    line[0] = '\0';

    while (word_index < word_count) {
        size_t word_len = s21_strlen(words[word_index]);

        if (line_length == 0 && word_len <= (size_t)width) {
            s21_strcpy(line, words[word_index]);
            line_length = word_len;
            word_index++;

        } else if ((size_t)line_length + word_len + 1 <= (size_t)width) {
            line[line_length] = ' ';
            s21_strcpy(line + line_length + 1, words[word_index]);
            line_length += word_len + 1;
            word_index++;

        } else if (word_len <= (size_t)width) {
            int i = line_length - 1;
            while (i >= 0 && line[i] == ' ') {
                i--;
            }
            line[i + 1] = '\0';
            printf("%s\n", line);

            s21_strcpy(line, words[word_index]);
            line_length = word_len;
            word_index++;

        } else {
            if (word_index > 0) {
                int i = line_length - 1;
                while (i >= 0 && line[i] == ' ') {
                    i--;
                }
                line[i + 1] = '\0';
                printf("%s\n", line);
            }

            int hyphen_pos = -1;
            for (size_t i = 0; i < word_len - 1 && (size_t)i < (size_t)width; i++) {
                if (words[word_index][i] == '-') {
                    hyphen_pos = (int)i;
                }
            }

            if (hyphen_pos != -1) {
                s21_memcpy(line, words[word_index], (size_t)hyphen_pos + 1);
                line[hyphen_pos + 1] = '\0';
                printf("%s\n", line);
                s21_strcpy(line, words[word_index] + hyphen_pos + 1);
                line_length = s21_strlen(words[word_index] + hyphen_pos + 1);

            } else {
                s21_memcpy(line, words[word_index], (size_t)width);
                line[width] = '\0';
                printf("%s\n", line);
                s21_strcpy(line, words[word_index] + width);
                line_length = s21_strlen(words[word_index] + width);
            }

            word_index++;

        }
    }

    if (line_length > 0) {
        int i = line_length - 1;
        while (i >= 0 && line[i] == ' ') {
            i--;
        }
        line[i + 1] = '\0';
        printf("%s", line);
    }

    free(line);
    if (words != NULL) {
        for (int i = 0; i < word_count; i++) {
        }
        free(words);
    }
    free(text_copy);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("n/a\n");
        return 1;
    }

    char *key = argv[1];

    if (s21_strcmp(key, "-w") == 0) {
        int width;
        char text[101];

        if (scanf("%d", &width) != 1 || width <= 0) {
            printf("n/a\n");
            return 1;
        }

        while (getchar() != '\n');

        if (fgets(text, 101, stdin) == NULL) {
            printf("n/a\n");
            return 1;
        }

        size_t len = s21_strlen(text);
        if (len > 0 && text[len - 1] == '\n') {
            text[len - 1] = '\0';
        }

        format_text(width, text);

    } else {
        printf("n/a\n");
        return 1;
    }

    return 0;
}
