#ifndef SLIDER_H
#define SLIDER_H

#include <avr/io.h>

#define MAX_JOYSTICK_VALUE 255
#define INITIAL_VALUE 127.5

typedef struct
{
	signed char right_slider;
	signed char left_slider;

}SLIDER_positions_t;

#endif
