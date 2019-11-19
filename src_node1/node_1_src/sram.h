/**
 * @file sram.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the SRAM.
 */

#ifndef SRAM_H
#define SRAM_H
#include <avr/io.h>

/**
 * @brief Initializes the SRAM.
 */
void SRAM_init(void);


/**
 * @brief Tests if the SRAM works properly.
 */
void SRAM_test(void);

#endif
