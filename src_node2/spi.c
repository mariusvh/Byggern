#include "spi.h"

void SPI_master_init(void){
  /* Set SS, MOSI and SCK output, all others input */
//  DDRB |= (1<<DDB0|1<<DDB1)|(1<<DDB2)|(DDB7);
  DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB7);

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
    SPI_master_transmit(0x00);
    /* Return data register */
    return SPDR;
}
