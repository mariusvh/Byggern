#include "menu.h"
//#include "joystick.h"
#include "oled.h"
#include "stdio.h"
#include <stdlib.h>
#include "slider.h"

#define F_CPU 4915200
#include <util/delay.h>

volatile MENU_t *current_menu;
volatile MENU_t *game_menu;
volatile MENU_t *main_global_menu;

uint8_t state = MENU;

volatile MENU_t *game_over_menu;

  MENU_t *main_menu;
  MENU_t *highscores;
  MENU_t *new_game;
  MENU_t *settings;
  MENU_t *show_highscores;
  MENU_t *reset_highscores;
  MENU_t *play_snake;
  MENU_t *snake_easy;
  MENU_t *snake_medium;
   // Starting game adding
  MENU_t *start_game;
  MENU_t *pong_easy;
  MENU_t *pong_medium;
  //
  //Game over
  MENU_t *game_over;
  // ADD :( FACE ON OLED
  

//

MENU_t* MENU_set_new_menu(char* title, MENU_t* parent, uint8_t child_size){
  MENU_t* new_menu = malloc(sizeof(MENU_t));
  new_menu->menu_title = title;
  new_menu->parent = parent;
  new_menu->child_array = malloc(sizeof(MENU_t*)*child_size);
  return new_menu;
}

void MENU_set_child(MENU_t *menu, MENU_t *child, uint8_t index){
  menu->child_array[index] = child;
}


void MENU_print_menu(volatile MENU_t *menu){
  printf("TITLE: %s\n\r", menu->menu_title);
  uint8_t title_page = 0;
  uint8_t title_size = 8;
  OLED_clear();
  OLED_set_start_page(title_page);
  OLED_set_col(TITLE_COL);
  OLED_print_string(menu->menu_title,title_size);

  uint8_t child_col = CHILD_COL;
  for (size_t i = 0; i < sizeof(menu->child_array); i++) {
    OLED_set_start_page(2*i+2);
    OLED_set_col(child_col);
    OLED_print_string(menu->child_array[i]->menu_title, 5);
  }
  //OLED_print_arrow(ARROW_COL,2);
}


void MENU_init_menus(void){

  main_menu = MENU_set_new_menu("MAIN MENU", NULL,3);
  highscores = MENU_set_new_menu("HIGHSCORES", main_menu,3);
  new_game = MENU_set_new_menu("START NEW GAME", main_menu,2);
  settings = MENU_set_new_menu("SETTINGS", main_menu,3);
  show_highscores = MENU_set_new_menu("SHOW HIGHSCORES", highscores,2);
  reset_highscores = MENU_set_new_menu("RESET HIGHSCORES", highscores,2);
  play_snake = MENU_set_new_menu("PLAY SNAKE", new_game,2);
  snake_easy = MENU_set_new_menu("EASY", play_snake,1);
  snake_medium = MENU_set_new_menu("HARDER", play_snake,1);
  // Starting game adding
  start_game = MENU_set_new_menu("PLAY PONG", new_game, 2);
  pong_easy = MENU_set_new_menu("EASY", start_game,1);
  pong_medium = MENU_set_new_menu("HARDER", start_game,1);
  //
  //Game over
  game_over = MENU_set_new_menu("GAME OVER :P", NULL, 0);
  // ADD :( FACE ON OLED

  game_over_menu = game_over;

  MENU_set_child(main_menu, new_game, 0);
  MENU_set_child(main_menu, highscores, 1);
  MENU_set_child(main_menu, settings, 2);

  // Starting game adding
  MENU_set_child(new_game,start_game,0);
  MENU_set_child(new_game,play_snake,1);

  MENU_set_child(play_snake,snake_easy,0);
  MENU_set_child(play_snake,snake_medium,1);
 

  MENU_set_child(start_game,pong_easy,0);
  MENU_set_child(start_game,pong_medium,1);
 


 // MENU_set_child(start_game,);
  game_menu = pong_easy;
  //
  MENU_set_child(highscores, show_highscores,0);
  MENU_set_child(highscores,reset_highscores, 1);
  //maybe more children to come
  main_global_menu = main_menu;
  current_menu = main_menu;
  MENU_print_menu(current_menu);
}

/*void MENU_creation(MENU_t *main_menu, MENU_t *highscores, MENU_t *show_highscores, MENU_t *reset_highscores, MENU_t *start_new_game, MENU_t *play_snake) {
  main_menu->menu_title = "MAIN MENU";
  main_menu->parent = NULL;
  main_menu->child_array = malloc(sizeof(MENU_t*)*2);
  main_menu->child_array[0] = highscores;
  main_menu->child_array[1] = start_new_game;
  printf("%s\n",main_menu->menu_title);

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

  play_snake->menu_title = "PLAYING SNAKE";
  play_snake->parent = start_new_game;

}*/

void MENU_arrow_creation(MENU_arrow_t *arrow){
  arrow->arrow_page = 2;
  arrow->prev_dir = NEUTRAL;
  arrow->prev_pos.x_position = 0;
  arrow->prev_pos.y_position = 0;
  OLED_print_arrow(ARROW_COL,2);
}

void MENU_arrow_get_position(MENU_arrow_t *arrow) {
  JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();
  //arrow->prev_pos.x_position = joystick.x_position;
  arrow->prev_pos.y_position = joystick.y_position;
}

JOYSTICK_direction_t MENU_move_arrow(MENU_arrow_t *arrow){
  JOYSTICK_direction_t dir = JOYSTICK_get_direction();
  switch (dir) {
    case DOWN:
      if (arrow->prev_dir == NEUTRAL){
        arrow->prev_dir = DOWN;
        if (MENU_set_arrow(arrow,arrow->arrow_page+2,current_menu)){
          arrow->arrow_page += 2;
        }
        return DOWN;
      }
    case UP:
      if (arrow->prev_dir == NEUTRAL){
        arrow->prev_dir = UP;
        if (MENU_set_arrow(arrow,arrow->arrow_page-2,current_menu)) {
          arrow->arrow_page -= 2;
        }
        return UP;
      }
    case NEUTRAL:
      MENU_set_arrow(arrow, arrow->arrow_page,current_menu);
      arrow->prev_dir = NEUTRAL;
      return NEUTRAL;
    default:
      return -1;
  }
 }


int MENU_set_arrow(MENU_arrow_t *arrow, uint8_t page, volatile MENU_t *menu){
  if (page <= 0) {
    return 0;
  }
  else if (page >= 5) {
    return 0;
  }
  else{
    OLED_set_start_page(arrow->arrow_page);
    OLED_set_col(ARROW_COL);
    OLED_print_string(" ",5);
    OLED_print_arrow(ARROW_COL,page);
    return 1;
  }
}

void MENU_select_menu(MENU_arrow_t *arrow){
  if (!SLIDER_right_button() && !SLIDER_left_button()) {
    return;
  }
  if (SLIDER_right_button()) {
    for (size_t i = 0; i < sizeof(current_menu->child_array); i++) {
      if ((arrow->arrow_page/2 - 1) == i) {
        current_menu = current_menu->child_array[i];
        MENU_print_menu(current_menu);
        // Starting game
        if (current_menu == pong_easy)
        {
          state = PLAY_PONG;
        }
        if (current_menu == pong_medium)
        {
          state = PLAY_PONG_H;
        }
        //
      }
    }
  }
  if (SLIDER_left_button()) {
    if (current_menu->parent != NULL) {
      current_menu = current_menu->parent;
      MENU_print_menu(current_menu);
    }
  }
}

//

uint8_t MENU_return_state(){
  return state;
}



void MENU_game_over(){

    MENU_print_menu(game_over_menu);

    _delay_ms(5000);
    //current_menu = main_global_menu;
    //MENU_init_menus();
    //MENU_arrow_creation(&arrow);
    //MENU_select_menu(&arrow);
}



void MENU_return(MENU_arrow_t *arrow){
    OLED_clear();
    //MENU_init_menus();
    current_menu = main_menu;
    MENU_print_menu(main_menu);
    MENU_arrow_creation(arrow);
    state = MENU;
}


  
