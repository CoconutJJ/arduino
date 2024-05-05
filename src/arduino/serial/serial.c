#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#define BAUD 9600

#include <avr/io.h>
#include <math.h>
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

        // 1 stop bits
        UCSR0C &= ~(1 << USBS0);

        // 8 bit dataframes
        UCSR0B &= ~(1 << UCSZ02);
        UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

        // no parity bit
        UCSR0C &= ~(1 << UPM01) & ~(1 << UPM00);
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
        // 9600 BAUD RATE, UBRR0 = 103 per Table 19-12
        // on
        // https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
        usart_init (103);

        while (1)
                usart_send ("Hello\n", 6);
}
