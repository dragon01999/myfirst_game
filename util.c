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
    exit(EXIT_FAILURE); // EXITS from the game
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
	node *temp = ptr;
	while (temp != NULL) {
		if (temp->next == NULL) {
			free(temp);
            ptr->next = NULL;
			return;
		}
        ptr = temp;
		temp = temp->next;
	}
	return;
} /* pointer "ptr" is importatnt here, it holds temp - 1 address. after deleting temp ptr which is temp - 1 after the first iteration, make sures after temp is deleted, a is not pointing to temp but has set its next as null. So basically it prevents dangling pointers */



// Handles input
void input()
{
	int key = getch();

	switch(key)  {
		
		case KEY_UP:
			if (CURRENT_DIR != DOWN) {
			CURRENT_DIR = key;
            }
			break;
        case KEY_DOWN:	
	    	if (CURRENT_DIR != UP) {
			CURRENT_DIR = key;
            }
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
        
