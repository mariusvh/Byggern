#include "pid.h"
#include "motor.h"
#include "avr/io.h"
#include <avr/interrupt.h>

void PID_init(){
  /*Timer overflow interrupt is enabled*/
  TIMSK5 |= (1<<TOIE5);

  /*Timer5 with 256 prescaler, timestep???*/
  TCCR5B |= (1<<CS52);

  /*Timer overflow flag is cleared*/
  TIFR5 |=(1<<TOV5);
}

void PID_regulator(uint8_t speed_ref,uint8_t K_p, uint8_t K_i, uint8_t K_d){
  uint8_t u;
  uint8_t T;
  int16_t encoder_measurement = MOTOR_read_encoder();
  double 
  uint8_t error = ;

}


ISR(TIMER5_OVF_vect){
  cli();
  PID_regulator();
  sei();
}
