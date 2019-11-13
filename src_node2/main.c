#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"
#include "can.h"
#include "mcp_controll.h"
#include "MCP2515.h"
#include "servo.h"
#include "ir.h"
#include "motor.h"

#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"
#define F_CPU 16000000UL
#include "avr/io.h"
#include <avr/interrupt.h>

CAN_MESSAGE_t *m_rec;
signed char prev_y;
//signed char prev_right_slider;
int main() {
  cli();
  String_Init(MYUBRR);
  CAN_init(MODE_NORMAL);
  SERVO_init();
  IR_init();
  MOTOR_init();
  MOTOR_encoder_init();
  MOTOR_read_scaled_encoder();

  sei();
  //MOTOR_set_direction(0);
  //MOTOR_set_speed(10);
  //CAN_MESSAGE_t *m_rec;

  while (1)
  {
    //printf("enc_scaled: %d\n\r", MOTOR_read_scaled_encoder());
    //MOTOR_set_speed(100);
    //uint8_t points = IR_count_scores();
    //MOTOR_read_encoder();
    //printf("Score: %d \n\r", points);

    //CAN_receive_message(0,m_rec);
    //SERVO_set_position(m_rec->data[0]);
    //MOTOR_joystic_set_speed(m_rec->data[1]);
    //printf("motor read: %d\n\r", MOTOR_read_encoder());
    //printf("Y: %d\n\r",m_rec->data[1]);

  }
  return 0;
}

ISR(INT2_vect){
  cli();
  CAN_receive_message(0,m_rec);
  //printf("Right_slider: %d\n\r", m_rec->data[]);
  //SERVO_set_position(m_rec->data[0], prev_y);
  //MOTOR_joystic_set_speed(m_rec->data[1]);
  printf("x: %d\n\r",m_rec->data[0]);
  printf("y: %d\n\r",m_rec->data[1]);
  //printf("Right_slider: %d\n\r",m_rec->data[2]);
 // printf("Left_slider: %d\n\r",m_rec->data[3]);
  sei();
}
