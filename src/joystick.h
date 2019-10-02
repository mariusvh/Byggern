#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

#define MAX_JOYSTICK_VALUE 255
#define INITIAL_VALUE 127.5
#define JOYSTICK_CONST 0.78431
#define PI 3.14159

typedef struct
{
	signed char x_position;
	signed char y_position;

}JOYSTICK_position_t;

typedef enum
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	NEUTRAL = 4
}JOYSTICK_direction_t;

void JOYSTICK_Init(void);


JOYSTICK_position_t JOYSTICK_get_position_scaled(void);

JOYSTICK_direction_t JOYSTICK_get_direction(void);

int JOYSTICK_button();


#endif
