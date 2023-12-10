/**
        SOS Led Blink
        This program blinks an LED attached to Pin 7 of the Arduino UNO R3 in
        an SOS pattern.
**/

#define __AVR_ATmega32U4__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void _pd7_enable ()
{
        PORTD |= (1 << PD7);
        return;
}

void _pd7_disable ()
{
        PORTD &= ~(1 << PD7);
        return;
}

void dot ()
{
        _delay_ms (125);
        _pd7_enable ();
        _delay_ms (125);
        _pd7_disable ();
}

void dash ()
{
        _delay_ms (250);
        _pd7_enable ();
        _delay_ms (250);
        _pd7_disable ();
}

int main (void)
{
        DDRD |= (1 << PD7);

        while (1) {
                dash ();
                dash ();
                dash ();
                dot ();
                dot ();
                dot ();
                dash ();
                dash ();
                dash ();
        }
        return 0;
}
