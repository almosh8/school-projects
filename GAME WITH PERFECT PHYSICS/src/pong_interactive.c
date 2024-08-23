// COMPILE WITH -lm -lncurses

#include <math.h>
#include <ncurses.h>
#include <stdio.h>

#define PI 2 * acos(0.0)

double move_ball_back_x(double x, double a) {
    x -= sin(a);

    return x;
}

double move_ball_back_y(double y, double a) {
    y -= cos(a);

    return y;
}
double move_ball_x(double x, double a) {
    x += sin(a);

    return x;
}

double move_ball_y(double y, double a) {
    y += cos(a);

    return y;
}

double hop_border(double a) { return 2 * PI - a; }

double hop_rocket(double a) { return PI - a; }

int next_seed(int seed) {
    seed = seed * 1147483647 % 3141592;

    double x = seed * 0.000001;

    while ((PI / 2 - 0.2 < x && x < PI / 2 + 0.2) || (PI / 2 - 0.2 < -x && -x < PI / 2 + 0.2) ||
           (PI - 0.2 < x && x < PI + 0.2) || (PI - 0.2 < -x && -x < PI + 0.2)) {
        seed = seed * 1147483647 % 3141592;
        x = seed * 0.000001;
    }

    return seed;
}

int main() {
    int seed;
    int difficulty;
    printf("Enter seed for random angle generation\n");
    scanf("%d", &seed);
    printf("Enter difficulty level(number from 1(the fastest) to 10(the slowest))\n");
    scanf("%d", &difficulty);

    seed = next_seed(seed);
    double a = seed * 0.000001;

    int score1 = 0;
    int score2 = 0;
    int str = 25;
    int row = 80;
    double ball_x = str / 2;
    double ball_y = row / 2;
    int racket1_y = 15;
    int racket2_y = 65;
    int racket1_x = str / 2 - 1;
    int racket2_x = str / 2 - 1;

    int gooool_cnt = 0;

    while (1) {
        ball_x = move_ball_x(ball_x, a);
        ball_y = move_ball_y(ball_y, a);

        if (((int)ball_y == racket1_y && (int)ball_x == racket1_x + 1) ||
            ((int)ball_y == racket1_y && (int)ball_x == racket1_x + 2) ||
            ((int)ball_y == racket1_y && (int)ball_x == racket1_x) ||
            ((int)ball_y == racket2_y && (int)ball_x == racket2_x + 1) ||
            ((int)ball_y == racket2_y && (int)ball_x == racket2_x + 2) ||
            ((int)ball_y == racket2_y && (int)ball_x == racket2_x)) {
            ball_x = move_ball_back_x(ball_x, a);
            ball_y = move_ball_back_y(ball_y, a);
            a = hop_rocket(a);
            ball_x = move_ball_x(ball_x, a);
            ball_y = move_ball_y(ball_y, a);
        }
        if ((int)ball_x == 1) a = hop_border(a);
        if ((int)ball_x == str - 2) a = hop_border(a);

        initscr();
        clear();

        for (int x = 0; x < str; x++) {
            for (int y = 0; y < row; y++) {
                if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (y == 0 && x == str - 1) ||
                    (x == str - 1 && y == row - 1))
                    printw("+");

                else if (x == 0 || x == str - 1)
                    printw("-");
                else if (y == 0 || y == row - 1)
                    printw("|");
                else if (x == (int)ball_x && y == (int)ball_y)
                    printw("*");
                else if (y == row / 2)
                    printw("|");
                else if ((y == racket1_y && x == racket1_x + 1) || (y == racket1_y && x == racket1_x + 2) ||
                         (y == racket1_y && x == racket1_x)) {
                    printw("|");
                    if (x == (int)ball_x && y == (int)ball_y) a = hop_rocket(a);
                } else if ((y == racket2_y && x == racket2_x + 1) || (y == racket2_y && x == racket2_x + 2) ||
                           (y == racket2_y && x == racket2_x)) {
                    printw("|");
                    if (x == (int)ball_x && y == (int)ball_y) a = hop_rocket(a);
                } else
                    printw(" ");
            }
            printw("\n");
        }

        if ((int)ball_y == 0 || (int)ball_y == row - 1) {
            if ((int)ball_y == 0) score2 += 1;
            if ((int)ball_y == row - 1) score1 += 1;

            gooool_cnt = 40;

            seed = next_seed(seed);
            a = seed * 0.000001;
            racket1_x = str / 2 - 1;
            racket2_x = str / 2 - 1;
            ball_x = str / 2;
            ball_y = row / 2;
            continue;
        }

        if (gooool_cnt > 0) {
            printw("GOOOOL\n");
            if (-914159 < seed && seed < 914159) {
                printw("Are you crazy? We're playing ping pong!\n");
            }
            gooool_cnt -= 1;
        }
        printw("Score:\nLeft: %d\nRight: %d\n", score1, score2);
        if (score1 == 21) {
            printw("Game over! The left has won!\n");
            getch();
            break;
        }
        if (score2 == 21) {
            printw("Game over! The right has won!\n");
            getch();
            break;
        }

        timeout(0);

        // timer
        int move1 = 0;
        int move2 = 0;
        for (int j = 0; j < difficulty * 100000; j++) {
            char c = getch();
            if (c != -1) {
                switch (c) {
                    case 'a': {
                        if (!move1) {
                            move1 = 1;
                            if (racket1_x > 1) racket1_x--;
                        }
                        break;
                    }
                    case 'z': {
                        if (!move1) {
                            move1 = 1;
                            if (racket1_x < str - 4) racket1_x++;
                        }
                        break;
                    }
                    case 'k': {
                        if (!move2) {
                            move2 = 1;
                            if (racket2_x > 1) racket2_x--;
                        }
                        break;
                    }
                    case 'm': {
                        if (!move2) {
                            move2 = 1;
                            if (racket2_x < str - 4) racket2_x++;
                        }
                        break;
                    }
                }
            }
        }
    }

    if (score1 == 21) {
        printw("Game over! The left has won!\n");
    }
    if (score2 == 21) {
        printw("Game over! The right has won!\n");
    }

    return 0;
}