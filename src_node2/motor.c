#include "motor.h"
#include <stdio.h>
#include <stdint.h>
#include "dac.h"
#include <stdlib.h>

#include <util/delay.h>


#define F_CPU 16000000UL //Clock speed

int  right = 0;
int left = 0;

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

    _delay_us(20);

    /*Read MSB*/
    uint8_t ms_byte = PINK;
    //printf("ms: %d\n\r", ms_byte);

    /*Set SEL high to get low byte*/
    PORTH |= (1<<PH3);

    _delay_us(20);
    /*read LSB*/
    uint8_t ls_byte = PINK;
    //printf("ls: %d\n\r", ls_byte);


    /*Toggle !RST to reset encoder
    PORTH &= ~(1<<PH6);
    _delay_us(300);
    PORTH |= (1<<PH6);
    */

    /*Set !OE high to disable output of encoder*/
    PORTH |= (1<<PH5);

    /*Process received data*/
    int16_t encoder = ((((int16_t)ms_byte) << 8) | (int16_t)ls_byte);
    //printf("Encoder: %d\n\r", encoder);
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
    }

    else
    {
        PORTH &= ~(1<<PH1);
    }
}


void MOTOR_joystic_set_speed(signed char joy_y){
   // printf("joy_y; %d\n\r", joy_y);
    //unsigned char joy_y_raw = (unsigned char)joy_y*(MAX_JOYSTICK_VALUE-INITIAL_VALUE)/100 + INITIAL_VALUE;
    //unsigned char joy_y_raw = (unsigned char)joy_y*(MAX_JOYSTICK_VALUE-INITIAL_VALUE)/100 + INITIAL_VALUE;
    //printf("joy_y_raw; %d\n\r", joy_y_raw);
    uint8_t threshold = 2;
    if (joy_y < -threshold) {
        MOTOR_set_direction(0);
        MOTOR_set_speed(-joy_y);
     //   printf("SETSPEED \n\r");
    }
    else if(joy_y > threshold){
        MOTOR_set_direction(1);
        MOTOR_set_speed(joy_y);
    }

}

void MOTOR_encoder_init(){
    //Find Left wall
    MOTOR_set_direction(0);
    MOTOR_set_speed(100);
    _delay_ms(1000);
    /*Toggle !RST to reset encoder*/
    PORTH &= ~(1<<PH6);
    _delay_us(20);
    PORTH |= (1<<PH6);
    left = MOTOR_read_encoder();
    printf("left %d\n\r", left);


    //Find right wall
    MOTOR_set_direction(1);
    MOTOR_set_speed(100);
    _delay_ms(1000);
    right = MOTOR_read_encoder();
    printf("right %d\n\r", right);


}

signed char MOTOR_read_scaled_encoder(){
    int middle = abs((left-right)/2);
   //printf("mid: %d \n\r",middle);

    int enc_raw = abs(MOTOR_read_encoder());

    //printf("Enc_raw: %d\n\r",enc_raw);

    signed char enc_scaled = ((float)enc_raw - (float)middle)/((float)middle)*100;

    //printf("Enc_scaled: %d\n\r",enc_scaled);


    return  enc_scaled; //maybe signed char
}

