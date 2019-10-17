#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"
#include "can.h"
#include "mcp_controll.h"
#include "MCP2515.h"


#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"

int main() {
  String_Init(MYUBRR);
  CAN_init(MODE_NORMAL);

  //CAN_MESSAGE_t m_send = CAN_construct_message("Node2",2,5);
  CAN_MESSAGE_t *m_rec;

  while (1)
  {
    CAN_receive_message(0,m_rec);
    printf("X: %d\n\r",m_rec->data[0]);
    printf("Y: %d\n\r",m_rec->data[1]);
  }
  
  return 0;
}
