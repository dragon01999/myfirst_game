#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ncurses.h>
#include"util.h"

void Food_gen(struct node *ptr, struct node *food)
{
      int x, y;
      bool status = TRUE;
	getmaxyx(stdscr, y, x);
  while (status == TRUE)  {
	srand(time(NULL)); //seed generator
        food->x = (rand() % x);
        food->y = (rand() % y);
        if (FD_IS_COLLIDING(ptr, food))
          status = TRUE;
        else
          status = FALSE;
  }
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

bool FD_IS_COLLIDING(struct node *ptr, struct node *food)
{
  while (ptr != NULL)  {
    if (ptr->x == food->x && ptr->y == food->y)
       return TRUE;
    ptr = ptr->next;
  }
  return FALSE;
}




void CO_UPDATE(struct node *ptr)
{
  int MAX_X, MAX_Y;
  node *second = NULL;
  second = ptr->next;
  getmaxyx(stdscr, MAX_Y, MAX_X);

  switch(CURRENT_DIR) {
    case RIGHT:
         if (ptr != NULL && ptr->next == NULL)  {
            ptr->x = 0;
            break;
        }
         else {
         ptr->x = (second->x + 1) % MAX_X;
         ptr->y = second->y;
         break;
         }
    case LEFT:
         if (second->x <= 0)  {
           ptr->x = MAX_X - 1;
           ptr->y = second->y;
           break;
         }
         ptr->x = second->x - 1;
         ptr->y = second->y;
         break;
    case UP:
         if (second->y <= 0)  {
           ptr->y = MAX_Y - 1;
           ptr->x = second->x;
           break;
         }
         ptr->y = second->y - 1;
         ptr->x = second->x;
         break;
    case DOWN:
         ptr->y = (second->y + 1) % MAX_Y;
         ptr->x = second->x;

    default:
         //Do nothing
         break;
  }
  second = NULL;
//  mvprintw(30, 4, "Y: %i X: %i", second->y, second->x);  refresh();
}

    
         








void collision(struct node *ptr)
{
  node *temp = ptr;
  while (ptr != NULL)  {
    ptr = ptr->next;
    if (ptr == NULL)
        return;
    if (temp->x == ptr->x && temp->y == ptr->y) {
       GAME_STATUS = FALSE;
       return;
    }
    
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
//    ptr->x = temp->x + 1; 
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


