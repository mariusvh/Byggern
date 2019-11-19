/**
 * @file mcp_controll.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for the IR diodes.
 */

#ifndef IR_H
#define IR_H
#include <stdint.h>
#include <avr/io.h>


/**
 * @brief Initializes the IR diodes. 
 */
void IR_init();


/**
 * @brief Calculates the average of 4 following ADC readings of the recived IR signals.
 *
 * @return uint16_t returns the average ADC reading.
 */
uint16_t IR_digital_filter();


/**
 * @brief Counts the amount of times the line of sight between the IR diodes is blocked.
 *
 * @return uint16_t returns the count.
 */
uint16_t IR_count_scores();


/**
 * @brief Checks if the line of sight between the IR diodes has been blocked too many times.
 *
 * @return uint8_t returns "1" if the limit is reached and "0" otherwise.
 */
uint8_t IR_game_over();


/**
 * @brief Fetches the score.
 *
 * @return uint8_t returns the score.
 */
uint8_t IR_return_score();


#endif