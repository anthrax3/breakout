#include "color.h"

void init_color_pairs() {
	init_pair(SCORE_COLOR, COLOR_BLUE, -1);
	init_pair(BALL_COLOR, COLOR_WHITE, COLOR_WHITE);
	init_pair(BAT_COLOR, COLOR_GREEN, COLOR_GREEN);
	init_pair(BRICKS_COLOR_1, COLOR_GREEN, COLOR_GREEN);
	init_pair(BRICKS_COLOR_2, COLOR_BLUE, COLOR_BLUE);
	init_pair(BRICKS_COLOR_3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(BRICKS_COLOR_4, COLOR_RED, COLOR_RED);
	init_pair(OVER_COLOR, COLOR_RED, -1);
	init_pair(WON_COLOR, COLOR_WHITE, -1);
	init_pair(LIFES_COLOR, COLOR_RED, -1);
	init_pair(TITLE_COLOR, COLOR_YELLOW, -1);
	init_pair(AUTHOR_COLOR, COLOR_CYAN, -1);
}