#include "motor.h"
#include <stdio.h>
#include <stdint.h>
#include "dac.h"

#include <util/delay.h>


void MOTOR_init(){
    DAC_init();

    /*MJ1: Set !OE, !RST, SEL, EN, DIR to output*/
    DDRH |= (1<<PH1) | (1<<PH3) | (1<<PH4) | (1<<PH5) | (1<<PH6);

    /*MJ2: Set to input */
    DDRK = 0;

    /*Enable motor by setting EN*/
    PORTH |= (1<<PH4);

    /*Toggle !RST to reset encoder*/
    PORTH &= ~(1<<PH6);
    _delay_us(20);
    PORTH |= (1<<PH6);
}

uint16_t MOTOR_read_encoder(){
    /*Set !OE to low to enable output of encoder*/
    PORTH &= ~(1<<PH5);

    /*Set SEL low to get high byte*/
    PORTH &= ~(1<<PH3);

    _delay_us(300);

    /*Read MSB*/
    uint8_t ms_byte = PINK;
    printf("ms: %d\n\r", ms_byte);  

    /*Set SEL high to get low byte*/
    PORTH |= (1<<PH3);

    _delay_us(300);
    /*read LSB*/
    uint8_t ls_byte = PINK;
    printf("ls: %d\n\r", ls_byte);


    /*Toggle !RST to reset encoder*/
    PORTH &= ~(1<<PH6);
    _delay_us(300);
    PORTH |= (1<<PH6);

    /*Set !OE high to disable output of encoder*/
    PORTH |= (1<<PH5);

    /*Process received data*/
    int16_t encoder = ((((int16_t)ms_byte) << 8) | (int16_t)ls_byte);

    return encoder;
}

void MOTOR_set_speed(unsigned char speed){
    DAC_write(speed);
}

void MOTOR_set_direction(uint8_t direction){
    //uint8_t right = 1;
    //uint8_t left = 0;

    if (direction){
        PORTH |= (1<<PH1);
        printf("1");
    }

    else
    {
        PORTH &= ~(1<<PH1);
    }
}
    

void MOTOR_joystic_set_speed(signed char joy_y){

    unsigned char joy_y_raw = (unsigned char)joy_y*(MAX_JOYSTICK_VALUE-INITIAL_VALUE)/100 + INITIAL_VALUE;
    printf("joy_y; %d\n\r", joy_y_raw);
}