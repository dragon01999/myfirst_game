#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
#include"util.h"

bool GAME_STATUS = TRUE;
Direction CURRENT_DIR = RIGHT;

int main(int argc, char *argv[])  {

initscr();
noecho();
keypad(stdscr, TRUE);
mvprintw(3, 55, "h");
node *n, *list = NULL, *var;
int size = getch();
size -= '0';
	// Initial body:
//	list = body_gen(list, size); // working properly
//	print_body(list);
	var = list;
	//	int i = 0;
   mvprintw(0, 0, "start");
	 refresh();
    for(int i = 0; i < size; i++)  {
			var = body_gen(var, 1);
//		mvprintw(7, 2, "x:%i 2nd x:%i",list->x, var->x);	
			 CO_UPDATE(var);
//		 var = list->next;
		}
		getch();
		 mvprintw(2,2, "Fine");
		 refresh();
		 getch();
     print_body(var);
		 getch();

		// 2. Print the values using mvprintw (at specified coordinates)
    mvprintw(20, 0, "KEY_UP: %d", KEY_UP);
    mvprintw(21, 0, "KEY_DOWN: %d", KEY_DOWN);
    mvprintw(22, 0, "KEY_LEFT: %d", KEY_LEFT);
    mvprintw(23, 0, "KEY_RIGHT: %d", KEY_RIGHT);
    input();
		mvprintw(24, 0, "CURR_DIR: %i", CURRENT_DIR);
    // 3. Update the screen to show the changes
    refresh();

	  
//    TAIL_DELET(list);
	//	var = list;
	//	i = 0;

/*    var = list;
    i = 0;
    while(var->next != NULL)  {
      var->x = i;
      var->y = 0;
      var = var->next;
      i++;
      mvprintw(i + 5, 4, "Node %p \n", var);
    }*/
		refresh();
    getch();
	  clear();
		print_body(list);
		list = var;

		for (int i = 0; i < 70; i++) {
			input();
			list = movement(list);
			CO_UPDATE(list);
			clear();
			print_body(list);
			mvprintw(10, 5, "Head: %p",list);
			mvprintw(10, 5, "Head: %p, x: %i, y: %i",list, list->x, list->y);
			getch();	
			napms(100);
		}

		
	getch();
	endwin();
	return 0;
}
