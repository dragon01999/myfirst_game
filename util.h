#ifndef MY_HEADER_H
#define MY_HEADER_H

#define INITIAL_SIZE 14
extern bool GAME_STATUS;
extern char FOOD_CHAR;
extern char BODY_CHAR;
extern char HEAD_CHAR;
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
void food_gen(struct node *ptr, struct node *food);

    // body print
void print_body(struct node *ptr);

    // generation of body
node* gen_body(struct node *ptr, int size);

    // collision detection of head & body
void collision(struct node *ptr);

    // Direction and input handling
void input();

    // creating body
node* creat();

    // deleting body
void  TAIL_DELET(node *ptr);

    // movement of the body
node* movement(struct node *ptr);

    // print body

void co_update(struct node *ptr);


// checks if food is spawning on snake body
bool fd_is_colliding(struct node *ptr, struct node *food);

// Deleting all nodes
void free_all(struct node **ptr);

#endif
