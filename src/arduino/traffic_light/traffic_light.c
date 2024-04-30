/**
        Traffic Lights

        PIN 4 - RED
        PIN 5 - YELLOW
        PIN 6 - GREEN
**/

#define __AVR_ATmega32U4__
#define RED_DELAY_MS    1000 * 5
#define GREEN_DELAY_MS  1000 * 5
#define YELLOW_DELAY_MS 1000 * 2
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

static void _set_output_PORTD (int pin)
{
        DDRD |= (1 << pin);
}
static void _enable_PORTD (int pin)
{
        PORTD |= (1 << pin);
}

static void _disable_PORTD (int pin)
{
        PORTD &= ~(1 << pin);
}

static void _enable_red ()
{
        _enable_PORTD (PD4);
}

static void _enable_yellow ()
{
        _enable_PORTD (PD5);
}

static void _enable_green ()
{
        _enable_PORTD (PD6);
}

static void _disable_red ()
{
        _disable_PORTD (PD4);
}

static void _disable_yellow ()
{
        _disable_PORTD (PD5);
}

static void _disable_green ()
{
        _disable_PORTD (PD6);
}

void init_traffic_light ()
{
        _enable_red ();
        _delay_ms (RED_DELAY_MS);
        _disable_red ();

        _enable_green ();
        _delay_ms (GREEN_DELAY_MS);
        _disable_green ();

        _enable_yellow ();
        _delay_ms (YELLOW_DELAY_MS);
        _disable_yellow ();
}

int main (void)
{
        _set_output_PORTD (PD4);
        _set_output_PORTD (PD5);
        _set_output_PORTD (PD6);
        while (1)
                init_traffic_light ();

        return 0;
}
