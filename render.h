#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#define BOARD_X 15
#define BOARD_Y 10
#define BOX_C '#'

void init_curses(void);

void erase_horizontal(int y, int x, int n);

void init_render(struct node *snake);

void render_snake(struct node *snake);

#endif
