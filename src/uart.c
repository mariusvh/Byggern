#include "uart.h"


void USART_Init( unsigned int ubrr ){
    // Baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Transmitter and receiver enabling
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // set fram formate: 8data, 2stop bit
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

}

void USART_Transmit( unsigned char data) {
    //Wait for empty transmit buffer
    while (!(UCSR0A & (1<<UDRE0)));
    //Put data into buffer, send data
    UDR0 = data;
}

unsigned char USART_Receive(void){
    //Wait for data to be recievd
    while (!(UCSR0A & (1<<RXC0)));
    //get and return recieved data from buffer
    return UDR0;
}
