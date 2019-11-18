#ifndef SNAKE_H
#define SNAKE_H

typedef struct SNAKE_coordinate_t SNAKE_coordinate_t;


struct SNAKE_coordinate_t{
    int x;
    int y;
    int dir;
    int prev_dir;
};


uint8_t SNAKE_random(uint8_t min, uint8_t max);

void SNAKE_draw_border();

void SNAKE_draw_snake(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[]);

void SNAKE_draw_body(SNAKE_coordinate_t *b[]);

void SNAKE_draw_apple(SNAKE_coordinate_t *apple);

void SNAKE_clear_apple(SNAKE_coordinate_t *apple);

void SNAKE_eat(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[], SNAKE_coordinate_t *a);

void SNAKE_update_head(JOYSTICK_direction_t dir, SNAKE_coordinate_t *h);

void SNAKE_update_body(JOYSTICK_direction_t dir, SNAKE_coordinate_t *b[],SNAKE_coordinate_t *h);

void SNAKE_clear_snake();

void SNAKE_move(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[], SNAKE_coordinate_t *apple);

int SNAKE_game_over(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[]);

void SNAKE_game_ended();

void SNAKE_run();


#endif