#include "mcp_controll.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include <stdio.h>

void CAN_init(){
  MCP_init();
//  MCP_controll_write( ,MCP_TXRTSCTRL);
  MCP_controll_write(MODE_LOOPBACK, MCP_CANCTRL);




  uint8_t read = MCP_CONTROLL_read(MCP_CANCTRL);
  printf("can control register:  %x \n\r", read);
}

void CAN_send_message(CAN_MESSAGE_t *message){


  /*message.id needs to be divided into SIDH and SIDL*/
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
}
