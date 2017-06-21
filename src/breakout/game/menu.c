#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#include "menu.h"
#include "color.h"

static inline void input(GAME *game)
{
    int ch = getch();

    switch (ch) {
    case 10:
        // Enter
        game_setup(game);
        break;

    case 27:
        // Escape
        game->end = true;
        break;
    }
}

static inline void draw(GAME *game, int flag)
{
    game_repaint(game);

    int middley = game->rect.top + (game->rect.height / 2);
    int middlex = game->rect.left + (game->rect.width / 2);
    char *over = "GAME OVER";
    char *won = "YOU WON";

    if (flag == OVER) {
        attron(COLOR_PAIR(OVER_COLOR));
        mvwaddstr(game->win, middley - 2, middlex - (strlen(over) / 2), over);
        attroff(COLOR_PAIR(OVER_COLOR));
    }

    if (flag == WON) {
        char str[32];
        attron(COLOR_PAIR(WON_COLOR));
        mvwaddstr(game->win, middley - 4, middlex - (strlen(won) / 2), won);
        attroff(COLOR_PAIR(WON_COLOR));

        sprintf(str, " %d points ", game->score + (game->lifes*2));
        attron(COLOR_PAIR(SCORE_COLOR));
        mvwaddstr(game->win, middley - 2, middlex - (strlen(str) / 2) + 1, str);
        attroff(COLOR_PAIR(SCORE_COLOR));
    }

    mvwaddstr(game->win, middley, middlex - (14 / 2), "[Enter]: Retry");
    mvwaddstr(game->win, middley + 1, middlex - (10 / 2), "[Esc]: Quit");

    game_refresh(game);
}

void game_menu_frame(GAME *game, int flag)
{
    input(game);
    draw(game, flag);
}
