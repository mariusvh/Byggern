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
#include "pid.h"

#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"
#define F_CPU 16000000UL
#include "avr/io.h"
#include <avr/interrupt.h>

CAN_MESSAGE_t *m_rec;
uint8_t run_pid = 1;

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
  PID_init();
  int c = 0;


  sei();
  //MOTOR_set_direction(0);
  //MOTOR_set_speed(10);
  //CAN_MESSAGE_t *m_rec;

  while (1)
  {
    if(run_pid){
       PID_regulator();
       run_pid = 0;
    }
    else
    {
      MOTOR_read_scaled_encoder();
    }
    
    //uint8_t points = IR_count_scores();
    //printf("Score: %d \n\r", points);
    //MOTOR_joystic_set_speed(m_rec->data[2]);
    //printf("motor read: %d\n\r", MOTOR_read_encoder());
    //printf("enc_scaled: %d\n\r", MOTOR_read_scaled_encoder());
    //_delay_ms(1000);

  }
  return 0;
}

ISR(INT2_vect){
  //printf("CAN \n\r");
  //cli();
  CAN_receive_message(0,m_rec);
  //printf("Right_slider: %d\n\r", m_rec->data[]);
  SERVO_set_position(m_rec->data[0]);
  //printf("x: %d\n\r",m_rec->data[0]);
  //printf("y: %d\n\r",m_rec->data[1]);
  //printf("Right_slider: %d\n\r",m_rec->data[2]);
  PID_update_reference(m_rec->data[2]);
  //printf("Left_slider: %d\n\r",m_rec->data[3]);
  //sei();
}

ISR(TIMER3_COMPA_vect){
  run_pid = 1;
  //printf("TIMER3 \n\r");
  TCNT3 = 0x00;
}