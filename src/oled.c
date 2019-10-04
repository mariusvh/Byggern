#include "oled.h"
#include "font_5x7.h"
#include "font_8x8.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

volatile char *ext_oled_command = (char*) 0x1000; //Start address for the OLED command
volatile char *ext_oled_data = (char*) 0x1200; //Start address for the OLED data


void OLED_write_command(uint8_t command){
  ext_oled_command[0] = command;
}

void OLED_init_program(){
  MCUCR |= (1 << SRE);
  SFIOR |= (1 << XMM2);

  OLED_write_command(0xae);        //  display  off
  OLED_write_command(0xa1);        //segment  remap
  OLED_write_command(0xda);        //common  pads  hardware:  alternative
  OLED_write_command(0x12);
  OLED_write_command(0x08);        //common  output scan direction:com63~com0
  OLED_write_command(0xa8);        //multiplex  ration  mode:63
  OLED_write_command(0x3f);
  OLED_write_command(0xd5);        //display  divide ratio/osc. freq. mode
  OLED_write_command(0x80);
  OLED_write_command(0x81);        //contrast  control
  OLED_write_command(0x50);
  OLED_write_command(0xd9);        //set  pre-charge  period
  OLED_write_command(0x21);
  OLED_write_command(0x20);        //Set  Memory  Addressing  Mode
  OLED_write_command(0x02);
  OLED_write_command(0xdb);        //VCOM  deselect  level  mode
  OLED_write_command(0x30);
  OLED_write_command(0xad);        //master  configuration
  OLED_write_command(0x00);
  OLED_write_command(0xa4);        //out  follows  RAM  content
  OLED_write_command(0xa6);        //set  normal  display
  OLED_write_command(0xaf);        //  display  on

  OLED_write_command(0xC8);
}

/*void OLED_reset(){

;
*/

/*void OLED_print(char*){

}
*/
void OLED_write_data(uint8_t data){
  ext_oled_data[0] = data;
}

void OLED_set_column_adress(uint8_t start, uint8_t end){
  OLED_write_command(0x21);
  OLED_write_command(start);
  OLED_write_command(end);
}


void OLED_set_page_adress(uint8_t start, uint8_t end){
  OLED_write_command(0x22);
  OLED_write_command(start);
  OLED_write_command(end);
}

void OLED_set_col(uint8_t start_col){
  // adressing mode set by OLED_clear
    uint8_t col_lsb = 0x00 | (start_col & 0x0F);
    OLED_write_command(col_lsb);
    uint8_t col_msb = 0x10 | ((start_col & 0xF0) >> 4);
    OLED_write_command(col_msb);
}

void OLED_set_start_page(uint8_t start_page){
    // adressing mode set by OLED_clear
    start_page |= 0xB0;
    OLED_write_command(start_page);
}


void OLED_clear(void){
  // Set to Horizontal adressing mode
  OLED_write_command(0x20);
  OLED_write_command(0);

  OLED_set_column_adress(0,127);
  OLED_set_page_adress(0,7);
  for (size_t i = 0; i < 1024; i++) {
    OLED_write_data(0);
  }
  // Set to page adressing mode
  OLED_write_command(0x20);
  OLED_write_command(0x02);
}

void OLED_print_arrow(uint8_t start_col, uint8_t start_row){
  // Set to page adressing mode
  OLED_write_command(0x20);
  OLED_write_command(0x02);
  OLED_set_col(start_col);
  OLED_set_start_page(start_row);
  OLED_write_data(0b00011000);
  OLED_write_data(0b00011000);
  OLED_write_data(0b01111110);
  OLED_write_data(0b00111100);
  OLED_write_data(0b00011000);
}

/*
void OLED_print_char_5x7(unsigned char character, uint8_t start_col, uint8_t start_row){
  OLED_set_column_adress(start_col,start_col+5);
  OLED_set_page_adress(start_row,start_row);
  uint8_t offset_ascii = 32;
  uint8_t char_value = (uint8_t)character - offset_ascii;
  for (int j = 0; j < 5; j++) {
      char char_out = (char) pgm_read_byte(&font5[char_value][j]);
      OLED_write_data(char_out);
  }
}

*/
/*
void OLED_print_char_5x7(unsigned char character){
  uint8_t offset_ascii = 32;
  uint8_t char_value = (uint8_t)character - offset_ascii;
  for (int j = 0; j < 5; j++) {
      char char_out = (char) pgm_read_byte(&font5[char_value][j]);
      OLED_write_data(char_out);
  }
}



void OLED_print_string_5x7(char *string){
  for (size_t i = 0; i < strlen(string); i++) {
    OLED_print_char_5x7(string[i]);
  }
}
*/

void OLED_print_char(unsigned char character, uint8_t font_size){
  uint8_t offset_ascii = 32;
  uint8_t char_value = (uint8_t)character - offset_ascii;

  if (font_size == 5) {
    for (int j = 0; j < 5; j++) {
        char char_out = (char) pgm_read_byte(&font5[char_value][j]);
        OLED_write_data(char_out);
    }
    if (character != " ") {
      OLED_write_data(0); //Easier to read with more space between characters
    }

  }
  else if (font_size == 8) {
    for (int j = 0; j < 8; j++) {
        char char_out = (char) pgm_read_byte(&font8[char_value][j]);
        OLED_write_data(char_out);
    }
  }
}

void OLED_print_string(char *string, uint8_t font_size){
  for (size_t i = 0; i < strlen(string); i++) {
    OLED_print_char(string[i], font_size);
  }
}
