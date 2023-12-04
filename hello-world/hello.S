#include <avr/io.h>

        .section .text
        .global main
        
main:
        ldi r16, low(RAMEND)
        rjmp main
        
