#include "pid.h"
#include "motor.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "avr/io.h"
#include <avr/interrupt.h>



/*

PID_parameters_t *pid;
pid.K_p = 3;
pid.K_i = 1;
pid.K_d = 0.2;
pid.reference = 0;
pid.error = 0;
pid.prev_error = 0;

*/



//PID_parameters_t *pid;

float T = 0.01;//(1/PID_frequence); // 0.01 in time period
float I_term = 0;
float K_p = 1;
float K_i = 1.5; // 0.8
float K_d = 10; // 
int16_t error = -1;
int16_t prev_error = -1;
signed char reference = 0;

void PID_init(){
  
  /*Timer overflow interrupt is enabled*/
//  TIMSK5 |= (1<<TOIE5);


  /*Timer5 with 256 prescaler, timestep???*/
//  TCCR5B |= (1<<CS52);
//  TCCR5B &= ~(1<<CS51);
//  TCCR5B &= ~(1<<CS50);

//  int prescaler = 256;

  /*Timer overflow flag is cleared*/
//  TIFR5 |=(1<<TOV5);

//  TCNT5 = 0x00;

  /*Set TOP*/
//  int TOP = 625; // (F_CPU)/(prescaler*PID_frequence); // 625 ticks

//  printf("TOP: %d\n\r",TOP);

//  OCR5A = TOP;

  TCCR3A |= (1 << WGM32);
  TCCR3B |= (1<<CS52);
  TCCR3B &= ~(1<<CS51);
  TCCR3B &= ~(1<<CS50);
  int TOP = 625; // (F_CPU)/(prescaler*PID_frequence); // 625 ticks

 // printf("TOP: %d\n\r",TOP);

  OCR3A = TOP;
  TIMSK3 |= (1 << OCIE3A);
  
}

void PID_update_reference(signed char ref){
  reference = ref;
}


void PID_set_parameters(PID_parameters_t *pid, double K_p, double K_i, double K_d){
  pid->K_p = K_p;
  pid->K_i = K_i;
  pid->K_d = K_d;
  pid->error = -1;
  pid->prev_error = -1;
}


void PID_regulator(){
  signed char encoder_measurement = MOTOR_read_scaled_encoder(); //position

 // printf("Encoder: %d\n\r", encoder_measurement);

 // printf("Reference: %d\n\r", reference);
  
  error = reference - encoder_measurement;

//  printf("Error: %d\n\r", error);

  int P_term = error;

  I_term = I_term + error*T;

  /*
  
  if (I_term > MAX_I_TERM)
  {
    I_term = MAX_I_TERM;
  }
  else if (I_term < -MAX_I_TERM)
  {
    I_term = -MAX_I_TERM;
  }
  */


  if (abs(error) < 1)
  {
    I_term = 0;
  }


  int D_term = (error-prev_error)*PID_frequence;


  //printf("T %d\n\r", T);
  //printf("K_p: %d  K_i: %d   K_d: %d\n\r", P_term, I_term, D_term);


  int u = abs(K_p*P_term + K_i*I_term); //+ K_d*D_term);

///  int u = abs(K_p*P_term + K_d*D_term);

  uint8_t error_threshold = 1;

  if (abs(error) > error_threshold)
  {
    if (error < 0)
    {
      MOTOR_set_direction(0); //left
      if (u > MAX_SPEED)
      {
        u = MAX_SPEED;
      }
    }
    else
    {
      MOTOR_set_direction(1); //right
      if (u > MAX_SPEED)
      {
        u = MAX_SPEED;
      }
    }
  }

  MOTOR_set_speed(u);
  prev_error = error;

  //printf("PÅDRAG: %d\n\r", u);

}








/*

void PID_regulator(PID_parameters_t *pid){
  uint8_t optimizing_scaler = 128; 
  double T = (1/PID_frequence); // 0.01 in time period

  //Ziegler-N
  double T_k = 0.02; // random
  double T_i = T_k*0.5;
  double T_d = T_k*0.12;

  //Optimizing factor optimizes the compiler
  
  pid->K_i = optimizing_scaler*pid->K_p*T/T_i;

  pid->K_d = optimizing_scaler*pid->K_p*T_d/T;

  pid->K_p = optimizing_scaler*pid->K_p;
  

  signed char encoder_measurement = MOTOR_read_scaled_encoder(); //position
  
  pid->error = pid->reference - encoder_measurement;

  double P_term = pid->K_p*pid->error;

  I_term = I_term + pid->K_i*pid->error;

  if (I_term > MAX_I_TERM)
  {
    I_term = MAX_I_TERM;
  }
  else if (I_term < -MAX_I_TERM)
  {
    I_term = -MAX_I_TERM;
  }
  

  if (pid->error < 1)
  {
    I_term = 0;
  }

  double D_term = pid->K_d*(pid->error-pid->prev_error);


  uint8_t u = P_term + I_term + D_term;

  uint8_t error_threshold = 2;

  if (u < 255 && u > 0 && abs(pid->error) > error_threshold)
  {
    if (pid->error < 0)
    {
      MOTOR_set_direction(0); //left
      MOTOR_set_speed(u);
    }
    else
    {
      MOTOR_set_direction(1); //right
      MOTOR_set_speed(u);
    }
  }

  pid->prev_error = pid->error;

}
*/