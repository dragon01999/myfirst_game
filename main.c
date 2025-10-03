#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
#include"util.h"

int curr_score = 0;
bool GAME_STATUS = TRUE;
Direction CURRENT_DIR = RIGHT;
int snake_size = 3;
char FOOD_CHAR = '#';
char BODY_CHAR = 't';
char HEAD_CHAR = '$';

int main(void)
{   
    // will intialize screen, input etc...
    initscr();
    curs_set(0);
    noecho();                                              keypad(stdscr, TRUE);
    cbreak();
    nodelay(stdscr, TRUE);
    // Colors
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLUE);
    init_pair(3, COLOR_MAGENTA, COLOR_CYAN);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    
    // variables and initial nodes
    node *head = NULL;
    node *food = NULL;
    food = creat();
    int size = 1;

    // Will intialize body
    for (int i = 0; i < INITIAL_SIZE; i++) {
        head = gen_body(head, size);
        co_update(head);
    }
        
    // Generates intial food
    food_gen(head, food);
    //printing score and highest score on screen
    // Main game loop
      while (GAME_STATUS) {
        erase();
		input();
        collision(head);
        attron(COLOR_PAIR(5));
        mvaddch(food->y, food->x, FOOD_CHAR);
        attroff(COLOR_PAIR(5));
        print_body(head);
        attron(COLOR_PAIR(3));
        mvprintw(0, 0, "CURR_SCORE: %i", curr_score);
        attroff(COLOR_PAIR(3));
        wnoutrefresh(stdscr);
        doupdate();
        if (head->x == food->x && head->y == food->y) {
            snake_size += 1;
            head = gen_body(head, 1);
            co_update(head);
            collision(head);
            food_gen(head, food);
            attron(COLOR_PAIR(5));
            mvaddch(food->y, food->x, FOOD_CHAR);
            attroff(COLOR_PAIR(5));
            curr_score += 10;
            }
            head = movement(head);
            co_update(head);
            napms(400);
            input();
           // erase();
      }

    clear();
    getch();
    free_all(&head);
	free(food);
    getch();
    endwin();
    if (head != NULL)
        printf("exists %p", head);
    printf("deleted all %p \n", head);
    return 0;
}
