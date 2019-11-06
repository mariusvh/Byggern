#include "dac.h"
#include "TWI_Master.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void DAC_init(){
   // sei();
    TWI_Master_Initialise();
}

void DAC_write(unsigned char data){
    /*Slave adress*/
    unsigned char adress = 80; // 80 = 01010000

    /*write bit*/
    unsigned char command = 0;
    unsigned char msg_size = 3;
    unsigned char msg[msg_size];
    msg[0] = adress;
    msg[1] = command;
    msg[2] = data; 
    TWI_Start_Transceiver_With_Data(msg,msg_size);
}
