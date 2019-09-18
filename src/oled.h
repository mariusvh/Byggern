#ifndef OLED_H
#define OLED_H

#include <avr/io.h>

void OLED_init_program();

void OLED_write_command(uint8_t command, uint8_t adress);

void OLED_write_data(uint8_t data, uint8_t adress);


#endif
