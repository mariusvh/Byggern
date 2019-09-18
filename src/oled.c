#include "oled.h"

void OLED_write_command(uint8_t command, uint8_t adress){
  volatile char *ext_oled_command = (char*) 0x1000; //Start address for the OLED command
  ext_oled_command[adress] = command;
}

void OLED_init_program(){
  OLED_write_command(0xae,0xae);        //  display  off
  OLED_write_command(0xa1,0xa1);        //segment  remap
  OLED_write_command(0xda,0xda);        //common  pads  hardware:  alternative
  OLED_write_command(0x12,0x12);
  OLED_write_command(0x08,0xc8);        //common  output scan direction:com63~com0
  OLED_write_command(0xa8,0xa8);        //multiplex  ration  mode:63
  OLED_write_command(0x3f,0x3f);
  OLED_write_command(0xd5,0xd5);        //display  divide ratio/osc. freq. mode
  OLED_write_command(0x80,0x80);
  OLED_write_command(0x81,0x81);        //contrast  control
  OLED_write_command(0x50,0x50);
  OLED_write_command(0xd9,0xd9);        //set  pre-charge  period
  OLED_write_command(0x21,0x21);
  OLED_write_command(0x20,0x20);        //Set  Memory  Addressing  Mode
  OLED_write_command(0x02,0x02);
  OLED_write_command(0xdb,0xdb);        //VCOM  deselect  level  mode
  OLED_write_command(0x30,0x30);
  OLED_write_command(0xad,0xad);        //master  configuration
  OLED_write_command(0x00,0x00);
  OLED_write_command(0xa4,0xa4);        //out  follows  RAM  content
  OLED_write_command(0xa6,0xa6);        //set  normal  display
  OLED_write_command(0xaf,0xaf);        //  display  on
}

/*void OLED_reset(){

}
*/

/*void OLED_print(char*){

}
*/
void OLED_write_data(uint8_t data, uint8_t adress){
  volatile char *ext_oled_data = (char*) 0x1200; //Start address for the OLED data
  ext_oled_data[adress] = data;
}
