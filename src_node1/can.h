#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

typedef struct CAN_MESSAGE_t CAN_MESSAGE_t;

struct CAN_MESSAGE_t
{
 unsigned int id;
 uint8_t length;
 signed char data[8];
};


void CAN_init(uint8_t mode);
CAN_MESSAGE_t CAN_construct_message(char *string, uint8_t id, uint8_t length);
void CAN_send_message(CAN_MESSAGE_t *message);
void CAN_receive_message(int buffer_number, CAN_MESSAGE_t *message);
void CAN_send_joystick_position(CAN_MESSAGE_t *message, signed char prev_joystick_positions[]);
void CAN_send_controllers(CAN_MESSAGE_t *message);
void CAN_send_controllers_filter(CAN_MESSAGE_t *message, uint8_t prev_slider_position, signed char prev_joystick_positions[]);

#endif
