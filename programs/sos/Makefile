CC=avr-gcc
MMCU=atmega328p
CPU_CLK_SPEED=16000000UL
PROGRAMMER=arduino
AVRDUDE=avrdude
OBJCOPY=avr-objcopy

sos.hex: sos.c
	$(CC) -O3 -mmcu=$(MMCU) -DF_CPU=$(CPU_CLK_SPEED) sos.c -o sos.elf
	$(OBJCOPY) -j .text -j .data -O ihex sos.elf sos.hex


upload: hello.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MMCU) -P /dev/cu.usbmodem101 -U flash:w:sos.hex:i
	

