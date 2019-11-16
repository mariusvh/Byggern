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


void CAN_construct_message(CAN_MESSAGE_t *message, signed char data, uint8_t id, uint8_t length);


void CAN_send_message(CAN_MESSAGE_t *message);
void CAN_receive_message(int buffer_number, CAN_MESSAGE_t *message);

#endif
