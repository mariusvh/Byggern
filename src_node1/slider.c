#include "slider.h"
#include "adc.h"
#include <stdio.h>

SLIDER_positions_t SLIDER_get_scaled_position(void){
	SLIDER_positions_t sliders;

	uint8_t right_slider = ADC_read_right_slider();
	uint8_t left_slider = ADC_read_left_slider();

	sliders.right_slider = (signed char)(right_slider-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;
	sliders.left_slider = (signed char)(left_slider-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;
	//printf("Right slider: %d\n\r", sliders.right_slider);
 	//printf("Right_ADC: %d\n\r", right_slider);

	return sliders;
}


int SLIDER_right_button(){
	DDRB &= 0xFD;
	return (PINB & (1 << PB1))==2; //return 0 or 1
}

int SLIDER_left_button(){
	DDRB &= 0xFE;
	return (PINB & (1 << PB0))==1; //return 0 or 1
}
