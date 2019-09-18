#include "slider.h"
#include "adc.h"

SLIDER_positions_t SLIDER_get_scaled_position(void){
	SLIDER_positions_t sliders;

	uint8_t right_slider = ADC_read_right_slider();
	uint8_t left_slider = ADC_read_left_slider();

	sliders.right_slider = (signed char)(right_slider-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;
	sliders.left_slider = (signed char)(left_slider-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;

	return sliders;
}


int SLIDER_right_button(){
	DDRB &= 0xFD;
	return (PINB & (1 << PB1))==2;
}

int SLIDER_left_button(){
	DDRB &= 0xFD;
	return (PINB & (1 << PB0))==1;
}
