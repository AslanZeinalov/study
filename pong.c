#include <stdio.h>

// Цвета
#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define DARK_GRAY_BG "\x1B[100m"

void draw_top_panel(int player_one_score, int player_two_score) {
    printf(RED BOLD "Player one score: %d " RESET, player_one_score);
    printf(BLUE BOLD " Player two score: %d" RESET, player_two_score);
}

void draw_left_paddle(int y, int left_rocket_y) {
    if ((y == left_rocket_y - 1 || y == left_rocket_y || y == left_rocket_y + 1) && y > 1 && y < 26) {
        printf(RED "█" RESET);
    } else {
        printf("░");
    }
}

void draw_right_paddle(int y, int right_rocket_y) {
    if ((y == right_rocket_y - 1 || y == right_rocket_y || y == right_rocket_y + 1) && y > 1 && y < 26) {
        printf(BLUE "█" RESET);
    } else {
        printf("░");
    }
}

void draw_ball(int x, int y, int ball_x, int ball_y) {
    if (x == ball_x && y == ball_y) {
        printf("●");
    } else {
        printf("░");
    }
}

void draw_bottom_panel(void) {
    printf(RED BOLD "Player one controls: ↑a ↓z   " RESET);
    printf(BLUE BOLD "Player two controls: ↑k ↓m" RESET);
}

void print_gameboard(int start_screen, int left_rocket_y, int right_rocket_y, int ball_x, int ball_y,
                     int player_one_score, int player_two_score) {
    for (int y = 0; y < 27; y++) {
        for (int x = 0; x < 80; x++) {
            if (start_screen == 0) {
                if (y == 25 || y == 1) {
                    printf("─");
                } else if (y == 0 && (x < 17 || x > 61)) {
                    printf(" ");
                } else if (y == 0 && x == 17) {
                    draw_top_panel(player_one_score, player_two_score);
                    x = 61;
                } else if (x == 0 && y > 1 && y < 26) {
                    draw_left_paddle(y, left_rocket_y);
                } else if (x == 79 && y > 1 && y < 26) {
                    draw_right_paddle(y, right_rocket_y);
                } else if (y > 1 && y < 26 && x > 0 && x < 79) {
                    draw_ball(x, y, ball_x, ball_y);
                } else if (y == 26 && (x < 10 || x > 61)) {
                    printf(" ");
                } else if (y == 26 && x == 10) {
                    draw_bottom_panel();

                } else if (y == 26 && x > 10) {
                    x = 79;
                } else {
                    printf("░");
                }
            } else if (start_screen == 1) {
                if ((x > 20 && x < 56) && (y > 9 && y < 17)) {
                    if (y == 13 && x == 24) {
                        printf(DARK_GRAY_BG BOLD "PRESS SPACE TO START THE GAME" RESET);
                        x += 28;
                    } else {
                        printf("▓");
                    }
                } else {
                    printf("░");
                }
            }
        }
        printf("\n");
    }
}

int player_one_pos(char key, int pos) {
    if (key == 'z' || key == 'Z') {
        if (pos < 23) {
            pos++;
        }
    } else if (key == 'a' || key == 'A') {
        if (pos > 3) {
            pos--;
        }
    }
    return pos;
}

int player_two_pos(char key, int pos) {
    if (key == 'm' || key == 'M') {
        if (pos < 23) {
            pos++;
        }
    } else if (key == 'k' || key == 'K') {
        if (pos > 3) {
            pos--;
        }
    }
    return pos;
}

int main(void) {
    int left_rocket_y = 12;
    int right_rocket_y = 12;
    int ball_x = 40;
    int ball_y = 12;
    int ball_dx = 1;
    int ball_dy = 1;
    int player_one_score = 0;
    int player_two_score = 0;
    int start_screen = 1;
    int game_running = 1;

    // Стартовый экран
    while (start_screen) {
        printf("\x1B[2J\x1B[H");
        print_gameboard(start_screen, left_rocket_y, right_rocket_y, ball_x, ball_y, player_one_score,
                        player_two_score);

        char key = getchar();
        while (getchar() != '\n');

        if (key == ' ') {
            start_screen = 0;
            printf("\x1B[2J\x1B[H");
            print_gameboard(start_screen, left_rocket_y, right_rocket_y, ball_x, ball_y, player_one_score,
                            player_two_score);
        }
    }

    // Основной игровой цикл
    while (game_running && player_one_score < 21 && player_two_score < 21) {
        ball_x += ball_dx;
        ball_y += ball_dy;

        if (ball_y <= 2 || ball_y >= 24) {
            ball_dy *= -1;
        }

        if (ball_x == 1 && (ball_y >= left_rocket_y - 1 && ball_y <= left_rocket_y + 1)) {
            ball_dx = 1;
        }

        if (ball_x == 78 && (ball_y >= right_rocket_y - 1 && ball_y <= right_rocket_y + 1)) {
            ball_dx = -1;
        }

        if (ball_x <= 0) {
            player_two_score++;
            ball_x = 40;
            ball_y = 12;
            ball_dx = 1;
            ball_dy = 1;
        }

        if (ball_x >= 79) {
            player_one_score++;
            ball_x = 40;
            ball_y = 12;
            ball_dx = -1;
            ball_dy = 1;
        }

        printf("\x1B[2J\x1B[H");
        print_gameboard(start_screen, left_rocket_y, right_rocket_y, ball_x, ball_y, player_one_score,
                        player_two_score);

        char key = getchar();
        while (getchar() != '\n');

        if (key == 'a' || key == 'z' || key == 'A' || key == 'Z') {
            left_rocket_y = player_one_pos(key, left_rocket_y);
        } else if (key == 'k' || key == 'm' || key == 'K' || key == 'M') {
            right_rocket_y = player_two_pos(key, right_rocket_y);
        } else if (key == 'q' || key == 'Q') {
            game_running = 0;
        }
    }

    return 0;
}