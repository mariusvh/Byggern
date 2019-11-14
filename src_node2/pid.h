#ifndef PID_H
#define PID_H

#include <avr/io.h>
#define F_CPU 16000000UL //Clock speed

 
#define PID_frequence 100 // 100 Hz in frequency with 625 ticks
#define MAX_I_TERM 50


typedef struct PID_parameters_t PID_parameters_t;

struct PID_parameters_t
{
    double K_p;
    double K_i;
    double K_d;
    signed char reference; //maybe not double
    signed char error;
    signed char prev_error;
};

void PID_init();

void PID_set_parameters(PID_parameters_t *pid, double K_p, double K_i, double K_d);

void PID_update_reference(signed char ref);

void PID_regulator();

//void PID_regulator(PID_parameters_t *pid);

#endif
