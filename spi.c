#include "spi.h"

void SPI_master_init(void){
  /* Set SS, MOSI and SCK output, all others input */
  DDRB |= (1<<DDB4|1<<DDB5)|(1<<DDB7);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


void SPI_master_transmit(uint8_t data){
  /* Start transmission */
  SPDR = data;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));

}



uint8_t SPI_slave_receive(void){
    SPI_master_transmit(0xaa);
    /* Return data register */
    return SPDR;
}

// value needs to be 0 or 1
void SPI_set_SS(uint8_t value){
  /*Set slave select to output*/

  DDRB |= (1<<DDB4);
  switch(value){
  case 0:
    PORTB &= ~(1 << PB4);
  case 1:
    PORTB |= (1 << PB4);
  }

  /*Set SS*/
}
