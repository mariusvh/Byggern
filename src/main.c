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


int main() {
  String_Init(MYUBRR);
  OLED_init_program();
  OLED_clear();

  OLED_print_string_5x7("Hello world!");

  while (1) {

  }
  return 0;
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
