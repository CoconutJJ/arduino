#define __AVR_ATmega32U4__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#define LED_PIN  PB5
#define LED_DDR  DDRB
#define LED_PORT PORTB

void swap (int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

int main (void)
{

        DDRB |= (1 << PB0);        
        return 0;
}
