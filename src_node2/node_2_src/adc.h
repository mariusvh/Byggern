/**
 * @file adc.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the analog to digital converter(ADC)
 */

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>


/**
 * @brief Initializing the ADC. 
 */

void ADC_init();


/**
 * @brief Reads from the ADC registers.
 * 
 * @return uint16_t returns the read data.
 */
uint16_t ADC_read();


#endif