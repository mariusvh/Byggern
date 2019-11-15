#include "adc.h"

void ADC_init(){
    /*Set A0 to input from the photodiode */
    DDRF &= ~(1<<PF0);


    /*Enable ADC with 128 as prescaler*/
    ADCSRA |= (1<< ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) ;
    
    /*Set reference voltage to 2.56V*/
    ADMUX |= (1<<REFS1) | (1<<REFS0);

    /*left adjust ADC conversion*/
    ADMUX |= (1<<ADLAR);

    /*Read the photodiode signal*/
    ADC_read();
}

uint16_t ADC_read(){

    uint16_t read_data = 0;

    /*Start single conversion mode */
    ADCSRA |= (1<<ADSC);

    /* Wait for converting to complete */
    while(!(ADCSRA & (1<<ADIF)));
    
    /*Read ADC-registers*/
    uint8_t low_divider = 64;
    uint8_t high_multiplier = 4;
    uint8_t data_low = ADCL/low_divider;
    uint8_t data_high = ADCH*high_multiplier;

    read_data = data_low + data_high;
    return read_data;
}

