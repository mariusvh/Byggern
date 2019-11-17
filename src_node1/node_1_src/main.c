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
#include <avr/interrupt.h>

#define F_CPU 4915200
#include <util/delay.h>
#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



CAN_MESSAGE_t *m_receive;
CAN_MESSAGE_t *message;

MENU_game_state_t STATE = MENU;


int main() {
  cli();
  String_Init(MYUBRR);
  OLED_init_program();
  int btn_pressed = 0;

  MENU_arrow_t arrow;
  MENU_init_menus();
  MENU_arrow_creation(&arrow);

  CAN_init(MODE_NORMAL);

  sei();

 // m_receive->data[0] = 0;


  while(1){
    
    //printf("State: %d\n\r", STATE);

    switch (STATE)
    {
    case MENU:
      MENU_move_arrow(&arrow);
      if (btn_pressed == 0 && SLIDER_right_button() || btn_pressed == 0 && SLIDER_left_button()){
        MENU_select_menu(&arrow);
        btn_pressed = 1;
        STATE = MENU_start_game();
      }
      if (!SLIDER_right_button() && !SLIDER_left_button()) {
        btn_pressed = 0;
      } 
      break;

    case PLAY:
      //_delay_ms(100);
      CAN_send_controllers_filter(message);
      //printf("state: %d\n\r",STATE);
      break;

    case GAMEOVER:
      //printf("GAMEOVER");
      break;

    default:
      break;
    }
  }

  return 0;
}

ISR(INT2_vect){
  CAN_receive_message(0,m_receive);
  if (m_receive->data[0] > 1)
  {
    STATE = GAMEOVER;
    MENU_game_over();
  }
  printf("Received: %d\n\r", m_receive->data[0]);
}