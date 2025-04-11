#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Структура для представления элемента многочлена (одночлена)
typedef struct PolynomialNode {
    int coefficient;  // Коэффициент
    int exponent;     // Степень
    struct PolynomialNode *next;
} PolynomialNode;

// Функция для создания нового элемента одночлена
PolynomialNode *createNode(int coefficient, int exponent) {
    PolynomialNode *newNode = (PolynomialNode *)malloc(sizeof(PolynomialNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления элемента в односвязный список
void appendNode(PolynomialNode **head, int coefficient, int exponent) {
    PolynomialNode *newNode = createNode(coefficient, exponent);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    PolynomialNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Функция для разбора строки многочлена
PolynomialNode *parsePolynomial(const char *polynomialStr) {
    PolynomialNode *head = NULL;
    int coefficient = 0;
    int exponent = 0;
    int sign = 1;  // 1 for positive, -1 for negative
    int state = 0;  // 0: start, 1: coefficient, 2: exponent

    const char *p = polynomialStr;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-') {
            if (state != 0) {
                appendNode(&head, sign * coefficient, exponent);
            }
            coefficient = 0;
            exponent = 0;
            sign = (*p == '+') ? 1 : -1;
            state = 0;
            p++;
        } else if (isdigit(*p)) {
            if (state == 0) {
                coefficient = coefficient * 10 + (*p - '0');
                state = 1;
            } else if (state == 1 && *(p - 1) == '^') { // Check if previous char was '^'
                exponent = exponent * 10 + (*p - '0');
                state = 2;
            } else if (state == 1 && *(p - 1) != '^') {
                coefficient = coefficient * 10 + (*p - '0');
            }
            p++;
        } else if (*p == '*') {
            p++;
        } else if (*p == 'x') {
            if (coefficient == 0) {
                coefficient = 1;  // Implicit coefficient of 1
            }
            if (state == 0) {
                coefficient = 1;
                state = 1;
            }

            if (*(p + 1) != '^') {
                exponent = 1; // Implicit exponent of 1
                appendNode(&head, sign * coefficient, exponent);
                coefficient = 0;
                exponent = 0;
                sign = 1;
                state = 0;
            } else {
                 state = 1;  // Expect exponent
            }
            p++;

        } else if (*p == '^') {
            p++;
        } else {
            fprintf(stderr, "Invalid character in polynomial: %c\n", *p);
            exit(EXIT_FAILURE);
        }
    }

    // Add the last term
    appendNode(&head, sign * coefficient, exponent);

    return head;
}

// Функция для вычисления значения многочлена
double evaluatePolynomial(PolynomialNode *head, double x) {
    double result = 0.0;
    PolynomialNode *current = head;
    while (current != NULL) {
        result += current->coefficient * pow(x, current->exponent);
        current = current->next;
    }
    return result;
}

// Функция для освобождения памяти, занятой односвязным списком
void freePolynomial(PolynomialNode *head) {
    PolynomialNode *current = head;
    while (current != NULL) {
        PolynomialNode *next = current->next;
        free(current);
        current = next;
    }
}

// Функция для вывода многочлена (для отладки)
void printPolynomial(PolynomialNode *head) {
    PolynomialNode *current = head;
    while (current != NULL) {
        printf("%+d*x^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <polynomial_string> <x_value>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *polynomialStr = argv[1];
    double x = strtod(argv[2], NULL); // Convert x to double

    PolynomialNode *polynomialList = parsePolynomial(polynomialStr);

    //printf("Parsed Polynomial: "); //Раскомментируйте для отладки
    //printPolynomial(polynomialList); //Раскомментируйте для отладки

    double result = evaluatePolynomial(polynomialList, x);
    printf("Polynomial value at x = %.2f: %.2f\n", x, result);

    freePolynomial(polynomialList);

    return EXIT_SUCCESS;
}
