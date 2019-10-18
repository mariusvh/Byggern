#include "servo.h"
#include "timer.h"

void SERVO_init(){
  uint8_t pwm_frec = 50;
  TIMER_init_fast_pwm(pwm_frec);
}

void SERVO_set_duty_cycle(float duty_cycle){
  TIMER_set_duty_cycle(duty_cycle);
}
