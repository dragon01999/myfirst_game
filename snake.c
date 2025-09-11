#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
#include"util.h"

int main(void)  {

	initscr();
	noecho();
        node *food, *n, *ptr, *list = NULL;

         // Creating intial body
	  for (int i = 0; i < 4; i++)
          {
	      n = creat();
	      n->next = list;
	      n->x = i;
	      n->y = 0;
	      list = n;
          }

         // For printing body.
	  ptr = list;
	  node *trav = NULL;

	  for (int i = 0; i < 4; i++)  {
		mvprintw(10,5,"Node: %i & %i",ptr->x,ptr->y);
		mvaddch(ptr->y, ptr->x, 'o');
		trav = ptr->next;
		ptr = trav;
	//	mvprintw(0, i +2, "%i",i);
	  }
//        node *list = NULL;
         ptr = list;
         trav = NULL;
        // Movement:
        for (int i = 0; i < 8; i++)  {
        	movement(list);
		mvaddch(ptr->y, ptr->x, 'o');
                trav = ptr->next;
                ptr = trav;
                refresh();
                napms(100000/2);
        }

	getch();
	endwin();

}
