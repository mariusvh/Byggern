#include "avr/io.h"
#include "uart.h"
#include "sram.h"
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "joystick.h"
#include "slider.h"
#include "oled.h"

#define F_CPU 4000000
#include "util/delay.h"
#define FOSC 4915200 //Clock speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void main() {
  String_Init(MYUBRR);
  ADC_init();
  JOYSTICK_Init();
  JOYSTICK_position_t joystick;
  SLIDER_positions_t sliders;
  uint8_t right_slider;
  OLED_init_program();
  //OLED_write_command(0xA5);
  /*
  OLED_write_command(0x01, 0x01); //page addressing mode
  OLED_write_command(0xB1, 0xB1); //page0
  OLED_write_command(0x00, 0x00); //set lower start column address
  OLED_write_command(0x10,0x10); //set upper start column address

*/






  while (1) {

    //printf("X position: %d\n", ADC_read_X_joystick() );
	  //joystick = JOYSTICK_get_position_scaled();
	  //printf("Y position: %d\n\r", joystick.y_position);
	  //printf("DIRECTION: %d\n", (int)JOYSTICK_get_direction());

  //  printf("Slider right_button %d\n\r", SLIDER_right_button());

    /*
    sliders = SLIDER_get_scaled_position();
    right_slider = ADC_read_right_slider();
    printf("RIGHTSLIDER: %d\n", right_slider);
    */

  }
}


/* //Latch test
  DDRA = (0xFF);
  DDRE = (0x02);
  PORTA = 0;
  PORTE = 0;
  PORTA = (1 << PA1);

  while (1) {

    _delay_ms(10000);
    PORTE = (1 << PE1);
    _delay_ms(10000);
    PORTE = 0;
  }

*/


  //USART_Init(MYUBRR);
  //fdevopen(USART_Transmit, USART_Receive);


/*
void SquareWaveTest(){

  DDRD = (1 << PD1);
  PORTD = 0;

  while(1){
    PORTD ^= (1 << PD1);
    _delay_ms(1000);
  }
}
*/
