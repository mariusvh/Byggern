#ifndef MENU_H
#define MENU_H

#include <avr/io.h>
#include "joystick.h"

typedef struct MENU_t MENU_t;
typedef struct MENU_arrow_t MENU_arrow_t;

struct MENU_t
{
	char* menu_title;
	MENU_t* parent;
  MENU_t** child_array;

};

struct MENU_arrow_t
{
  int arrow_page;
  JOYSTICK_direction_t prev_dir;
  JOYSTICK_position_t prev_pos;
};

MENU_t* MENU_set_new_menu(char* menu_title, MENU_t* parent);

void MENU_set_child(MENU_t *menu, MENU_t *child, uint8_t index);

void MENU_print_menu(MENU_t *menu);

volatile MENU_t *MENU_init_menus(void);




void MENU_creation(MENU_t *main_menu, MENU_t *highscores, MENU_t *show_highscores, MENU_t *reset_highscores, MENU_t *start_new_game);

void MENU_arrow_creation(MENU_arrow_t *arrow);

void MENU_arrow_get_position(MENU_arrow_t *arrow);

JOYSTICK_direction_t MENU_get_direction(MENU_arrow_t *arrow);

void MENU_set_arrow(MENU_arrow_t *arrow, uint8_t page);

void MENU_main_menu(void);

void MENU_init(void);
void MENU_highscores(void);
#endif
