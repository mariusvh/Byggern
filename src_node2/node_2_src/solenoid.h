/**
 * @file spi.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for using the solenoid.
 */


#ifndef SOLENOID_H
#define SOLENOID_H

#include <avr/io.h>


#define F_CPU 16000000UL //Clock speed


/**
 * @brief Initializes the solenoid. 
 */
void SOLENOID_init();


/**
 * @brief Shoots the solenoid forward. 
 */
void SOLENOID_shoot();


#endif