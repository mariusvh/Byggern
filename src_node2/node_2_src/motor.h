/**
 * @file motor.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for actuating the motor.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

#define F_CPU 16000000UL //Clock speed

#define MAX_JOYSTICK_VALUE 64
#define INITIAL_VALUE 32


/**
 * @brief Initializes the motor. 
 */
void MOTOR_init();


/**
 * @brief Reads the sensor data from the encoder.
 * 
 * @return uint16_t returns the dencoder data.
 */
uint16_t MOTOR_read_encoder();


/**
 * @brief Sets the rotational speed of the motor to @p speed.
 * 
 * @param speed The speed the motor is set to.
 */
void MOTOR_set_speed(unsigned char speed);


/**
 * @brief Sets the rotational direction of the motor to @p direction.
 * 
 * @param direction The direction the motor is set to have.
 */
void MOTOR_set_direction(uint8_t direction);


/**
 * @brief Sets the speed of the motor according to the joystick y-position.
 * 
 * @param joy_y The Y-position of the joystick.
 */
void MOTOR_joystic_set_speed(signed char joy_y);


/**
 * @brief Initializes the encoder.
 */
void MOTOR_encoder_init();


/**
 * @brief Scales the encoder data to the range [-100,100].
 *
 * @return uint8_t returns the scaled encoder data.
 */
signed char MOTOR_read_scaled_encoder();

#endif
