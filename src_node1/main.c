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

  //CAN_MESSAGE_t m_send = CAN_construct_message("node1",1,5);

  CAN_message_ptr m_rec;
  CAN_message_ptr message;
  JOYSTICK_position_t joystick;
  uint8_t id = 0;

  while(1){

    joystick = JOYSTICK_get_position_scaled();
      
    message->id = id;
    message->data[0] = joystick.x_position;
    message->data[1] = joystick.y_position;
    printf("X.joystick: %d\n\r",message->data[0]);
    printf("Y.joystick: %d\n\r",message->data[1]);
    message->length = 2;
    CAN_send_message(message);
    _delay_ms(30);
    id = id + 1;
    //CAN_receive_message(0,m_rec);
    //printf("Data: %s\n\r", m_rec.data);

    //CAN_send_joystick_position();
    //CAN_send_message(&m_send);
    //CAN_receive_message(0,&m_rec);
    //CAN_receive_message(0,&m_rec);
    //printf("X: %d\n\r",m_rec->data[0]);
    //printf("Y: %d\n\r",m_rec->data[1]);
    //_delay_ms(500);
   
    /*
    CAN_send_message(&m_send);
    CAN_receive_message(0,&m_rec);
    printf("Data: %s\n\r", m_rec.data);
    */

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
