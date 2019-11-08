#include "servo.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

void SERVO_init(){
  uint8_t pwm_frec = 50;
  TIMER_init_fast_pwm(pwm_frec);
}

void SERVO_set_duty_cycle(uint8_t duty_cycle_us){
  TIMER_set_duty_cycle(duty_cycle_us);
}

void SERVO_set_position(signed char joystick_x, signed char prev_x){
    uint8_t duty_cycle = 150;
    //printf("T: %d\n\r", 0);
    uint8_t neutral_threshold = 15;
    uint8_t filter_threshold = 25;
    if (joystick_x > neutral_threshold){
      if (abs(joystick_x-prev_x) > filter_threshold) {
        duty_cycle = 150 - (0.5263* (joystick_x-5));
        printf("Duty_cycle: %d\n\r", duty_cycle);
        SERVO_set_duty_cycle(duty_cycle);
      }
    }

    else if (joystick_x < -neutral_threshold){
      if (abs(joystick_x-prev_x) > filter_threshold) {
        duty_cycle = 150 + (0.5263 * (-joystick_x-5));
        printf("Duty_cycle: %d\n\r", duty_cycle);
        SERVO_set_duty_cycle(duty_cycle);
      }
    }
    prev_x = joystick_x;

}
