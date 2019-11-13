#include "pid.h"
#include "motor.h"
#include <stdint.h>
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
double I_term = 0;


void PID_init(){
  /*Timer overflow interrupt is enabled*/
  TIMSK5 |= (1<<TOIE5);

  /*Timer5 with 256 prescaler, timestep???*/
  TCCR5B |= (1<<CS52);
  TCCR5B &= ~(1<<CS51);
  TCCR5B &= ~(1<<CS50);

  int16_t prescaler = 256;

  /*Timer overflow flag is cleared*/
  TIFR5 |=(1<<TOV5);

  /*Set TOP*/
  int TOP = (F_CPU)/(prescaler*PID_freq) - 1;
  ICR5 = TOP;

}

void PID_set_parameters(double K_p, double K_i, double K_d, double reference){
  PID_parameters_t *pid;
  pid->K_p = K_p;
  pid->K_i = K_i;
  pid->K_d = K_d;
  pid->reference = reference;
  pid->error = 0;
  pid->prev_error = 0;
}

void PID_regulator(PID_parameters_t *pid){
  uint8_t optimizing_scaler = 128; 
  uint16_t prescaler = 256;
  double frequency = F_CPU/prescaler;
  double T = (1/frequency)*100;
  double T_i = T/2;
  double T_d = T/8;
  pid->K_i = optimizing_scaler*pid->K_p*T/T_i;
  pid->K_d = optimizing_scaler*pid->K_p*T_d/T;
  pid->K_p = optimizing_scaler*pid->K_p;
 

  int16_t encoder_measurement = MOTOR_read_encoder();
  
  pid->error= encoder_measurement - pid->reference;

  double P_term = pid->K_p*pid->error;

  I_term = I_term + pid->K_i*pid->error;

  if (pid->error < 1)
  {
    I_term = 0;
  }

  double D_term = pid->K_d*(pid->error-pid->prev_error);
  int16_t u_signed = P_term + I_term + D_term;
  
  uint8_t u = P_term + I_term + D_term;

  if (u < 255)
  {
     MOTOR_set_speed(u);
  }

  pid->prev_error = pid->error;

}



/*


ISR(TIMER5_OVF_vect){
  cli();
  PID_regulator();
  sei();
}
*/