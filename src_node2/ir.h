#ifndef IR_H
#define IR_H
#include <stdint.h>
#include <avr/io.h>

void IR_init();

uint16_t IR_digital_filter();

uint16_t IR_count_scores();

uint8_t IR_game_over();

#endif