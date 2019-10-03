#include "mcp_controll.h"
#include "spi.h"
#include "MCP2515.h"


void MCP_init(){
    SPI_master_init();
    MCP_reset();
    MCP_controll_write(MODE_NORMAL,MCP_CANCTRL);
}

void MCP_CONTROLL_setCS(uint8_t value){
    /*Set slave select to output*/
    DDRB = (1<<DDB4);
    /*Set SS*/
    PORTB = (value << PB4);
}

uint8_t MCP_CONTROLL_read(uint8_t adress){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the READ instruction to the MCP2515*/
    SPI_master_transmit(MCP_READ);
    /*Sending the adress to be read from*/
    SPI_master_transmit(adress);
    /*receive data from the selected adress*/
    char data = SPI_slave_receive();
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
    return data;
}

void MCP_controll_write(uint8_t data,uint8_t adress){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the WRTIE instruction to the MCP2515*/
    SPI_master_transmit(MCP_WRITE);
    /*Sending the adress to be written to*/
    SPI_master_transmit(adress);
    /*Sending the data to be placed at that adress*/
    SPI_master_transmit(data);
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
}

void MCP_request_to_send(uint8_t buffer){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the RTS_buffer instruction to the MCP2515*/
    switch (buffer) {
        case 0:
            SPI_master_transmit(MCP_RTS_TX0);
            break;
        case 1:
            SPI_master_transmit(MCP_RTS_TX1);
            break;
        case 2:
            SPI_master_transmit(MCP_RTS_TX2);
            break;
        case 3:
            SPI_master_transmit(MCP_RTS_TXALL);
            break;
        default:
            break;
    }
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
}

uint8_t MCP_read_status(void){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the READ STATUS instruction to the MCP2515*/
    SPI_master_transmit(MCP_READ_STATUS);
    /*receive data from the selected adress*/
    char data_status = SPI_slave_receive();
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
    return data_status;
}

void MCP_bit_modify(uint8_t adress,uint8_t mask, uint8_t data){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the BIT MODIFY instruction to the MCP2515*/
    SPI_master_transmit(MCP_BITMOD);
    /*Sending the adress to be written to*/
    SPI_master_transmit(adress);
    /*Sending the mask.The mask byte determines which bits in the register willbe allowed to change.
    A ‘1’ in the mask byte will allowa bit in the register to change, while a ‘0’ will not. */
    SPI_master_transmit(mask);
    /*Sending the data to be placed at that adress.The data byte determines what value the modified bitsin the register will be changed to.
     A ‘1’ in the data bytewill set the bit and a ‘0’ will clear the bit, provided thatthe mask for that bit is set to a ‘1’ */
    SPI_master_transmit(data);
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
}

void MCP_reset(){
    /*Set CS to low*/
    MCP_CONTROLL_setCS(0);
    /*Sending the RESET instruction to the MCP2515*/
    SPI_master_transmit(MCP_RESET);
    /*Set CS to high*/
    MCP_CONTROLL_setCS(1);
}

/*
Read
Write
Request to send
Read status
Bit modify
Reset

*/
