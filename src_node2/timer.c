#include "timer.h"

void TIMER_init_fast_pwm(){
    /*mode 14, fast PWM*/
    TCCR1B |= (1 << WGM13)|(1<<WGM12);
    TCCR1A |=(1<<WGM11);
    TCCR1A &= ~(1<<WGM10); 

    uint8_t prescaler_divider = 256;
    /*Select clock source, prescaler divider = 256*/
    TCCR1B |= (1<<CS12);
    TCCR1B &= ~(1<<CS11);
    TCCR1B &= ~(1<<CS10);


    /*PB5/OC1A set to output mode*/
    DDRB |= (1<<PB5);

    /*Compare Output Mode, inverting, fast pwm*/
    TCCR1A |= (1<<COM1A1);
    TCCR1A |= (1<<COM1A0);

    /*set period*/
    uint8_t period = 20*10⁻3;
    ICR1 = period;

    /*duty cycle*/
    
    OCR1B 

}


