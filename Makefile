CC=avr-gcc/avr/bin/avr-gcc
MMCU=atmega328p
CPU_CLK_SPEED=16000000UL
PROGRAMMER=arduino
AVRDUDE=avr-gcc/avr/bin/avrdude
OBJCOPY=avr-gcc/avr/bin/avr-objcopy

hello: hello.c
	$(CC) -Os -mmcu=$(MMCU) -DF_CPU=$(CPU_CLK_SPEED) hello.c -o hello.elf
	$(OBJCOPY) -j .text -j .data -O ihex hello.elf hello.hex


upload: hello.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MMCU) -P /dev/cu.usbmodem1101 -U flash:w:hello.hex:i
	

