#ifndef OLED_H
#define OLED_H

#include <avr/io.h>


/**
 * @brief Initializes the OLED screen through a sequnce of predefined commands.
 * 
 */
void OLED_init_program();


/**
 * @brief Writes a command @p command to the OLED command part of the SRAM.
 * 
 * @param command Which chommand to write.
 */
void OLED_write_command(uint8_t command);


/**
 * @brief Writes data @p data to the OLED data part of the SRAM.
 * 
 * @param[in] data Data to write.
 */
void OLED_write_data(uint8_t data);


/**
 * @brief Sets the column range [start,end] that will be utilized.
 * 
 * @param start First column that will be utilized.
 *
 * @param end Last column that will be utilized.
 */
void OLED_set_column_adress(uint8_t start, uint8_t end);


/**
 * @brief Sets the page range [start,end] that will be utilized.
 * 
 * @param start First page that will be utilized.
 *
 * @param end Last page that will be utilized.
 */
void OLED_set_page_adress(uint8_t start, uint8_t end);


/**
 * @brief Sets the first column to be utilized.
 * 
 * @param start_col First column that will be utilized.
 */
void OLED_set_col(uint8_t start_col);


/**
 * @brief Sets the first page to be utilized.
 * 
 * @param start_page First page that will be utilized.
 */
void OLED_set_start_page(uint8_t start_page);


/**
 * @brief Clears the screen. All "pixels" are set low.
 */
void OLED_clear(void);


/**
 * @brief Prints the arrow object on the OLED screen.
 * 
 * @param start_col Column where the printing of the arrow vill start.
 *
 * @param start_page Page where the printing of the arrow vill start.
 */
void OLED_print_arrow(uint8_t start_col, uint8_t start_page);


/**
 * @brief Prints the character @p character on the OLED screen.
 * 
 * @param character Which character to print.
 *
 * @param font_size The font size the character @p character gets.
 */
void OLED_print_char(unsigned char character, uint8_t font_size);


/**
 * @brief Prints the string @p *string on the OLED screen.
 * 
 * @param *string Which string to print.
 *
 * @param font_size The font size the string @p *string gets.
 */
void OLED_print_string(char *string, uint8_t font_size);


#endif
