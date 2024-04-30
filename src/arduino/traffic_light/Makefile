CC=avr-gcc
MMCU=atmega328p
CPU_CLK_SPEED=16000000UL
PROGRAMMER=arduino
AVRDUDE=avrdude
OBJCOPY=avr-objcopy

traffic_light.hex: traffic_light.c
	$(CC) -O3 -mmcu=$(MMCU) -DF_CPU=$(CPU_CLK_SPEED) traffic_light.c -o traffic_light.elf
	$(OBJCOPY) -j .text -j .data -O ihex traffic_light.elf traffic_light.hex


upload: traffic_light.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MMCU) -P /dev/cu.usbmodem2101 -U flash:w:traffic_light.hex:i
	

