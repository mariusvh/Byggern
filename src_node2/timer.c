#include "timer.h"


void TIMER_init_fast_pwm(uint8_t pwm_frec){
    /*mode 14, fast PWM*/
    TCCR1B |= (1 << WGM13)|(1<<WGM12);
    TCCR1A |=(1<<WGM11);
    TCCR1A &= ~(1<<WGM10);

    int prescaler_divider = 256;
    /*Select clock source, prescaler divider = 256*/
    TCCR1B |= (1<<CS12);
    TCCR1B &= ~(1<<CS11);
    TCCR1B &= ~(1<<CS10);

    /*Interupt Flag cleared*/
    //OCF1A =

    /*PB5/OC1A set to output mode*/
    DDRB |= (1<<PB5);

    /*Compare Output Mode, inverting, fast pwm*/ //Update: change to non-inverting mode
    TCCR1A |= (1<<COM1A1);
    TCCR1A &= ~(1<<COM1A0);

    /*set TOP, maybe period related*/
    int TOP = (FOSC)/(prescaler_divider*pwm_frec) - 1;
    ICR1 = TOP; //1249

    /*duty cycle init*/
    OCR1A = (DUTY_MAX+DUTY_MIN)/2;
}

void TIMER_set_duty_cycle(float duty_cycle){
    int prescaler = 256;
    float duty_cycle_min = prescaler*(1+DUTY_MIN)/(FOSC);
    float duty_cycle_max = prescaler*(1+DUTY_MAX)/(FOSC);
    int duty_convert = FOSC*duty_cycle/prescaler - 1;

    if (duty_cycle >= duty_cycle_min && duty_cycle <= duty_cycle_max)
    {
        OCR1A = duty_convert;
    }
    else if(duty_cycle < duty_cycle_min)
    {
        OCR1A = DUTY_MIN;
    }
    else if(duty_cycle > duty_cycle_max)
    {
        OCR1A = DUTY_MAX;
    }
}
