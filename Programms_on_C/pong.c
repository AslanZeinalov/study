#include <stdio.h>
#include <stdlib.h>

// Константы
#define WIDTH 80
#define HEIGHT 25
#define PADDLE_HEIGHT 3
#define BALL_SPEED_X 1
#define BALL_SPEED_Y 1
#define WIN_SCORE 21

// Глобальные переменные
// Мяч: x, y
int ball_x, ball_y;
// Ракетки: player1_x, player1_y, player2_x, player2_y
int player1_x, player1_y;
int player2_x, player2_y;

int ball_dx, ball_dy; // Направление мяча по x и y (1 или -1)
int score1, score2;

// Функции

// Инициализация игры
void init() {
    // Инициализация мяча
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = BALL_SPEED_X;
    ball_dy = BALL_SPEED_Y;

    // Инициализация ракеток
    player1_x = 1;
    player1_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;

    player2_x = WIDTH - 2;
    player2_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;

    // Инициализация счета
    score1 = 0;
    score2 = 0;
}

// Отрисовка игры в терминале
void draw() {
    // Создание буфера экрана
    char screen[HEIGHT][WIDTH + 1]; // +1 для завершающего нуля

    // Заполнение буфера пробелами
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = ' ';
        }
        screen[i][WIDTH] = '\0'; // Завершающий нуль для printf
    }

    // Отрисовка мяча
    screen[ball_y][ball_x] = 'O';

    // Отрисовка ракеток
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        if (player1_y + i >= 0 && player1_y + i < HEIGHT) { // Проверка границ
            screen[player1_y + i][player1_x] = '|';
        }
        if (player2_y + i >= 0 && player2_y + i < HEIGHT) { // Проверка границ
            screen[player2_y + i][player2_x] = '|';
        }
    }

    // Отрисовка верхней и нижней границ
    for (int j = 0; j < WIDTH; j++) {
        screen[0][j] = '-';
        screen[HEIGHT - 1][j] = '-';
    }

    // Вывод буфера на экран
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", screen[i]);
    }

    // Вывод счета
    printf("Score: Player 1: %d  Player 2: %d\n", score1, score2);
}

// Обновление состояния игры
void update() {
    // Движение мяча
    ball_x += ball_dx;
    ball_y += ball_dy;

    // Отскок от верхней и нижней границ
    if (ball_y <= 0 || ball_y >= HEIGHT - 1) {
        ball_dy *= -1;
    }

    // Проверка столкновения с ракетками
    if (ball_x <= player1_x + 1 && ball_y >= player1_y && ball_y < player1_y + PADDLE_HEIGHT) {
        ball_dx *= -1;
    } else if (ball_x >= player2_x - 1 && ball_y >= player2_y && ball_y < player2_y + PADDLE_HEIGHT) {
        ball_dx *= -1;
    }

    // Проверка, если мяч ушел за ракетку (гол)
    if (ball_x <= 0) {
        score2++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dx = BALL_SPEED_X; // Возобновляем движение вправо
    } else if (ball_x >= WIDTH - 1) {
        score1++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dx = -BALL_SPEED_X; // Возобновляем движение влево
    }
}

// Обработка ввода пользователя
void handle_input() {
    char input;
    printf("Enter command (A/Z for Player 1, K/M for Player 2, Space for next step, Q to quit): ");
    scanf(" %c", &input);

    switch (input) {
        case 'A':
        case 'a':
            player1_y--;
            if (player1_y < 1) player1_y = 1;
            break;
        case 'Z':
        case 'z':
            player1_y++;
            if (player1_y > HEIGHT - 1 - PADDLE_HEIGHT) player1_y = HEIGHT - 1 - PADDLE_HEIGHT;
            break;
        case 'K':
        case 'k':
            player2_y--;
            if (player2_y < 1) player2_y = 1;
            break;
        case 'M':
        case 'm':
            player2_y++;
            if (player2_y > HEIGHT - 1 - PADDLE_HEIGHT) player2_y = HEIGHT - 1 - PADDLE_HEIGHT;
            break;
        case ' ': // Spacebar
            // Do nothing, next step handled in main loop
            break;
        case 'Q':
        case 'q':
            exit(0);
        default:
            printf("Invalid command.\n");
            break;
    }
}

int main() {
    init();

    while (1) {
        draw();
        printf("\n"); // Add an extra newline for readability in step mode
        handle_input();
        update(); // Обновляем состояние игры только после ввода команды 'n'

        if (score1 >= WIN_SCORE) {
            printf("Player 1 wins!\n");
            break;
        }
        if (score2 >= WIN_SCORE) {
            printf("Player 2 wins!\n");
            break;
        }
    }

    return 0;
}
