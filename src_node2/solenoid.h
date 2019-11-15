#ifndef SOLENOID_H
#define SOLENOID_H

#include <avr/io.h>


#define F_CPU 16000000UL //Clock speed



void SOLENOID_init();

void SOLENOID_shoot();


#endif