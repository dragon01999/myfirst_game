#include <ncurses.h>
#include "game.h"
#include "render.h"

int gmax_x, gmax_y;
int wall[2];
extern int tail[2];
extern unsigned int score;
extern int game_status;
extern struct node food;

const char head = 'O';
const char body = 'o';

void init_curses(void)
{
    initscr();
    start_color();
    if (!has_colors()) {
        endwin();
        die("no colours\n");
    }
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);
    init_pair(2, COLOR_BLUE, -1);
    curs_set(0);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, gmax_y, gmax_x);
    wall[0] = (gmax_y - BOARD_Y) / 2;
    wall[1] = (gmax_x - BOARD_X) / 2;
}

static void draw_hline(int y, int x, int n, const char c)
{
    for(int i = x; i < x + n; ++i)
        mvaddch(y, i, c);
    refresh();
}

static void draw_vline(int y, int x, int n, const char c)
{
    for(int i = y; i < y + n; ++i)
        mvaddch(i, x, c);
    refresh();
}

static void draw_board(void)
{
    int x = (gmax_x - BOARD_X) / 2;
    int y = (gmax_y - BOARD_Y) / 2;
    draw_hline(y, x, BOARD_X, BOX_C);
    draw_vline(y, x, BOARD_Y, BOX_C);
    draw_hline(y + BOARD_Y, x, BOARD_X, BOX_C);
    draw_vline(y, x + BOARD_X, BOARD_Y+1, BOX_C);
    refresh();
}

static void draw_snake(struct node *snake)
{
    attron(COLOR_PAIR(1));
    mvaddch(snake->y, snake->x, head);
    for (snake = snake->next; snake != NULL; snake = snake->next) 
        mvaddch(snake->y, snake->x, body);
    attroff(COLOR_PAIR(1));
    refresh();
}

void erase_horizontal(int y, int x, int n)
{
    for (int i = x; i < x + n; i++)
        mvaddch(y, i, ' ');
    refresh();
}

void init_render(struct node *snake)
{
    init_curses();
    draw_board();
    mvprintw(wall[0]-2, wall[1], "Score: %d     ", score);
}
void render_snake(struct node *snake)
{
    if (!game_status) //if game_status is false then dont render
        return;
    erase_horizontal(tail[0], tail[1], 1);
    draw_snake(snake);
    mvprintw(wall[0]-2, wall[1], "Score: %d     ", score);
    mvaddch(food.y, food.x, '#');
    refresh();
}
