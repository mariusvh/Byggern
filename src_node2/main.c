#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"
#include "can.h"
#include "mcp_controll.h"
#include "MCP2515.h"
#include "servo.h"
#include "ir.h"

#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"

int main() {
  String_Init(MYUBRR);
  CAN_init(MODE_NORMAL);
  SERVO_init();
 // printf("Score: %d\n\r", IR_count_scores());

  //CAN_MESSAGE_t m_send = CAN_construct_message("Node2",2,5);
  CAN_MESSAGE_t *m_rec;
/*
   SERVO_set_duty_cycle(100);
   _delay_ms(500);
   SERVO_set_duty_cycle(200);
   _delay_ms(500);
   SERVO_set_duty_cycle(150);
*/
  while (1)
  { 

    printf("HEO : \n\r");
    uint8_t points = IR_count_scores();
    printf("Score: %d \n\r", points);
    
    /*
    CAN_receive_message(0,m_rec);
    SERVO_set_position(m_rec->data[0]);
    printf("X: %d\n\r",m_rec->data[0]);
    */


    //_delay_ms(500);
  /*
   SERVO_set_duty_cycle(100);
   _delay_ms(500);
   SERVO_set_duty_cycle(200);
   _delay_ms(500);
   SERVO_set_duty_cycle(150);
  _delay_ms(500);
  */
 /*

  SERVO_set_position(90);
  _delay_ms(500);

  SERVO_set_position(-90);
  _delay_ms(500);
  */

  }
  
  return 0;
}
