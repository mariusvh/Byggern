#ifndef DAC_H
#define DAC_H

#include <avr/io.h>


void DAC_init();

void DAC_write(unsigned char data);

#endif