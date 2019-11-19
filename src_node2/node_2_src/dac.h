/**
 * @file dac.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the digital to analog converter(DAC)
 */


#ifndef DAC_H
#define DAC_H

#include <avr/io.h>


/**
 * @brief Initializing the DAC. 
*/
void DAC_init();


/**
 * @brief Writes the data from @p data to the DAC.
 * 
 * @param data Data to be written to the DAC.
 */
void DAC_write(unsigned char data);

#endif