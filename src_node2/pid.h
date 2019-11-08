#ifndef PID_H
#define PID_H

#include <avr/io.h>

void PID_init();

void PID_regulator(uint8_t speed_ref,uint8_t K_p, uint8_t K_i, uint8_t K_d);

#endif
