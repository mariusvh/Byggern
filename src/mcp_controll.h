#ifndef MCP_CONTROLL_H
#define MCP_CONTROLL_H

#include <avr/io.h>

void MCP_CONTROLL_setCS(uint8_t value);

uint8_t MCP_CONTROLL_read(uint8_t adress);

void MCP_controll_write(uint8_t data,uint8_t adress);

void MCP_request_to_send(uint8_t buffer);

uint8_t MCP_read_status(void);

void MCP_bit_modify(uint8_t adress,uint8_t mask, uint8_t data);

void MCP_reset();

#endif
