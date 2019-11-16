/**
 * @file adc.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the analog to digital converter(ADC)
 */


#ifndef ADC_H
#define ADC_H
#include <avr/io.h>

#define T_C 40
#define T_DS 0.1
#define T_DH 0.05
#define T_WI 0.4
#define T_RI 0.4


/**
 * @brief Initializing the ADC. 
 * Enables external memory and defines the length of the external memory adresses.
 * 
 */

void ADC_init(void);

/**
 * @brief Reads data on channel @p channel from the ADC.
 * 
 * @param[in] channel Which channel to read from.
 * @return uint8_t returns the data on the chosen channel.
 */
uint8_t ADC_read(uint8_t channel);

/**
 * @brief Reads the X-position of the joystick from the ADC.
 * 
 * @return uint8_t returns the X-position, a value between 0-255.
 */
uint8_t ADC_read_X_joystick(void);

/**
 * @brief Reads the Y-position of the joystick from the ADC.
 * 
 * @return uint8_t returns the Y-position, a value between 0-255.
 */
uint8_t ADC_read_Y_joystick(void);

/**
 * @brief Reads the position of the left slider from the ADC.
 * 
 * @return uint8_t returns the position of the left slider, a value between 0-255.
 */t8_t ADC_read_left_slider(void)


/**
 * @brief Reads the position of the right slider from the ADC.
 * 
 * @return uint8_t returns the position of the right slider, a value between 0-255.
 */
uint8_t ADC_read_right_slider(void);


#endif
