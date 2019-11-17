#include "mcp_controll.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include <stdio.h>
#include "ir.h"
#include "avr/io.h"
#include <avr/interrupt.h>


#ifndef F_CPU
#define F_CPU 16000000UL //Clock speed
#endif

void CAN_init(uint8_t mode){
  MCP_init();
  MCP_controll_write(mode, MCP_CANCTRL);
  uint8_t read = MCP_CONTROLL_read(MCP_CANCTRL);
  //printf("can control register:  %x \n\r", read);
 
  /*Interrupts*/
  MCP_bit_modify(MCP_CANINTE,0b00000011,0b11);
  MCP_bit_modify(MCP_CANINTF,0b00000011,0b00);

  /*Set interrupt to falling edge on PD2. The falling edge of INT2 generates asynchronously an interrupt request*/
  EICRA |= (1<<ISC01);

  /*Enable interupts on PD2*/
  EIMSK |= (1<<INT2);

  /*Clear interrupt flag on PD2*/
  EIFR |= (1<<INT2);

}

void CAN_construct_message(CAN_MESSAGE_t *message, signed char data, uint8_t id, uint8_t length){
  message->id = id;
  message->length = length;
  message->data[0] = data;
  /*
  for (size_t i = 0; i < length; i++) {
    message->data[i] = string[i];
  }
  */
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

  MCP_controll_write(id_high,MCP_TXB0SIDH + 16*buffer_number); //not sure about 0
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

  /*Taking care of interrupts*/
  uint8_t read = MCP_CONTROLL_read(MCP_CANINTF);
  if(read & (1<<0)) //RX0 int
    {
      read &= ~(1<<0);
    }

  if(read & (1<<5)) //ERRIF
    {
       read &= ~(1<<5);
    }
  MCP_controll_write(read, MCP_CANINTF);

  MCP_bit_modify(MCP_CANINTF,0b00000011,0b00);
}

/*

void CAN_send_score(CAN_MESSAGE_t *message){
  uint8_t id = 0;
  message->id = id;
  message->data[0] = IR_return_score(); //score
  message->length = 1;
  //Filter, we only send joystick position when new postion is set
  if (message->data[0] == 2) {
    CAN_send_message(message);
  }
  //Update prev_joystick_positions
  for (size_t i = 0; i < message->length; i++) {
    prev_joystick_positions[i] = message->data[i];
  }

}

*/