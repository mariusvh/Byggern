/**
 * @file spi.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for using SPI communicatoin.
 */

#ifndef SPI_H
#define SPI_H

#include <avr/io.h>


/**
 * @brief Reads data on channel @p channel from the ADC.
 */
void SPI_master_init(void);


/**
 * @brief Transmits the data in @p data to the SPI slave.
 * 
 * @param data The data to be transmitted.
 */
void SPI_master_transmit(uint8_t data);


/**
 * @brief Reads data transmitted by the SPI master.
 * 
 * @return uint8_t returns the recived data.
 */
uint8_t SPI_slave_receive(void);


/**
 * @brief Sets the slave select (SS) according to the value of @p value.
 * 
 * @param value Value to pass on to the SS.
 */
void SPI_set_SS(uint8_t value);

#endif
