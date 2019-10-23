#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

#define FOSC 16000000 //Clock speed
#define DUTY_MIN 61.5
#define DUTY_MAX 124

void TIMER_init_fast_pwm(uint8_t pwm_frec);

void TIMER_set_duty_cycle(uint8_t duty_cycle_us);

#endif