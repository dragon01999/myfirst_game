#ifndef MY_HEADER_H
#define MY_HEADER_H

extern bool GAME_STATUS;

    // Body of the snake
typedef struct node
{
    int x;
    int y;
    struct node *next;
} node;

    // Directions
typedef enum
{
    UP = KEY_UP,
    DOWN = KEY_DOWN,
    LEFT = KEY_LEFT,
    RIGHT = KEY_RIGHT,
} Direction;

extern Direction CURRENT_DIR; // Current direction

// For generating food on ramdom loc
void Food_gen(struct node *food);

    // body print
void print_body(struct node *ptr);

    // generation of body
node* body_gen(struct node *ptr, int size);

    // collision detection of head & body
void collision(struct node *ptr);

    // Direction and input handling
void input();

    // creating body
node* creat();

    // deleting body
void  TAIL_DELET(node *ptr);

    // Wrap-around
int WR_AROUND(struct node *ptr);

    // movement of the body
node* movement(struct node *ptr);

    // print body

#endif
