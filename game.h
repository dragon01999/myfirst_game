#ifndef GAME_H
#define GAME_H

typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
} Direction;

struct node {
    int x;
    int y;
    struct node *next;
};

extern int wall[2];

void die(const char *mesg);

void append_node(struct node **snake);

void free_nodes(struct node **snake);

void move_snake(struct node *snake);

void delete_tail(struct node **snake);

int collision(struct node *head, struct node *snake);

void take_input(int key);

void spawn_food(struct node *snake);

void snake_consume_food(struct node **snake);

void init_snake(struct node **snake);

void update_snake(struct node **snake);

void fps(unsigned int fps);

#endif
