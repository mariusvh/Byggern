#include "servo.h"
#include "timer.h"
#include <stdio.h>

void SERVO_init(){
  uint8_t pwm_frec = 50;
  TIMER_init_fast_pwm(pwm_frec);
}

void SERVO_set_duty_cycle(uint8_t duty_cycle_us){
  TIMER_set_duty_cycle(duty_cycle_us);
}

void SERVO_set_position(signed char joystick_x){
    uint8_t duty_cycle = 150;
    //printf("T: %d\n\r", 0);
  
    if (joystick_x > 5){

      duty_cycle = 150 - (0.5263* (joystick_x-5));
      printf("Duty_cycle: %d\n\r", duty_cycle);
      SERVO_set_duty_cycle(duty_cycle);
      printf("T2: %d\n\r",2);
    }

    else if (joystick_x < -5){

      duty_cycle = 150 + (0.5263 * (-joystick_x-5));
      printf("Duty_cycle: %d\n\r", duty_cycle);
      SERVO_set_duty_cycle(duty_cycle);
      printf("T3: %d\n\r",3);
    }

}

