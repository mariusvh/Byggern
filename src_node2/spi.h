#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

void SPI_master_init(void);

void SPI_master_transmit(uint8_t data);

uint8_t SPI_slave_receive(void);

#endif
