#include "menu.h"
//#include "joystick.h"
#include "oled.h"
#include "stdio.h"
#include <stdlib.h>

volatile MENU_t *current_menu;

MENU_t* MENU_set_new_menu(char* menu_title, MENU_t* parent){
  MENU_t* new_menu;
  new_menu->menu_title = menu_title;
  new_menu->parent = parent;
  new_menu->child_array = malloc(sizeof(MENU_t*)*2);
  return new_menu;
}

void MENU_set_child(MENU_t *menu, MENU_t *child, uint8_t index){
  menu->child_array[index] = child;
}


void MENU_print_menu(MENU_t *menu){
  uint8_t title_col = 28;
  uint8_t title_page = 0;
  uint8_t title_size = 8;
  OLED_clear();
  OLED_set_start_page(title_page);
  OLED_set_col(title_col);

  if (&menu->menu_title != "MAIN MENU") {
    printf("ERROR: \n\r");
  }
  printf("PRINT: %s\n\r", menu->menu_title);


  OLED_print_string(menu->menu_title,title_size);

  uint8_t child_col = 40;

  for (size_t i = 0; i < sizeof(menu->child_array); i++) {
    OLED_set_start_page(2*i+2);
    OLED_set_col(child_col);
    OLED_print_string(menu->child_array[i]->menu_title, 5);
    printf("CHILD: %s\n\r",menu->child_array[i]->menu_title );
  }
}


volatile MENU_t *MENU_init_menus(void){
  MENU_t* main_menu = MENU_set_new_menu("MAIN MENU", NULL);
  MENU_t* highscores = MENU_set_new_menu("HIGHSCORES", main_menu);
  MENU_t* new_game = MENU_set_new_menu("START NEW GAME", main_menu);
  MENU_t* show_highscores = MENU_set_new_menu("SHOW HIGHSCORES", highscores);
  MENU_t* reset_highscores = MENU_set_new_menu("RESET HIGHSCORES", highscores);

  MENU_set_child(main_menu, new_game, 0);
  MENU_set_child(main_menu, highscores, 1);
  MENU_set_child(highscores, show_highscores,0);
  MENU_set_child(highscores,reset_highscores, 1);
  //maybe more children to come

  current_menu = main_menu;
  MENU_print_menu(main_menu);
  return current_menu;
}

void MENU_creation(MENU_t *main_menu, MENU_t *highscores, MENU_t *show_highscores, MENU_t *reset_highscores, MENU_t *start_new_game) {
  main_menu->menu_title = "MAIN MENU";
  main_menu->parent = NULL;
  main_menu->child_array = malloc(sizeof(MENU_t*)*2);
  main_menu->child_array[0] = highscores;
  main_menu->child_array[1] = start_new_game;

  highscores->menu_title = "HIGHSCORES";
  highscores->parent = main_menu;
  highscores->child_array = malloc(sizeof(MENU_t*)*2);
  highscores->child_array[0] = show_highscores;
  highscores->child_array[1] = reset_highscores;

  show_highscores->menu_title = "SHOW HIGHSCORES";
  show_highscores->parent = highscores;

  reset_highscores->menu_title = "RESET HIGHSCORES";
  reset_highscores->parent = highscores;

  start_new_game->menu_title = "START NEW GAME";
  start_new_game->parent = main_menu;
}

void MENU_arrow_creation(MENU_arrow_t *arrow){
  arrow->arrow_page = 2;
  arrow->prev_dir = NEUTRAL;
  arrow->prev_pos.x_position = 0;
  arrow->prev_pos.y_position = 0;
}

void MENU_arrow_get_position(MENU_arrow_t *arrow) {
  JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();
  arrow->prev_pos.x_position = joystick.x_position;
  arrow->prev_pos.y_position = joystick.y_position;
}

JOYSTICK_direction_t MENU_get_direction(MENU_arrow_t *arrow){
  JOYSTICK_direction_t dir = JOYSTICK_get_direction();
  switch (dir) {
    case DOWN:
      if (arrow->prev_dir == NEUTRAL){
        arrow->prev_dir = DOWN;
        if (arrow->arrow_page != 0) {
          MENU_set_arrow(arrow,arrow->arrow_page+1);
          arrow->arrow_page ++;
        }
        return DOWN;
      }
    case UP:
      if (arrow->prev_dir == NEUTRAL){
        arrow->prev_dir = UP;
        if (arrow->arrow_page != 7) {
          MENU_set_arrow(arrow,arrow->arrow_page-1);
          arrow->arrow_page --;
        }
        OLED_clear();
        return UP;
      }
    case NEUTRAL:
      return NEUTRAL;
    default:
      return -1;
  }
 }

void MENU_set_arrow(MENU_arrow_t *arrow, uint8_t page){
  if (page == arrow->arrow_page) {
    return;
  }
  else{
    OLED_set_start_page(arrow->arrow_page);
    OLED_set_col(28);
    OLED_print_string(" ",5);
    OLED_print_arrow(28,page);


  }
}

void MENU_main_menu(void){
  OLED_clear();
  OLED_set_start_page(0);
  OLED_set_col(28);
  OLED_print_string("MAIN MENU",8);
  OLED_set_start_page(2);
  OLED_set_col(40);
  OLED_print_string("START NEW GAME",5);
  OLED_set_start_page(4);
  OLED_set_col(40);
  OLED_print_string("HIGHSCORES",5);
}

void MENU_highscores(void){
  OLED_clear();
  OLED_set_start_page(0);
  OLED_set_col(28);
  OLED_print_string("HIGHSCORES",8);
  OLED_set_start_page(2);
  OLED_set_col(40);
  OLED_print_string("SHOW HIGHSCORES",5);
  OLED_set_start_page(4);
  OLED_set_col(40);
  OLED_print_string("RESET HIGHSCORES",5);

}

void MENU_init(void){
    MENU_main_menu();
  OLED_print_arrow(28,2);
}
