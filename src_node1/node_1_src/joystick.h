/**
 * @file joystick.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Functions that utilize the ADC to enable more sofisticated use of the joystick.    
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

#define MAX_JOYSTICK_VALUE 255
#define INITIAL_VALUE 127.5
#define JOYSTICK_CONST 0.78431
#define PI 3.14159


/**
 * @brief A structure to represent the X- and Y-position of the joystick.
 * 
 */
typedef struct
{
	signed char x_position; /**< The X-position of the joystick. */
	signed char y_position; /**< The Y-position of the joystick. */

}JOYSTICK_position_t;


/*! This is an enum for the joystick directions*/
typedef enum
{
	UP = 0, /*!< Joystick directed UP */
	DOWN = 1, /*!< Joystick directed DOWN */
	LEFT = 2, /*!< Joystick directed LEFT */
	RIGHT = 3, /*!< Joystick directed RIGHT */
	NEUTRAL = 4 /*!< Joystick in NEUTRAL direction */
}JOYSTICK_direction_t;


/**
 * @brief Reads joystick position through the ADC.
 * 
 */
void JOYSTICK_Init(void);

/**
 * @brief Scales the X- and Y-postion from the range [0,255] to the range [-100,100]
 * 
 * @return JOYSTICK_position_t returns the scaled joystick position.
 */
JOYSTICK_position_t JOYSTICK_get_position_scaled(void);

/**
 * @brief Calculates the direction of the joystick from 
 the angle between the X- and Y-position of the joystick.
 * 
 * @return JOYSTICK_direction_t returns the direction of the joystick.
 */
JOYSTICK_direction_t JOYSTICK_get_direction(void);

/**
 * @brief Checks if the joystick button is pressed.
 * 
 * @return int returns 1 if the button is pressed down and 0 otherwise.
 */
int JOYSTICK_button();


#endif
