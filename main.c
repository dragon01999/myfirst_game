#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
#include"util.h"

int curr_score = 0;
bool GAME_STATUS = TRUE;
Direction CURRENT_DIR = RIGHT;
int snake_size = 3;

int main(void)
{   
    // will intialize screen, input etc...
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLUE);
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    nodelay(stdscr, TRUE);
    node *head = NULL;
    node *food = NULL;
    food = creat();
    int size = 1;

    // Will intialize body
    for (int i = 0; i < INITIAL_SIZE; i++) {
        head = gen_body(head, size);
        co_update(head);
    }
        
    printw("Fine");
    // Generates intial food
    food_gen(head, food);
    //printing score and highest score on screen
    mvprintw(0, 3, "Hi");
    // Main game loop
      while (GAME_STATUS) {
//        input();
        clear();
        mvaddch(food->y, food->x, '@');
        collision(head);
        print_body(head);
        if (head->x == food->x && head->y == food->y) {
            snake_size += 1;
            head = gen_body(head, 1);
            co_update(head);
            food_gen(head, food);
            mvaddch(food->y, food->x, '@');
            refresh();
            curr_score += 10;
        }   
            attron(COLOR_PAIR(2));
            mvprintw(0, 4, "CURR_SCORE: %i", curr_score);
            attroff(COLOR_PAIR(2));
            refresh();
            head = movement(head);
            co_update(head);
            napms(1000/2);
            input();
    }

    clear();
    getch();
    free_all(&head);
    if (head != NULL)
        printw("exists %p", head);
    printw("deleted all %p", head);
    getch();
    endwin();
    return 0;
}
