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
#include "spi.h"
#include "mcp_controll.h"
#include "can.h"
#include "MCP2515.h"

#define F_CPU 4000000
#include "util/delay.h"
#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main() {

  String_Init(MYUBRR);
  OLED_init_program();
  int btn_pressed = 0;
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

  //OLED_clear();
  MENU_arrow_t arrow;
  MENU_init_menus();
  MENU_arrow_creation(&arrow);
  CAN_init();
  //MCP_controll_write(170,MCP_TXB0CTRL);
  //uint8_t data = MCP_CONTROLL_read(MCP_CANSTAT);
  //printf("DATA: %d\n", data);

  while(1){
  //  MCP_controll_write(170,MCP_TXB0CTRL);
    MENU_move_arrow(&arrow);
    if (btn_pressed == 0 && SLIDER_right_button() || btn_pressed == 0 && SLIDER_left_button()){
      MENU_select_menu(&arrow);
      btn_pressed = 1;
    }
    if (!SLIDER_right_button() && !SLIDER_left_button()) {
      btn_pressed = 0;
    }

  }
  return 0;
}
