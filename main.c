#include <stdio.h>
#include <ncurses.h>
#include "render.h"
#include "game.h"

extern int game_status;
void end_snake(void);

int main(void) {
    struct node *snake = NULL;

    init_render(snake);
    init_snake(&snake);
    render_snake(snake);

    while (game_status) {
        update_snake(&snake);
        render_snake(snake);
        fps(3);
    }
    free_nodes(&snake);
    end_snake();
}



void end_snake(void)
{
    clear();
    printw("Game Over\n");
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}
