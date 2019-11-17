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
#include "solenoid.h"


#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include "util/delay.h"
#define F_CPU 16000000UL
#include "avr/io.h"
#include <avr/interrupt.h>

CAN_MESSAGE_t *m_rec;

CAN_MESSAGE_t *m_send;


uint8_t run_pid = 1;

uint8_t x_joustick_index = 0;
uint8_t y_joystick_index = 1;
uint8_t right_slider_index = 2;
uint8_t left_slider_index = 3;
uint8_t right_button_index = 4;

int btn_pressed = 0;
int game_over = 0;
uint8_t lives = 0;

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
  SOLENOID_init();

  sei();

  game_over = 0;
  static uint8_t score_limit = 2;

  while (1)
  { 

    lives = IR_count_scores();


    if (lives < score_limit)//IR_game_over() != 1)
    {
      //printf("run_pid: %d\n\r", run_pid);
      if(run_pid){
        PID_regulator();
        run_pid = 0;
      }
    }
     // After game
    else
    {

      if (!game_over)
      { 
        printf("Sending: %d\n\r",m_send->data[0]);
        CAN_construct_message(m_send, score_limit, 0, 1);
        CAN_send_message(m_send);
        game_over = 1;
        //score_limit = 0;
        //CAN_construct_message(m_send, score_limit, 0, 1);
        //CAN_send_message(m_send);
      }
      /* 
      printf("Sending: %d\n\r",m_send->data[0]);
      uint16_t score = IR_count_scores();
      CAN_construct_message(m_send, score, 1, 1);
      CAN_send_message(m_send);*/
    }


  }
  return 0;
}

ISR(INT2_vect){
  if (lives < 2)//IR_game_over() != 1)
  {
    CAN_receive_message(0,m_rec);
    SERVO_set_position(m_rec->data[0]);
    PID_update_reference(m_rec->data[2]);
    if (btn_pressed == 0 && m_rec->data[right_button_index])
    {
      SOLENOID_shoot();
      btn_pressed = 1;
    }
    if (!m_rec->data[right_button_index])
    {
      btn_pressed = 0;
    }
  }

  
}

ISR(TIMER3_COMPA_vect){
  run_pid = 1;
  //printf("TIMER3 \n\r");
  TCNT3 = 0x00;
}