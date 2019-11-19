/**
 * @file timer.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for PWM timer.
 */

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

#define FOSC 16000000 //Clock speed
#define DUTY_MIN 61.5
#define DUTY_MAX 124


/**
 * @brief Initializes the timer for fast PWM.
 * 
 * @param pwm_frec The frequency of the PWM signal.
 */
void TIMER_init_fast_pwm(uint8_t pwm_frec);


/**
 * @brief Sets the duty cycle for the timer.
 * 
 * @param duty_cycle_us The duty cycle of the PWM signal.
 */
void TIMER_set_duty_cycle(uint8_t duty_cycle_us);

#endif