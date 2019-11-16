#include "solenoid.h"
#include "util/delay.h"

void SOLENOID_init(){
    /*Set A3 to output to the solenoid*/
    DDRF |= (1<<PF3);
    PORTF |= (1<<PF3);
}

void SOLENOID_shoot(){
    PORTF &= ~(1<<PF3);
    _delay_ms(50);
    PORTF |= (1<<PF3);
}