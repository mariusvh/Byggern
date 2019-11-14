#include "timer.h"
#include <stdio.h>
#define DUTY_MIN 61.5
#define DUTY_MAX 124


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

    /*PB5/OC1A set to output mode*/
    DDRB |= (1<<PB5);

    /*Compare Output Mode, inverting, fast pwm*/ //Update: change to non-inverting mode
    TCCR1A |= (1<<COM1A1);
    TCCR1A &= ~(1<<COM1A0);

    /*set TOP, period related*/
    int TOP = (FOSC)/(prescaler_divider*pwm_frec) - 1;
    ICR1 = TOP; //1249

    /*duty cycle init*/
    OCR1A = (DUTY_MAX+DUTY_MIN)/2;
}

void TIMER_set_duty_cycle(uint8_t duty_cycle_us){ 
    /*
    int prescaler = 256;
    uint8_t duty_cycle_min = 100000*prescaler*(1+DUTY_MIN)/(FOSC);
    printf("Duty_min: %d\n\r", duty_cycle_min);
    uint8_t duty_cycle_max = 100000*prescaler*(1+DUTY_MAX)/(FOSC);
    printf("Duty_max: %d\n\r",duty_cycle_max);
    uint8_t duty_cycle = duty_cycle_us;
    uint8_t duty_convert = FOSC*duty_cycle/(100000*prescaler) - 1;
    printf("Duty_conv: %d\n\r",duty_convert);
*/
    uint8_t duty_cycle_min = 100;
    uint8_t duty_cycle_max = 200;
    uint8_t duty_scaled = DUTY_MIN + (duty_cycle_us-duty_cycle_min)*(DUTY_MAX-DUTY_MIN)/(duty_cycle_max-duty_cycle_min);
    //printf("Duty_scaled: %d\n\r",duty_scaled);
    
    if(duty_scaled < DUTY_MIN)
    {
        OCR1A = DUTY_MIN;
        return;
    }

    if(duty_scaled > DUTY_MAX)
    {
        OCR1A = DUTY_MAX;
        return;
    }

    OCR1A = duty_scaled;
}

