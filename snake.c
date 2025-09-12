#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ncurses.h>
#include"util.h"

bool GAME_STATUS = TRUE;                               Direction CURRENT_DIR = RIGHT;

int main(void)  {
initscr();
noecho();
keypad(stdscr, TRUE);

node *list = NULL, *var, *temp = NULL;
//Initial body
			list = body_gen(list, 3);
			CO_UPDATE(list);
      print_body(list);
			getch();
			clear();
			for (int i = 0; i < 70; i++) {
				   list = movement(list);
					input();
					CO_UPDATE(list);
					clear();
					print_body(list);
					napms(100);
			}
			getch();
			endwin();
			return 0;

}
