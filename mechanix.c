#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ncurses.h>
#include"util.h"

void Food_gen(struct node *food)
{
      int x, y;
	getmaxyx(stdscr, y, x);
	srand(time(NULL)); //seed generator
        food->x = (rand() % x);
        food->y = (rand() % y);
	mvaddch(food->y, food->x, '@');
	refresh();
            return;
}

// Function for printing body
void print_body(struct node *ptr)
{
  int i = 12;
  node *a = ptr;
  while (a != NULL)  {
    mvaddch(a->y, a->x, 'o');
    mvprintw(i, 5, "x: %i, y: %i", a->x, a->y);
    mvprintw(i+4, 5,"%i node: %p", i - 12, a);
    refresh();
    i++;
    a = a->next;
  }
}

// Function to generate body.

node* body_gen(struct node *ptr, int size)
{
  node *head = ptr;
  node *temp = NULL;
  for (int i = 0; i < size; i++)  {
      temp = creat();
      temp->next = head;
      head = temp;
  }
  return head;
}

void CO_UPDATE(struct node *ptr)
{
  int x, y;

  getmaxyx(stdscr, y, x);
  node *second = ptr->next;
  if (ptr != NULL && ptr->next == NULL)  {
     ptr->x = 0;
     return;
  }
  else if (CURRENT_DIR == RIGHT)  {
     ptr->x = (second->x + 1) % x;
     ptr->y = second->y;
  }
 /* else if (CURRENT_DIR == UP)  {
        if (ptr->y == 0) {
        ptr->y = y;
        ptr->x = ptr->x;
        }
    ptr->x = second->x;
    ptr->y = ptr->y - 1;
      
  }*/
   else if (CURRENT_DIR == DOWN)  {
          ptr->y = second->y+1;
          ptr->x = second->x;
   }
   mvprintw(30, 4, "Y: %i X: %i", second->y, second->x);
refresh();
}

void collision(struct node *ptr)
{
  node *temp = ptr;
  while (ptr != NULL)  {
    if (temp->x == ptr->x && temp->y == ptr->y) {
       GAME_STATUS = FALSE;
       return;
    }
    ptr = ptr->next;
  }
       return;
}

/* Function for wrap-around
int WR_AROUND(struct node *ptr) 
{
  int MAX_X, MAX_Y;
  node *head = ptr;
  getmaxyx(stdscr, MAX_Y, MAX_Y);
  if (head->y == MAX_Y)
  {
    head->y = 0;
    return 1;
  }
  else if (head->x == MAX_X)
  {
    head->x = 0;
    return 2;
  }
    return 0; 
}
*/

// Function for movement
node* movement(struct node *ptr)
{
    TAIL_DELET(ptr);  //deletes tail
    int size = 1;
    node *temp = ptr;
//    WR_AROUND(ptr);
    // Create new head and update coordinates
    ptr = body_gen(ptr, size);
//    CO_UPDATE(ptr);
    ptr->x = temp->x + 1; 
   // int x, y;
   // getmaxyx(stdscr, y, x);
//    ptr->x = (temp->x + 1) % x;
  //  ptr->y = temp->y;
    /*int bl =  WR_AROUND(ptr);
    if (bl == 1)
      ptr->y = 0;
    else if (bl == 2) 
      ptr->x = 0; */
    mvprintw(15, 4, "x: %i", ptr->x);
    refresh();
//    getch();
    return ptr;
}


