#ifndef MENU_H
#define MENU_H

#include <avr/io.h>
#include "joystick.h"

#define ARROW_COL 20
#define TITLE_COL 12
#define CHILD_COL 32

typedef struct MENU MENU_t;
typedef struct MENU_arrow MENU_arrow_t;

struct MENU
{
  char* menu_title;
  MENU_t* parent;
  MENU_t** child_array;

};

struct MENU_arrow
{
  int arrow_page;
  JOYSTICK_direction_t prev_dir;
  JOYSTICK_position_t prev_pos;
};


//

typedef enum
{
	MENU = 0,
	PLAY_PONG = 1,
  GAMEOVER = 2,
  PLAY_SNAKE = 3,
  PLAY_PONG_H = 4
}MENU_game_state_t;

//
MENU_t* MENU_set_new_menu(char* title, MENU_t* parent, uint8_t child_size);

void MENU_set_child(MENU_t *menu, MENU_t *child, uint8_t index);

void MENU_print_menu(volatile MENU_t *menu);

void MENU_init_menus(void);




void MENU_creation(MENU_t *main_menu, MENU_t *highscores, MENU_t *show_highscores, MENU_t *reset_highscores, MENU_t *start_new_game);

void MENU_arrow_creation(MENU_arrow_t *arrow);

void MENU_arrow_get_position(MENU_arrow_t *arrow);

JOYSTICK_direction_t MENU_move_arrow(MENU_arrow_t *arrow);

int MENU_set_arrow(MENU_arrow_t *arrow, uint8_t page, volatile MENU_t *menu);

void MENU_select_menu(MENU_arrow_t *arrow);

void MENU_main_menu(void);

void MENU_init(void);

void MENU_highscores(void);

void MENU_return(MENU_arrow_t *arrow);


//
uint8_t MENU_return_state();


void MENU_game_over();



#endif
