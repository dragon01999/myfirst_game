#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ncurses.h>
#include"util.h"

// Function to generate food
void food_gen(struct node *ptr, struct node *food)
{
      int x, y;
      bool status = TRUE;
      getmaxyx(stdscr, y, x);
      while (status == TRUE) {
         food->x = (rand() % x);
         food->y = (rand() % y);
         if (fd_is_colliding(ptr, food) || food->y == 0) 
			status = TRUE;
        else
            status = FALSE;
      }
      return;
}

// Function for printing body
void print_body(struct node *ptr)
{
 // int i = 12;
  node *a = ptr->next;
  attron(COLOR_PAIR(7));
  mvaddch(ptr->y, ptr->x, HEAD_CHAR);
  attroff(COLOR_PAIR(7));
  while (a != NULL) {
    attron(COLOR_PAIR(8));
    mvaddch(a->y, a->x, BODY_CHAR);
    attron(COLOR_PAIR(8));
    // mvprintw(i, 5, "x: %i, y: %i", a->x, a->y);
    //mvprintw(i+4, 5,"%i node: %p", i - 12, a);
  //  refresh();
//    i++;
    a = a->next;
  }
  a = NULL;
}

// Function to generate body
node* gen_body(struct node *ptr, int size)
{
  node *head = ptr;
  node *temp = NULL;
  for (int i = 0; i < size; i++) {
      temp = creat();
      temp->next = head;
      head = temp;
  }
  return head;
}

// Function to check wether food is generated on snake
bool fd_is_colliding(struct node *ptr, struct node *food)
{
  while (ptr != NULL) {
    if (ptr->x == food->x && ptr->y == food->y)
       return TRUE;
    ptr = ptr->next;
  }
  return FALSE;
}

// Update coordinates
void co_update(struct node *ptr)
{
  int MAX_X, MAX_Y;
  node *second = NULL;
  second = ptr->next;
  getmaxyx(stdscr, MAX_Y, MAX_X);

  switch(CURRENT_DIR) {
    case RIGHT:
         if (ptr != NULL && ptr->next == NULL)  {
            ptr->x = 0;
            ptr->y = 1;
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
         if (second->y <= 1)  {
           ptr->y = MAX_Y - 1;
           ptr->x = second->x;
           break;
         }
         ptr->y = second->y - 1;
         ptr->x = second->x;
         break;
    case DOWN: // capping y to 1 so i can use y 0
         if (second->y == MAX_Y - 1) {
             ptr->y = 1;
             ptr->x = second->x;
             break;
         }
         ptr->y = (second->y + 1) % MAX_Y;
         ptr->x = second->x;

    default:
         //Do nothing
         break;
  }
  second = NULL;
}

    
// Function to detect collision
void collision(struct node *ptr)
{
  int i = 0;
  node *temp = ptr;
  while (ptr != NULL) {
    ptr = ptr->next;
    if (ptr == NULL)
        return;
    if (i > 2)
        if (temp->x == ptr->x && temp->y == ptr->y) {
             GAME_STATUS = FALSE;
             return;
    }
    i++;
  }
    return;
}

// Function for movement
node* movement(struct node *ptr)
{
    TAIL_DELET(ptr);  //deletes tail
    int size = 1;
    ptr = gen_body(ptr, size);
//    mvprintw(15, 4, "x: %i", ptr->x);
//    refresh();
    return ptr;
}


