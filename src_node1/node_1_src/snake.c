#include "oled.h"
#include "SNAKE_8x8.h"
#include "joystick.h"
#include <stdlib.h>
#include <stdio.h>
#include "snake.h"
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"


int game_over = 0;
uint8_t score = 1;



uint8_t SNAKE_random(uint8_t min, uint8_t max){
    uint8_t rand_val = 0;
    uint8_t seed_rand_val = 0;

    for(uint8_t i=0; i<8; i++){
      seed_rand_val = seed_rand_val<<1 | (ADC_read(4)&0b1);
      }
    srand (seed_rand_val);

    rand_val = (rand()%(max+1 - min)) + min;

    return rand_val;

}

void SNAKE_draw_border(){
    OLED_clear();

    // Top border
    for (uint8_t i = 0; i < 127; i++)
    {
        OLED_set_start_page(1);
        OLED_set_col(i);
        for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[101][j]); //top
        OLED_write_data(char_out);
        }
    }
    // Bottom border
    for (uint8_t i = 0; i < 127; i++)
    {
        OLED_set_start_page(7);
        OLED_set_col(i);
        for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[102][j]); //top
        OLED_write_data(char_out);
        }
    }
    // Left Border
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_set_start_page(i);
        OLED_set_col(0);
        for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[103][j]); //left
        OLED_write_data(char_out);
        }
    }
    // Right Border
    for (uint8_t i = 0; i < 8; i++)
    {
        OLED_set_start_page(i);
        OLED_set_col(120);
        for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[104][j]); //right
        OLED_write_data(char_out);
        }
    }
}

void SNAKE_draw_snake(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[]){

    if (h->dir != h->prev_dir){
        switch (h->dir){
        case RIGHT:
            //print right head
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[96][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case LEFT:
            //print head left
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[97][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case UP:
            //print head up
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[98][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case DOWN:
            //print head down
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[99][j]);
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        }
    }
    else{
        switch (h->prev_dir){
        case RIGHT:
            //print right head
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[96][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case LEFT:
            //print head left
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[97][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case UP:
            //print head up
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[98][j]); 
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
        
        case DOWN:
            //print head down
            OLED_set_start_page(h->y);
            OLED_set_col(h->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[99][j]);
                OLED_write_data(char_out);
            }
            SNAKE_draw_body(b);
            break;
    
        }
    }
}

void SNAKE_draw_body(SNAKE_coordinate_t *b[]){
    for (uint8_t i = 0; i < score; i++)
    {
            OLED_set_start_page(b[i]->y);
            OLED_set_col(b[i]->x);
            for (uint8_t j = 0; j < 8; j++) {
                char char_out = (char) pgm_read_byte(&SNAKE_font8[100][j]); 
                OLED_write_data(char_out);
            }
    }
    
    
}


void SNAKE_draw_apple(SNAKE_coordinate_t *apple){
    OLED_set_start_page(apple->y);
    OLED_set_col(apple->x);
    for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[105][j]); //apple
        OLED_write_data(char_out);
    }
}

void SNAKE_clear_apple(SNAKE_coordinate_t *apple){
    OLED_set_start_page(apple->y);
    OLED_set_col(apple->x);
    for (uint8_t j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&SNAKE_font8[0][j]); //" "
        OLED_write_data(char_out);
    }
}

void SNAKE_eat(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[], SNAKE_coordinate_t *a){
    if (h->x == a->x && h->y == a->y) {
        SNAKE_coordinate_t elem;

        switch (b[score]->dir) //Decides coord and dir of the last body element
        {
        case UP:
            elem.x = b[score]->x;
            elem.y = b[score]->y + 1;

            elem.dir = b[score]->dir;
            elem.prev_dir = b[score]->dir;
            break;

        case DOWN:
            elem.x = b[score]->x;
            elem.y = b[score]->y - 1;

            elem.dir = b[score]->dir;
            elem.prev_dir = b[score]->dir;
            break;

        case LEFT:
            elem.x = b[score]->x - 8;
            elem.y = b[score]->y;

            elem.dir = b[score]->dir;
            elem.prev_dir = b[score]->dir;
            break;

        case RIGHT:
            elem.x = b[score]->x + 8;
            elem.y = b[score]->y;

            elem.dir = b[score]->dir;
            elem.prev_dir = b[score]->dir;

            break;
        
        default:
            break;
        }

        score++;
        *b[score] = elem;

        // Spawn new apple

        a->x = SNAKE_random(8,112); // next apple X coord in range [8,112]
        a->y = SNAKE_random(1,6); // next apple Y coord in range [1,6]
        SNAKE_clear_apple(a);
        SNAKE_draw_apple(a);
    }
}

void SNAKE_update_head(JOYSTICK_direction_t dir, SNAKE_coordinate_t *h){
    if (dir == h->prev_dir || dir == NEUTRAL)
    {
        h->dir = h->prev_dir; // Set new dir

        switch (h->prev_dir)
        {
        case UP:
            h->y ++;
            break;

        case DOWN:
            h->y --;
            break;

        case LEFT:
            h->x -= 8;
            break;
            
        case RIGHT:
            h->x += 8;
            break;
        
        default:
            break;
        }
    }
    
    switch (dir)
    {
    case UP:
        // Cant go from down --> up in one move
        if (h->prev_dir == DOWN)
        {
            SNAKE_update_head(NEUTRAL,h);
            break;
        }
        h->y ++;
        h->prev_dir = h->dir;
        h->dir = dir;
        break;

    case DOWN:
        // Cant go from up --> down in one move
        if (h->prev_dir == UP)
        {
            SNAKE_update_head(NEUTRAL,h);
            break;
        }
        h->y --;
        h->prev_dir = h->dir;
        h->dir = dir;
        break;

    case LEFT:
        // Cant go from right --> left in one move
        if (h->prev_dir == RIGHT)
        {
            SNAKE_update_head(NEUTRAL,h);
            break;
        }
        h->x -= 8;
        h->prev_dir = h->dir;
        h->dir = dir;
        break;

    case RIGHT:
        // Cant go from left --> right in one move
        if (h->prev_dir == LEFT)
        {
            SNAKE_update_head(NEUTRAL,h);
            break;
        }
        h->x += 8;
        h->prev_dir = h->dir;
        h->dir = dir;
        break;
    
    default:
        break;
    }
}

// Must run before SNAKE_update_body !!
void SNAKE_update_body(JOYSTICK_direction_t dir, SNAKE_coordinate_t *b[],SNAKE_coordinate_t *h){
        // Update 1st element according to head
        b[0]->x = h->x;
        b[0]->y = h->y;
        b[0]->prev_dir = b[0]->dir;
        b[0]->dir = h->dir;

        // Update the nth element according to the (n-1)th element 
        for (uint8_t i = 0; i < score-1; i++){
            b[i+1]->x = b[i]->x;
            b[i+1]->y = b[i]->y;
            b[i+1]->prev_dir = b[i+1]->dir;
            b[i+1]->dir = b[i]->prev_dir;
        }
        
}

void SNAKE_clear_snake(){
    for (uint8_t i = 1; i < 7; i++){ 
        for (uint8_t i = 8; i <= 112; i+=8){
            for (int j = 0; j < 8; j++) {
            char char_out = (char) pgm_read_byte(&SNAKE_font8[0][j]); //" "
            OLED_write_data(char_out);
            }
        }
    }
    
}

void SNAKE_move(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[], SNAKE_coordinate_t *apple){
    JOYSTICK_direction_t dir = JOYSTICK_get_direction();

    // Update the coordinates of the snake so it can be drawn right.
    SNAKE_update_body(dir,b,h);
    SNAKE_update_head(dir,h);

    // Clear board
    SNAKE_clear_snake();
    SNAKE_draw_apple(apple);

    // Draw apple and "new" snake
    SNAKE_draw_apple(apple);
    SNAKE_draw_snake(h,b);   

}

// Må ikke kjøres mellom SNAKE_update_body/head
int SNAKE_game_over(SNAKE_coordinate_t *h, SNAKE_coordinate_t *b[]){
    if (h->x > 119 || h->x < 8 || h->y < 1 || h->y > 6)
    {
        return 1;
    }
    for (int i = 0; i < score; i++)
    {
        if (h->x == b[i]->x && h->y == b[i]->y)
        {
            return 1;
        }
        
    }
    return 0;  
}

void SNAKE_game_ended(){

    OLED_clear();

    // Print GAME OVER
    OLED_set_start_page(1);
    OLED_set_col(16);
    OLED_print_string("GAME OVER",8);

    // Print Score: 
    OLED_set_start_page(3);
    OLED_set_col(32);
    OLED_print_string("SCORE:",8);

    // Print X Apples
    OLED_set_start_page(5);
    OLED_set_col(48);
    
    int tot_score = score-1;

    for (uint8_t j = 0; j < 8; j++) {
            char char_out = (char) pgm_read_byte(&SNAKE_font8[16+tot_score][j]); 
            OLED_write_data(char_out);
    }

    OLED_set_start_page(5);
    OLED_set_col(64);
    OLED_print_string("APPLES:",8);

    // Integrate with menu system
}

void SNAKE_run(){ // Make all values that might change to pointers.
    int game_over = 0;

    SNAKE_coordinate_t *head;
    head->x = 64;
    head->y = 3;
    head->dir = RIGHT;
    head->prev_dir = RIGHT;

    SNAKE_coordinate_t* body[250];
    SNAKE_coordinate_t *elem0;
    elem0->x = head->x - 8;
    elem0->y = head->y;
    elem0->dir = RIGHT;
    elem0->prev_dir = RIGHT;
    body[0] = elem0;

    SNAKE_coordinate_t *elem1;
    elem1->x = elem0->x - 8;
    elem1->y = elem0->y;
    elem1->dir = RIGHT;
    elem1->prev_dir = RIGHT;
    body[1] = elem1;

    SNAKE_coordinate_t *apple;
    apple->x = SNAKE_random(8,112); // next apple X coord in range [8,112]
    apple->y = SNAKE_random(1,6); // next apple Y coord in range [1,6]

    SNAKE_draw_border();
    SNAKE_draw_apple(apple);
    SNAKE_draw_snake(head,body);

    while (1)
    {
        SNAKE_move(head,body,apple);
        SNAKE_eat(head,body,apple);

        game_over = SNAKE_game_over(head,body);

    }

    // Game over
    SNAKE_game_ended();

}