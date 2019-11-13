#ifndef PID_H
#define PID_H

#include <avr/io.h>
#define F_CPU 16000000UL //Clock speed
#define PID_freq 100
#define MAX_I_TERM 20

typedef struct PID_parameters_t PID_parameters_t;

struct PID_parameters_t
{
    double K_p;
    double K_i;
    double K_d;
    double reference; //maybe not double
    double error;
    double prev_error;

};

void PID_init();
void PID_set_parameters(double K_p, double K_i, double K_d, double reference);
void PID_regulator(PID_parameters_t *pid);

#endif
