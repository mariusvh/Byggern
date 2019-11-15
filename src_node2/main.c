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
uint8_t run_pid = 1;

  uint8_t x_joustick_index = 0;
  uint8_t y_joystick_index = 1;
  uint8_t right_slider_index = 2;
  uint8_t left_slider_index = 3;
  uint8_t right_button_index = 4;
  int btn_pressed = 0;
  //uint8_t points = 0;
  int game_over = 0;


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
  SOLENOID_init();


  sei();
  //MOTOR_set_direction(0);
  //MOTOR_set_speed(10);
  //CAN_MESSAGE_t *m_rec;

  while (1)
  {
    if (IR_game_over() != 1)
    {
      if(run_pid){
        PID_regulator();
        run_pid = 0;
      }
    }
    
    //MOTOR_joystic_set_speed(m_rec->data[2]);
    //printf("motor read: %d\n\r", MOTOR_read_encoder());
    //printf("enc_scaled: %d\n\r", MOTOR_read_scaled_encoder());
    //_delay_ms(1000);

  }
  return 0;
}

ISR(INT2_vect){
  if (IR_game_over() != 1)
  {
    CAN_receive_message(0,m_rec);
    SERVO_set_position(m_rec->data[0]);
    PID_update_reference(m_rec->data[2]);
    if (btn_pressed == 0 && m_rec->data[right_button_index])
    {
      SOLENOID_shoot();
      //printf("Right button: %d\n\r",m_rec->data[right_button_index]);
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