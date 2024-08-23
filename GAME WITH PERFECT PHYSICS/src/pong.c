// COMPILE WITH -lm -lncurses

#include <math.h>
#include <stdio.h>

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

double hop_border(double a) {
    double pi = 2 * acos(0.0);
    return 2 * pi - a;
}

double hop_rocket(double a) {
    double pi = 2 * acos(0.0);

    return pi - a;
}

int main() {
    int seed;
    printf("Enter seed for random angle generation\n");
    scanf("%d", &seed);

    seed = seed * 1147483647 % 3141592;
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

        if ((int)ball_y == 0 || (int)ball_y == row - 1) {
            printf("ГООООЛ\n");
            if (-314159 < seed && seed < 314159) {
                printf("Ты с ума сошёл? Мы в пинг-понг играем!\n");
            }
            if ((int)ball_y == 0) score2 += 1;
            if ((int)ball_y == row - 1) score1 += 1;

            if (score1 == 21) {
                printf("Игра окончена! Левые победили!\n");
                return 0;
            }
            if (score2 == 21) {
                printf("Игра окончена! Правые победили!\n");
                return 0;
            }
            printf("Счёт:\nЛевый: %d\nПравый: %d\nНажмите любую кнопку для запуска следующего раунда...\n",
                   score1, score2);

            char c;
            scanf("%c", &c);
            seed = seed * 1147483647 % 3141592;
            a = seed * 0.000001;
            racket1_x = str / 2 - 1;
            racket2_x = str / 2 - 1;
            ball_x = str / 2;
            ball_y = row / 2;
        }

        for (int x = 0; x < str; x++) {
            for (int y = 0; y < row; y++) {
                if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (y == 0 && x == str - 1) ||
                    (x == str - 1 && y == row - 1))
                    printf("+");

                else if (x == 0 || x == str - 1)
                    printf("-");
                else if (y == 0 || y == row - 1)
                    printf("|");
                else if (x == (int)ball_x && y == (int)ball_y)
                    printf("*");
                else if (y == row / 2)
                    printf("|");
                else if ((y == racket1_y && x == racket1_x + 1) || (y == racket1_y && x == racket1_x + 2) ||
                         (y == racket1_y && x == racket1_x)) {
                    printf("|");
                    if (x == (int)ball_x && y == (int)ball_y) a = hop_rocket(a);
                } else if ((y == racket2_y && x == racket2_x + 1) || (y == racket2_y && x == racket2_x + 2) ||
                           (y == racket2_y && x == racket2_x)) {
                    printf("|");
                    if (x == (int)ball_x && y == (int)ball_y) a = hop_rocket(a);
                } else
                    printf(" ");
            }
            printf("\n");
        }

        printf("Счёт:\nЛевый: %d\nПравый: %d\nНажмите любую кнопку для запуска следующего раунда...\n",
               score1, score2);
        char c;
        scanf("%c", &c);

        switch (c) {
            case 's': {
                if (racket1_x > 1) racket1_x--;
                break;
            }
            case 'x': {
                if (racket1_x < str - 4) racket1_x++;
                break;
            }
            case 'k': {
                if (racket2_x > 1) racket2_x--;
                break;
            }
            case 'm': {
                if (racket2_x < str - 4) racket2_x++;
                break;
            }
        }
    }

    return 0;
}