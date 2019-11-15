#include "mcp_controll.h"
#include "spi.h"
#include "MCP2515.h"
#include "adc.h"
#include "can.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "joystick.h"
#include "slider.h"

signed char prev_joystick_positions[2];
signed char prev_right_slider_position;

void CAN_init(uint8_t mode){
  MCP_init();
  MCP_controll_write(mode, MCP_CANCTRL);
  uint8_t read = MCP_CONTROLL_read(MCP_CANCTRL);
  printf("can control register:  %x \n\r", read);
}


CAN_MESSAGE_t CAN_construct_message(char *string, uint8_t id, uint8_t length){
  CAN_MESSAGE_t message;
  message.id = id;
  message.length = length;
  for (size_t i = 0; i < length; i++) {
    message.data[i] = string[i];
  }
  return message;
}

void CAN_send_message(CAN_MESSAGE_t *message){
  static int buffer_number = 0;
  buffer_number +=1;
  if (buffer_number > 2){

    buffer_number = 0;
  }

  uint8_t SIDH_divider = 8;
  uint8_t SIDL_multiplier = 32;
  unsigned int id_high = message->id/SIDH_divider;
  unsigned int id_low = message->id%8;

  id_low = id_low*SIDL_multiplier;

  MCP_controll_write(id_high,MCP_TXB0SIDH + 16*buffer_number);
  MCP_controll_write(id_low, MCP_TXB0SIDL + 16*buffer_number);


  MCP_controll_write(message->length, MCP_TXB0DLC+ 16*buffer_number);

  for (uint8_t byte = 0; byte < message->length; byte++) {
    MCP_controll_write(message->data[byte], MCP_TXB0D0 + byte + 16*buffer_number);
  }
  switch (buffer_number) {
    case 0:
      MCP_controll_write(0x08, MCP_TXB0CTRL);
      break;
    case 1:
      MCP_controll_write(0x08, MCP_TXB1CTRL);
      break;
    case 2:
      MCP_controll_write(0x08, MCP_TXB2CTRL);
      break;
  }

  MCP_request_to_send(buffer_number);

}

void CAN_receive_message(int buffer_number, CAN_MESSAGE_t *message){
  unsigned int id_high = MCP_CONTROLL_read(MCP_RXB0SIDH+16*buffer_number);
  unsigned int id_low = MCP_CONTROLL_read(MCP_RXB0SIDL+16*buffer_number);
  id_low = (id_low & MODE_MASK);
  uint8_t SIDL_divider = 32;
  uint8_t SIDH_multiplier = 8;
  message->id = id_low/SIDL_divider + id_high*SIDH_multiplier;
  uint8_t mask = 0x0F;
  message->length = (MCP_CONTROLL_read(MCP_RXB0DLC+16*buffer_number) & mask);

  for (uint8_t byte = 0; byte < message->length; byte++) {
    message->data[byte] = MCP_CONTROLL_read(MCP_RXB0D0 + byte + 16*buffer_number);
  }

  switch (buffer_number) {
    case 0:
      MCP_controll_write(0,MCP_RX0IF);
      break;
    case 1:
      MCP_controll_write(0,MCP_RX1IF);
      break;
  }
  /*message.id needs to be divided into SIDH and SIDL*/
  id_high = message->id/8;
  id_low = message->id%8;

  MCP_controll_write(id_high,MCP_TXB0SIDH); //not sure about 0
  MCP_controll_write(id_low << 5, MCP_TXB0SIDL);
  MCP_controll_write(message->length, MCP_TXB0DLC);

  for (uint8_t i = 0; i < message->length; i++) {
    MCP_controll_write(message->data[i], MCP_TXB0D0 + i);
  }
}



void CAN_send_joystick_position(CAN_MESSAGE_t *message){
  JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();
  uint8_t id = 0;
  message->id = id;
  message->data[0] = joystick.x_position;
  message->data[1] = joystick.y_position;
  printf("X.joystick: %d\n\r",message->data[0]);
  printf("Y.joystick: %d\n\r",message->data[1]);
  message->length = 2;
  /*Filter, we only send joystick position when new postion is set*/
  uint8_t filter_threshold = 5;
  if ((abs(message->data[0])-abs(prev_joystick_positions[0]) > filter_threshold) || (abs(message->data[1])-abs(prev_joystick_positions[1]) > filter_threshold)) {
    CAN_send_message(message);
  }
  /*Update prev_joystick_positions*/
  for (size_t i = 0; i < message->length; i++) {
    prev_joystick_positions[i] = message->data[i];
  }

}

void CAN_send_controllers(CAN_MESSAGE_t *message){
  uint8_t right_slider = ADC_read_right_slider();
  uint8_t left_slider = ADC_read_left_slider();
  JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();

  uint8_t id = 0;
  message->id = id;
  message->data[0] = joystick.x_position;
  message->data[1] = joystick.y_position;
  message->data[2] = right_slider;
  message->data[3] = left_slider;
  message->length = 4;
  CAN_send_message(message);
}

void CAN_send_controllers_filter(CAN_MESSAGE_t *message){
  uint8_t right_slider = ADC_read_right_slider();
 // uint8_t left_slider = ADC_read_left_slider();
  JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();
  SLIDER_positions_t sliders = SLIDER_get_scaled_position();
  int right_button = SLIDER_right_button();

  uint8_t id = 0;
  message->id = id;
  message->data[0] = joystick.x_position;
  message->data[1] = joystick.y_position;
  message->data[2] = sliders.right_slider; //right_slider;
  message->data[3] = sliders.left_slider; //left_slider;
  message->data[4] = right_button; // 
  message->length = 5; //4
  //printf("x: %d\n\r", message->data[0]);
  //printf("Right button: %d\n\r", message->data[4]);
  
  //printf("y: %d\n\r", message->data[1]);
  printf("Right slider: %d\n\r", message->data[2]);
 // printf("Right_ADC: %d\n\r", right_slider);
  //printf("Left slider: %d\n\r", message->data[3]);
  /*Filter, we only send slider position when new postion is set*/
  uint8_t filter_threshold = 1;
  if (abs(message->data[2]-prev_right_slider_position) > filter_threshold) {
    prev_right_slider_position = message->data[2];
    CAN_send_message(message);

  }
  if ((abs(message->data[0]-prev_joystick_positions[0]) > filter_threshold) || (abs(message->data[1]-prev_joystick_positions[1]) > filter_threshold)) {
    CAN_send_message(message);
      /*Update prev_joystick_positions*/
    for (size_t i = 0; i < 2; i++) {
      prev_joystick_positions[i] = message->data[i];
    }
  }
  if (message->data[4] == 1)
  {
    CAN_send_message(message);
  }
  
}
