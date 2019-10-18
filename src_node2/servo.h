#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

void SERVO_init();

void SERVO_set_duty_cycle(float duty_cycle);

#endif