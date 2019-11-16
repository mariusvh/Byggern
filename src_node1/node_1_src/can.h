/**
 * @file can.h
  * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the CAN communication.
 */


#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

//typedef struct CAN_MESSAGE_t CAN_MESSAGE_t;

/**
 * @brief A structure to represent the CAN messages.
 * 
 */
typedef struct CAN_MESSAGE
{
 unsigned int id; /**< The id of the CAN message */
 uint8_t length; /**< The length of the CAN message */
 signed char data[8]; /**< The content of the CAN message */
}CAN_MESSAGE_t;


/**
 * @brief Initialization of the CAN communication. 
 * Defines mode of communication and initializes the interrupts.
 * 
 * @param[in] mode Selecting communication mode.
 */
void CAN_init(uint8_t mode);

/**
 * @brief Sends the message @p message onto the CAN bus.
 * 
 * @param[in] message The message that is beeing sent.
 */
void CAN_send_message(CAN_MESSAGE_t *message);

/**
 * @brief Recieves message from CAN bus and updates @p message .
 * 
 * @param buffer_number Decides which buffer to recieve from.
 * @param[in/out] message Where the recieved message is stored.
 */
void CAN_receive_message(int buffer_number, CAN_MESSAGE_t *message);

/**
 * @brief Sends the X- and Y-position from the joystic to the CAN bus.
 * 
 * @param message 
 */
void CAN_send_joystick_position(CAN_MESSAGE_t *message);

/**
 * @brief Sends the X- and Y-position of the joystick,
 *  the position of the right and left slider, 
 * and the output from the right and left button onto the CAN bus.
 * 
 * @param message The message that is beeing sent.
 */
void CAN_send_controllers_filter(CAN_MESSAGE_t *message);

#endif
