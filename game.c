#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "render.h"
#include "game.h"

Direction direction = RIGHT;
int game_status = 1;
int tail[2];
struct node food;
unsigned int score = 0;
int key = 0;

void die(const char *mesg)
{
    perror(mesg);
    exit(EXIT_FAILURE);
}

void free_nodes(struct node **snake)
{
    struct node *tmp = NULL;
    for (; *snake != NULL; *snake = tmp) {
        tmp = (*snake)->next;
        free(*snake);
    }
    snake = NULL;
}

void append_node(struct node **snake)
{
    struct node *tmp = NULL;
    tmp = malloc(sizeof(struct node) * 1);
    if (tmp == NULL) {
        free_nodes(snake);
        die("Malloc failed\n");
    }

    if (snake == NULL)
        *snake = tmp;
    else {
        tmp->next = *snake;
        *snake = tmp;
    }

}

//Its not deleting but making it the head
void delete_tail(struct node **snake)
{
    struct node *tmp = *snake;
    for (; (tmp != NULL && tmp->next != NULL); tmp = tmp->next)
        ;
    tail[0] = tmp->y;
    tail[1] = tmp->x;

    if (tmp != NULL) {
        *tmp = **snake; //we are assigning the previous first nodes coords
        tmp->next = *snake;
        *snake = tmp;
    }
    //make the current last node point to null instead of our current head
    for (tmp = *snake; tmp != NULL && tmp->next != *snake; tmp = tmp->next)
        ;
    if (tmp != NULL) {
        tmp->next = NULL;
    }
    tmp = (*snake)->next; //2Nd node
}

// this collison will check snake collision + food on wall or snake body
int collision(struct node *head, struct node *snake)
   
{
    if (head->y <= wall[0] || head->y >= wall[0] + BOARD_Y)
        return 1;
    if (head->x <= wall[1] || head->x >= wall[1] + BOARD_X)
        return 1;
        

    for (snake = snake->next; snake != NULL; snake = snake->next)
        if (head->x == snake->x && head->y == snake->y)
            return 1;

    return 0;
}

void take_input(int key)
{
    if (key == ERR)
        return;

    switch (key) {
        case KEY_UP:
            if (direction != DOWN)
                direction = UP;
            break;
        case KEY_DOWN:
            if (direction != UP)
                direction = DOWN;
            break;
        case KEY_RIGHT:
            if (direction != LEFT)
                direction = RIGHT;
            break;
        case KEY_LEFT:
            if (direction != RIGHT)
                direction = LEFT;
            break;
        case 'p':
            nodelay(stdscr, FALSE);
            do {
                //
            } while (getch() != 'p');
            nodelay(stdscr, TRUE);
            break;
        default:
            break;
    }
}
void move_snake(struct node *snake)
{
    switch (direction) {
        case UP:
            snake->y -= 1;
            break;
        case DOWN:
            snake->y += 1;
            break;
        case RIGHT:
            snake->x += 1;
            break;
        case LEFT:
            snake->x -= 1;
            break;
            break;
        default:
            break;
    }
}

void spawn_food(struct node *snake)
{
    do {
        food.y = wall[0] + (rand() % BOARD_Y) + 1;
        food.x = wall[1] + (rand() % BOARD_X) + 1;
    } while (collision(&food, snake));

}

void snake_consume_food(struct node **snake)
{
    if ((*snake)->y == food.y && (*snake)->x == food.x) {
        score += 10;
        spawn_food(*snake);
    //damn i messed up initially now to keep it simple i gotta add new seg in old tail coord
        struct node *tmp = NULL;
        append_node(snake);
        tmp = *snake;
        (*snake) = (*snake)->next;
        struct node *t = *snake;
        for (; t->next != NULL; t = t->next)
            ;
        t->next = tmp;
        tmp->y = tail[0];
        tmp->x = tail[1];
        tmp->next = NULL;
        //move_snake(*snake);*/
        
    }
}

void init_snake(struct node **snake)
{
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        append_node(snake);
        (*snake)->x = i + 1 + wall[1];
        (*snake)->y = 1 + wall[0];
    }
    spawn_food(*snake); //we are passing snake to make sure food doesnt get spawned on snake
}

void update_snake(struct node **snake)
{
    take_input(getch());
    delete_tail(snake);
    move_snake(*snake);
    game_status = !collision(*snake, *snake);
    snake_consume_food(snake);
}

void fps(unsigned int fps)
{
    napms(1000/fps);
}

