#include "avr/io.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/delay.h>
#include "spi.h"
#include "can.h"
#include "mcp_controll.h"
#include "MCP2515.h"

#include "util/delay.h"
#define FOSC 16000000 //Clock speed
#ifndef F_CPU
#define F_CPU 16000000UL //Clock speed
#endif
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int main() {
  String_Init(MYUBRR);
  /*CAN_init(MODE_LOOPBACK); */

  SPI_master_init();



  while(1){
    MCP_controll_write(0xaf, MCP_CANCTRL);

    _delay_ms(10);

    uint8_t data =  MCP_CONTROLL_read(MCP_CANCTRL);

    printf("Data from control reg: %x \n\r", data);

    _delay_ms(1000);
}

  /*CAN_MESSAGE_t m = CAN_construct_message("Node2m",3,6);
  printf("M: %s\n\r", m.data);
  CAN_MESSAGE_t m_rec;
  CAN_send_message(&m);

  CAN_receive_message(0, &m_rec);
  printf("Data: %s\n\r",m_rec.data);
  */
  //printf("Hello world!\n\r");
  return 0;
}
