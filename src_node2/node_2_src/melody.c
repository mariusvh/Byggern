#include "melody.h"
#include "melodies.h"
#define __DELAY_BACKWARD_COMPATIBLE__
#include "util/delay.h"




void MELODY_init(uint8_t pwm_frec){
    /*mode 14, fast PWM*/
    TCCR5B |= (1 << WGM53)|(1<<WGM52);
    TCCR5A |=(1<<WGM51);
    TCCR5A &= ~(1<<WGM50);

    int prescaler_divider = 256;
    /*Select clock source, prescaler divider = 256*/
    TCCR5B |= (1<<CS52);
    TCCR5B &= ~(1<<CS51);
    TCCR5B &= ~(1<<CS50);

    /*PB5/OC1A set to output mode*/
    DDRH |= (1<<PH5);

    /*Compare Output Mode, inverting, fast pwm*/ //Update: change to non-inverting mode
    TCCR5A |= (1<<COM5A1);
    TCCR5A &= ~(1<<COM5A0);

    /*set TOP, period related*/
    int TOP = (FOSC)/(prescaler_divider*pwm_frec) - 1;
    ICR5 = TOP; //1249

    /*duty cycle init*/
    OCR5A = (DUTY_MAX+DUTY_MIN)/2;
}


void MELODY_set_duty_cycle(uint8_t duty_cycle_us){ 

    uint8_t duty_cycle_min = 100;
    uint8_t duty_cycle_max = 200;
    uint8_t duty_scaled = DUTY_MIN + (duty_cycle_us-duty_cycle_min)*(DUTY_MAX-DUTY_MIN)/(duty_cycle_max-duty_cycle_min);
    
    if(duty_scaled < DUTY_MIN)
    {
        OCR5A = DUTY_MIN;
        return;
    }

    if(duty_scaled > DUTY_MAX)
    {
        OCR5A = DUTY_MAX;
        return;
    }

    OCR5A = duty_scaled;
}

// Virker som man kan gjøre dette med PWM
void MELODY_buzz(int frequency, int length){
    // Calculate deleay between transistions, 1 sec /freq /2 phases per cycle.
    int delay_value = 1000000/frequency/2;

    //Total amount of cycles
    int num_cycles = frequency*length/1000;

    for (int i = 0; i < num_cycles; i++)
    {
        PORTH |= (1<<PH5);
        _delay_us(delay_value);
        PORTH &= ~(1<<PH5);
        _delay_us(delay_value);
    }
    
}


void MELODY_play(int song_part){
    if (song_part == 2 )
    {
        int size = sizeof(underworld_melody)/sizeof(int);

        for (int i = 0; i < size; i++)
        {
            int duration = 1000/underworld_tempo[i];
            MELODY_buzz(underworld_melody[i], duration);

            int pause = duration*1.30;
            _delay_us(pause);
            MELODY_buzz(0, duration);
        }
        
    }
    else
    {
        int size = sizeof(melody)/sizeof(int);

        for (int i = 0; i < size; i++)
        {
            int duration = 1000/tempo[i];
            MELODY_buzz(melody[i], duration);

            int pause = duration*1.30;
            _delay_us(pause);
            MELODY_buzz(0, duration);
        }
        
    }
    
    
}
