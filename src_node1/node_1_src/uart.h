/**
 * @file uart.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the UART/USART communication.
 */

#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <stdio.h>


/**
 * @brief Initializes the USART communication.
 * 
 * @param ubrr 
 */
void USART_Init(unsigned int ubrr);


/**
 * @brief Transmits the data from @p data to the bus.
 * 
 * @param data Data to be transmitted.
 */
void USART_Transmit(unsigned char data);


/**
 * @brief Recives the data on the bus.
 *
 * @return unsigned char returns the recived data.
 */
unsigned char USART_Receive(void);


/**
 * @brief Reads data on channel @p channel from the ADC.
 * 
 * @param ubrr 
 */
void String_Init(unsigned int ubrr);

#endif
