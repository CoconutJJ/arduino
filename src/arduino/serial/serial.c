#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#define BAUD 9600

#include <avr/io.h>
#include <stdlib.h>
#include <util/setbaud.h>

void _usart_transmit (char c)
{
        while (!(UCSR0A & (1 << UDRE0)))
                ;

        UDR0 = c;
}

unsigned char _usart_receive ()
{
        while (!(UCSR0A & (1 << RXC0)))
                ;

        return UDR0;
}

void usart_init (int baud_rate)
{
        UBRR0H = (unsigned char)baud_rate >> 8;
        UBRR0L = (unsigned char)baud_rate;

        // enable transmitter and receiver
        UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void usart_send (char *buf, size_t nbytes)
{
        while (nbytes-- > 0)
                _usart_transmit (*(buf++));
}

void usart_recv (char *buf, size_t nbytes)
{
        while (nbytes-- > 0)
                *(buf++) = _usart_receive ();
}

int main (void)
{
        usart_init (9600);



}
