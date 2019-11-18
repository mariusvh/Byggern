#ifndef MELODY_H
#define MELODY_H

#include <stdint.h>
#include <avr/io.h>


#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define DUTY_MIN 61.5
#define DUTY_MAX 124



void MELODY_init(uint8_t pwm_frec);

void MELODY_set_duty_cycle(uint8_t duty_cycle_us);

void MELODY_buzz(int frequency, int length);

void MELODY_play(int song_part);

#endif