#include "joystick.h"
#include "adc.h"
#include <math.h>
#include <stdlib.h>
#include "stdio.h"


static uint8_t x_initial_position, y_initial_position;

void JOYSTICK_Init(void){
	x_initial_position = ADC_read_X_joystick();
	y_initial_position = ADC_read_Y_joystick();

}


JOYSTICK_position_t JOYSTICK_get_position_scaled(void){
	ADC_init();
	JOYSTICK_position_t joystick;

	uint8_t x_value = ADC_read_X_joystick();
	uint8_t y_value = ADC_read_Y_joystick();
	printf("X_ADC: %d\n\r",x_value );
	printf("Y_ADC: %d\n\r",y_value );

	// scales between 99 and -99 for some reason, not 100 and -100
	joystick.x_position = (signed char)(x_value-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;
	joystick.y_position = (signed char)(y_value-INITIAL_VALUE)/(MAX_JOYSTICK_VALUE-INITIAL_VALUE)*100;
	//joystick.x_position = (int)(x_value*JOYSTICK_CONST-100);
	//joystick.y_position = (int)(y_value*JOYSTICK_CONST-100);

	return joystick;
}



JOYSTICK_direction_t JOYSTICK_get_direction(void){
	JOYSTICK_position_t joystick = JOYSTICK_get_position_scaled();

	uint8_t offset_value = 5;

	// returns error if x or y is 0
	double angle = atan2(joystick.y_position, joystick.x_position); // the function takes into account the sign of both arguments in order to determine the quadrant.
	angle = (int)angle*180/PI;
	if ((joystick.y_position <= offset_value && joystick.y_position >= -offset_value) && (joystick.x_position <= offset_value && joystick.x_position >= -offset_value)) {
		return NEUTRAL;
	}

	// limit value is 60 degrees, could change to 45

	if (angle >= 45 && angle <= 135) {
		return UP;
	}
	if (angle <= -45 && angle >= -135) {
		return DOWN;
	}
	if (angle <= 45 && angle >= -45) {
		return RIGHT;
	}
	if (angle >= 135 || angle <= -135) {
		return LEFT;
	}
}

int JOYSTICK_button(){
	DDRB &= 0xFB;
	return (PINB & (1 << PB2))==3;
}
