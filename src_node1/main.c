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

#define F_CPU 4915200
#include <util/delay.h>
#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main() {
  String_Init(MYUBRR);
  OLED_init_program();
  int btn_pressed = 0;

  MENU_arrow_t arrow;
  MENU_init_menus();
  MENU_arrow_creation(&arrow);

  CAN_init(MODE_NORMAL);

  CAN_MESSAGE_t *message;
  signed char prev_joystick_positions[2];
  //signed char prev_right_slider_position;
  //uint8_t prev_slider_position;
  while(1){
    //CAN_send_controllers(message);
    CAN_send_joystick_position(message, &prev_joystick_positions);
    //CAN_send_controllers_filter(message, &prev_right_slider_position, &prev_joystick_positions);

    //CAN_send_slider_position(message_slider, &prev_slider_position);
    //_delay_ms(500);

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
