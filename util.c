#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<ncurses.h>
#include"util.h"

// creates node
node* creat()
{
	node *n = malloc(sizeof(node));
	if (n == NULL)  {
	if (errno == ENOMEM)
		fprintf(stderr, "Error: Not enough memory.\n");
        else
		perror("Malloc failed");
	return NULL;
	}
	else  {
		n->next = NULL;
		return n;    // returns memory addr
}	}

// deletes node
void TAIL_DELET(node *ptr) 
{
	//Traverse till end of list and free tail
	node *temp = NULL;
	node *a = NULL;
	temp = ptr;
	while (temp != NULL) {
		if (temp->next == NULL)  {
			free(temp);
				a->next = NULL;
				return;
		}
		a = temp;
		temp = temp->next;
	}
	return;
}



// Handles input
void input()
{
	int key = getch();

	switch(key)  {
		
		case KEY_UP:
			if (CURRENT_DIR != DOWN)
			CURRENT_DIR = key;
			break;
    case KEY_DOWN:	
		  if (CURRENT_DIR != UP) 
			CURRENT_DIR = key;
			break;
		case KEY_LEFT:
			if (CURRENT_DIR != RIGHT)
			CURRENT_DIR = key;
			break;
		case KEY_RIGHT:
			if (CURRENT_DIR != LEFT)
			CURRENT_DIR = key;
	    break;
		case 'q':
			GAME_STATUS = FALSE;
			break;
		default:
			// Do nothing
			break;
	}

}
    // Function for freeing all nodes
void free_all(struct node **ptr)
{
    node *temp = *ptr;
    while (*ptr != NULL) {
        temp = temp->next;
        free(*ptr);
        *ptr = temp;
    }
    *ptr = NULL;  // preventing dangling pointers
}
        
