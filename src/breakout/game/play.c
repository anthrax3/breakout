#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include <breakout.h>

#include "play.h"
#include "color.h"

static inline void input_move(GAME *game, int speed)
{
    int bat;
    int win;
    int mul;

    if (speed < 0) {
        bat = game->bat->rect.left;
        win = game->rect.left;
        mul = 1;
    } else {
        bat = game->bat->rect.right;
        win = game->rect.right;
        mul = -1;
    }

    if ((mul * (bat + speed)) >= (mul * win)) {
        rect_mov_x(&game->bat->rect, speed);
    }
}

static inline void input(GAME *game)
{
    int ch = getch();

    if (-1 == ch) {
        return;
    }

    switch (ch) {
    case 27:
        // Escape
        game->end = true;
        break;

    case KEY_LEFT:
        if(!game->pause)
            input_move(game, -game->bat->speed);
        break;

    case KEY_UP:
        if(!game->pause)
            input_move(game, -game->bat->speed * 4);
        break;

    case KEY_RIGHT:
        if(!game->pause)
            input_move(game, game->bat->speed);
        break;

    case KEY_DOWN:
        if(!game->pause)
            input_move(game, game->bat->speed * 4);
        break;
    
    case 112:
        // p
        if(game->pause){
            game->pause = false;
        } else {
            game->pause = true;
        }
        break;
    }

    if (konami_push(game->konami, ch)) {
        game->score += 1024;
        game->won = true;
    }
}

static inline void live_ball_win(GAME *game)
{
    if ((game->ball->rect.top + game->ball->vel.y) < game->rect.top) {
        game->ball->vel.y *= -1;
    }

    if ((game->ball->rect.left + game->ball->vel.x) < game->rect.left) {
        game->ball->vel.x *= -1;
    }

    if ((game->ball->rect.bottom + game->ball->vel.y) > game->rect.bottom) {
        if (game->debug) {
            game->ball->vel.y *= -1;
        } else {
            if(game->lifes == 0){
                game->over = true;
                return;
            } else {
                game->lifes--;
                rect_init(&game->ball->rect, (LINES / 2) - 1, (COLS / 2) - 1, 1, 1);
                game->ball->vel.y = 1;
                game->ball->vel.x = 0;
                rect_init(&game->bat->rect, LINES - 3, (COLS / 2) - 8, 1, 16);
            }
        }
    }

    if ((game->ball->rect.right + game->ball->vel.x) > game->rect.right) {
        game->ball->vel.x *= -1;
    }
}

static inline void live_ball_bat(GAME *game)
{
    if (game->ball->rect.bottom < (game->bat->rect.top - 1)) {
        return;
    }

    COL col = col_mov_test(&game->bat->rect, &game->ball->rect, &game->ball->vel);

    if (TOP != col) {
        return;
    }

    int dif = game->ball->rect.left - game->bat->rect.left;//0-15
    int mid = game->bat->rect.width / 2;//8
    int dir = dif < mid ? -1 : 1;

    if (dir > 0) {
        // Same value for extreme left and extreme right
        dif = 15 - dif;
    }

    // 3 possible angles per half
    int len = mid / 3;

    int vy;
    int vx;

    if (dif < len) {
        // Extremity
        vy = 1;
        vx = 2;
    } else if (dif < (len * 2)) {
        // Middle
        vy = 1;
        vx = 1;
    } else {
        // Center
        vy = 2;
        vx = 1;
    }

    game->ball->vel.y = vy * -1;
    game->ball->vel.x = vx * dir;
}

static inline void live_ball_bricks(GAME *game)
{
    COL col;
    int i = game->nbricks;

    while (--i >= 0) {
        if (!game->bricks[i].lives) {
            continue;
        }

        col = col_mov_test(
            &game->bricks[i].rect,
            &game->ball->rect,
            &game->ball->vel
        );

        if (NONE == col) {
            continue;
        }

        if (!--game->bricks[i].lives) {
            game->score += game->bricks[i].btype->score;

            
            if (!--game->rbricks) {
                game->won = true;
            }
        }

        if (TOP == col || BOTTOM == col) {
            game->ball->vel.y *= -1;
        } else {
            game->ball->vel.x *= -1;
        }
    }
}

static inline void live_ball(GAME *game)
{
    if (game->clock.ms % 50) {
        return;
    }

    live_ball_win(game);
    live_ball_bat(game);
    live_ball_bricks(game);

    mov_rect(&game->ball->rect, &game->ball->vel);
}

static inline void live(GAME *game)
{
    live_ball(game);
    
    if(game->rbricks == 0)
        game->won = true;
}

static inline void draw_score(GAME *game)
{
    char str[32], str2[11];

    attron(COLOR_PAIR(SCORE_COLOR));
    sprintf(str, " %d points ", game->score);
    mvwaddstr(game->win, 0, COLS - strlen(str) - 2, str);
    attroff(COLOR_PAIR(SCORE_COLOR));

    attron(COLOR_PAIR(LIFES_COLOR));
    sprintf(str2, " %d lifes ", game->lifes);
    mvwaddstr(game->win, 0, COLS - strlen(str) - 13, str2);
    attroff(COLOR_PAIR(LIFES_COLOR));
}

static inline void draw_rect(WINDOW *win, RECT *rect, char ch)
{
    int i = rect->height;

    while (--i >= 0) {
        mvwhline(
            win,
            rect->top + i,
            rect->left,
            ch,
            rect->width
        );
    }
}

static inline void draw_ball(GAME *game)
{
    attron(COLOR_PAIR(BALL_COLOR));
    draw_rect(game->win, &game->ball->rect, game->ball->ch);
    attroff(COLOR_PAIR(BALL_COLOR));
}

static inline void draw_bat(GAME *game)
{
    attron(COLOR_PAIR(BAT_COLOR));
    draw_rect(game->win, &game->bat->rect, game->bat->ch);
    attroff(COLOR_PAIR(BAT_COLOR));
}

static inline void draw_bricks(GAME *game)
{
    int i = game->nbricks;

    while (--i >= 0) {
        if (!game->bricks[i].lives) {
            continue;
        }

        attron(COLOR_PAIR(game->bricks[i].lives + 3));
        draw_rect(game->win, &game->bricks[i].rect, game->chlives[game->bricks[i].lives - 1]);
        attroff(COLOR_PAIR(game->bricks[i].lives + 3));
    }
}

static inline void draw(GAME *game)
{
    init_color_pairs();
    game_repaint(game);

    draw_score(game);
    draw_ball(game);
    draw_bat(game);
    draw_bricks(game);

    game_refresh(game);
}

void game_play_frame(GAME *game)
{
    input(game);
    if(!game->pause){
        live(game);
    }   
    draw(game);
}