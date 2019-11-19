/**
 * @file servo.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for actuating the servo.
 */

#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>


/**
 * @brief Initializes the servo. 
 */
void SERVO_init();


/**
 * @brief Sets the duty cycle of the servo, ie. the angle of the servo.
 * 
 * @param duty_cycle_us The duty cycle/angle that the servo gets.
 */
void SERVO_set_duty_cycle(uint8_t duty_cycle_us);


/**
 * @brief Sets the duty cycle of the servo according to the x position of the joystick.
 * 
 * @param joystick_x The joystick X-position.
 */
void SERVO_set_position(signed char joystick_x);

#endif
