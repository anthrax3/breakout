#ifndef BREAKOUT_GAME_COLOR_H
#define BREAKOUT_GAME_COLOR_H

#include <ncurses.h>

#define SCORE_COLOR 	1
#define BALL_COLOR 		2
#define BAT_COLOR 		3
#define BRICKS_COLOR_1 	4
#define BRICKS_COLOR_2 	5
#define BRICKS_COLOR_3 	6
#define BRICKS_COLOR_4 	7
#define OVER_COLOR 		8
#define WON_COLOR 		9
#define LIFES_COLOR 	10
#define TITLE_COLOR 	11
#define AUTHOR_COLOR 	12

void init_color_pairs();

#endif