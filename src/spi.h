#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_master_init(void);

void SPI_master_transmit(uint8_t data);

void SPI_slave_init(void);

uint8_t SPI_slave_receive(void);

void SPI_set_SS(uint8_t value);

#endif
