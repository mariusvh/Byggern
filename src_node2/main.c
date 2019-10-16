#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"
#include "can.h"
#include "mcp_controll.h"
#include "MCP2515.h"

#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"


int main() {
  String_Init(MYUBRR);
  CAN_init(MODE_NORMAL);

  CAN_MESSAGE_t m_sent = CAN_construct_message("HELLO1",2,6);
  CAN_send_message(&m_sent);
  return 0;
}
