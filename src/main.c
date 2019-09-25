#include "avr/io.h"
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"
#include "menu.h"

#define F_CPU 4000000
#include "util/delay.h"
#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main() {
/*
  MENU_t main_menu;
  MENU_t highscores;
  MENU_t start_new_game;
  MENU_t show_highscores;
  MENU_t reset_highscores;

  MENU_arrow_t arrow;

  MENU_creation(&main_menu, &highscores, &show_highscores, &reset_highscores, &start_new_game);
  MENU_arrow_creation(&arrow);
  MENU_init();
*/
  String_Init(MYUBRR);
  OLED_init_program();
  //OLED_clear();

  MENU_init_menus();


  while(1){

  }
  return 0;
}
