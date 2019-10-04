#include "mcp_controll.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"


void CAN_init(){
  MCP_init();
//  MCP_controll_write( ,MCP_TXRTSCTRL);
  MCP_controll_write(MODE_LOOPBACK, MCP_CANCTRL);
  uint8_t read = MCP_CONTROLL_read(MCP_CANCTRL);
  printf("can control register:  %x \n\r", read);
}

void CAN_send_message(CAN_MESSAGE_t *message){
  /*message.id needs to be divided into SIDH and SIDL*/
  unsigned int id_high = message->id/8;
  unsigned int id_low = message->id%8;

  MCP_controll_write(id_high,MCP_TXB0SIDH); //not sure about 0
  MCP_controll_write(id_low << 5, MCP_TXB0SIDL);
  MCP_controll_write(message->length, MCP_TXB0DLC);

  for (uint8_t i = 0; i < message->length; i++) {
    MCP_controll_write(message->data[i], MCP_TXB0D0 + i);
  }
}
