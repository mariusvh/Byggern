/**
 * @file slider.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for utilizing the slider features.
 */

#ifndef SLIDER_H
#define SLIDER_H

#include <avr/io.h>

#define MAX_JOYSTICK_VALUE 255
#define INITIAL_VALUE 127.5



/**
 * @brief Structures representing the slider positions.
 *
 */
typedef struct
{
	signed char right_slider; /**< The position of the right slider. */
	signed char left_slider; /**< The position of the left slider. */

}SLIDER_positions_t;



/**
 * @brief Scales the values from the ADC from the range [0,255] to [-100,100]
 * 
 * @return SLIDER_positions_t returns a struct with the right and left slider position.
 */
SLIDER_positions_t SLIDER_get_scaled_position(void);


/**
 * @brief Checks wheter the slider right button is pressed down.
 *
 * @return int returns "1" if the button is pressed down, and "0" otherwise.
 */
int SLIDER_right_button();


/**
 * @brief Checks wheter the slider left button is pressed down.
 *
 * @return int returns "1" if the button is pressed down, and "0" otherwise.
 */
int SLIDER_left_button();

#endif
