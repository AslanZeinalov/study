#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void code(void);
void decode(void);
int main() {
    int command;
    printf("Введите команду:\n0 - кодирование\n1 - декодирование\n");
    if (scanf("%d", &command) != 1) {
        printf("n/a\n");
        return 1;
    }
    getchar();
    if (command == 0) {
        printf("Введите слово для кодирования:\n");
        code();
    } else if (command == 1) {
        printf("Введите код:\n");
        decode();
    } else {
        printf("n/a\n");
    }
    return 0;
}
void decode(void) {
    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    char *token = strtok_r(input, " ");
        while (token != NULL) {
        int hex_value;
        if (sscanf(token, "%x", &hex_value) != 1 || hex_value < 0 || hex_value > 255) {
            printf("n/a\n");
            return;
        }
        printf("%c ", (char)hex_value);
        token = strtok_r(NULL, " ");
    }
    printf("\n");
}
void code(void) {
    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    char *token = strtok_r(input, " ");
    while (token != NULL) {
        printf("%02X ", (unsigned char)token[0]);
        token = strtok_r(NULL, " ");
    }
    printf("\n");
}
