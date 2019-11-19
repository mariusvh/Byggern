/**
 * @file mcp_controll.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for controlling of the MPC.
 */

#ifndef MCP_CONTROLL_H
#define MCP_CONTROLL_H

#include <avr/io.h>


/**
 * @brief Initializes the MCP2515. Setting the  MCP in configuration mode. 
 */
void MCP_init();


/**
 * @brief Sets the value of the chip select (CS) signal according to @p value.
 * 
 * @param value Choose if CS is sat to high or low.
 */
void MCP_CONTROLL_setCS(uint8_t value);


/**
 * @brief Reads data from the SPI slave on adress @p adress.
 * 
 * @param adress Which adress to read from.
 *
 * @return uint8_t returns the data that was read.
 */
uint8_t MCP_CONTROLL_read(uint8_t adress);


/**
 * @brief Writes the data in @p data to adress @p adress.
 * 
 * @param data Data that will be sent.
 * @param adress Which adress to write to.
 */
void MCP_controll_write(uint8_t data,uint8_t adress);


/**
 * @brief Sends out RTS buffer instruction to the MCP2515.
 * 
 * @param buffer The buffer that will be used.
 */
void MCP_request_to_send(uint8_t buffer);


/**
 * @brief Fetches the read status from the MCP2515.
 *
 * @return uint8_t returns the read status.
 */
uint8_t MCP_read_status(void);


/**
 * @brief Changes the bits decided by the mask @p mask on adress @p adress to the data given by @p data.
 * 
 * @param adress Adress where the bits change.
 *
 * @param mask Decides which bits that can be altered.
 *
 * @param data Data that the bits are changed to.
 */
void MCP_bit_modify(uint8_t adress,uint8_t mask, uint8_t data);


/**
 * @brief Resets the MCP2515.
 */
void MCP_reset();

#endif
