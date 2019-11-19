/**
 * @file can.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the CAN communication.
 */

#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

typedef struct CAN_MESSAGE_t CAN_MESSAGE_t;



/**
 * @brief A structure to represent the CAN messages.
 * 
 */
struct CAN_MESSAGE_t
{
 unsigned int id; /**< The id of the CAN message */
 uint8_t length; /**< The length of the CAN message */
 signed char data[8]; /**< The content of the CAN message */
};



/**
 * @brief Initialization of the CAN communication. 
 * Defines mode of communication and initializes the interrupts.
 * 
 * @param mode Selecting communication mode.
 */
void CAN_init(uint8_t mode);


/**
 * @brief Creates and initializes a message structure.
 * 
 * @param message Pointert to the message to be constructed.
 */
void CAN_construct_message(CAN_MESSAGE_t *message, signed char data, uint8_t id, uint8_t length);


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

#endif
