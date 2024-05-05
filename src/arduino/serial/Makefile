CC=avr-gcc
MMCU=atmega328p
CPU_CLK_SPEED=16000000UL
PROGRAMMER=arduino
AVRDUDE=avrdude
OBJCOPY=avr-objcopy

serial.hex: serial.c
	$(CC) -O3 -mmcu=$(MMCU) -DF_CPU=$(CPU_CLK_SPEED) serial.c -o serial.elf
	$(OBJCOPY) -j .text -j .data -O ihex serial.elf serial.hex


upload: serial.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MMCU) -P /dev/cu.usbmodem2101 -U flash:w:serial.hex:i
	

