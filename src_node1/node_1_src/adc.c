#include "adc.h"

#define F_CPU 4915200
#include "util/delay.h"

void ADC_init(void) {
  MCUCR |= (1 << SRE);
  SFIOR |= (1 << XMM2);
}

uint8_t ADC_read(uint8_t channel){
  volatile char *ext_adc = (char *) 0x1400; // Start address for the ADC
  ext_adc[0] = channel;
  _delay_us(40);
  return ext_adc[0];
}

uint8_t ADC_read_X_joystick(void){
	uint8_t ch1 = 4;
	uint8_t x = ADC_read(ch1);
	return x;
}


uint8_t ADC_read_Y_joystick(void){
	uint8_t ch2 = 5;
	uint8_t y = ADC_read(ch2);
	return y; // min y=0, max y=255,
}

uint8_t ADC_read_left_slider(void){
	uint8_t ch3 = 6;
	return ADC_read(ch3);
}

uint8_t ADC_read_right_slider(void){
	uint8_t ch4 = 7;
	return ADC_read(ch4);
}



