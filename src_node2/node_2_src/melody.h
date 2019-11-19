/**
 * @file melody.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for playing melodies.
 */


#ifndef MELODY_H
#define MELODY_H

#include <stdint.h>
#include <avr/io.h>


#define F_CPU 16000000UL //Clock speed
#define FOSC 16000000 //Clock speed
#define DUTY_MIN 61.5
#define DUTY_MAX 124


/**
 * @brief Initializes a timer and PWM.
 * 
 *  @param pwm_frec The frequency of the PWM signal to be generated.
 */
void MELODY_init(uint8_t pwm_frec);


/**
 * @brief Sets the duty cycle for the PWM signal.
 * 
 *  @param duty_cycle_us The duty cycle of the PWM signal to be generated.
 */
void MELODY_set_duty_cycle(uint8_t duty_cycle_us);


/**
 * @brief Applies the PWM signal on the piezo buzzer.
 * 
 * @param frequency The frequency of the melody to be played.
 * 
 * @param length The length of the tones in melody to be played.
 */
void MELODY_buzz(int frequency, int length);


/**
 * @brief Plays the melody part by part.
 * 
 *  @param song_part The song part to be played.
 */
void MELODY_play(int song_part);

#endif