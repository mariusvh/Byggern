#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

void SERVO_init();

void SERVO_set_duty_cycle(uint8_t duty_cycle_us);

void SERVO_set_position(signed char joystick_x, signed char prev_x);

#endif
