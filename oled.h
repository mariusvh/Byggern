#ifndef OLED_H
#define OLED_H

#include <avr/io.h>

void OLED_init_program();

void OLED_write_command(uint8_t command);

void OLED_write_data(uint8_t data);

void OLED_set_column_adress(uint8_t start, uint8_t end);

void OLED_set_page_adress(uint8_t start, uint8_t end);

void OLED_set_col(uint8_t start_col);

void OLED_set_start_page(uint8_t start_page);

void OLED_clear(void);

void OLED_print_arrow(uint8_t start_col, uint8_t start_row);

//void OLED_print_char_5x7(unsigned char character, uint8_t start_col, uint8_t start_row);

//void OLED_print_char_5x7(unsigned char character);


//void OLED_print_string_5x7(char *string);

void OLED_print_char(unsigned char character, uint8_t font_size);

void OLED_print_string(char *string, uint8_t font_size);

void OLED_set_column_adress(uint8_t start, uint8_t end);

void OLED_set_page_adress(uint8_t start, uint8_t end);

void OLED_set_col(uint8_t start_col);

void OLED_set_start_page(uint8_t start_page);

void OLED_clear(void);

void OLED_print_arrow(uint8_t start_col, uint8_t start_row);

void OLED_print_char_5x7(unsigned char character, uint8_t start_col, uint8_t start_row);
void OLED_print_char_5x7_2(unsigned char character);


void OLED_print_string_5x7(char *string);

#endif
