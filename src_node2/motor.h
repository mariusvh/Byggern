#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

#define MAX_JOYSTICK_VALUE 255
#define INITIAL_VALUE 127.5

void MOTOR_init();

uint16_t MOTOR_read_encoder();
void MOTOR_set_speed(unsigned char speed);

void MOTOR_set_direction(uint8_t direction);

void MOTOR_joystic_set_speed(signed char joy_y);

#endif