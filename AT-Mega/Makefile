main:
	avr-gcc -mmcu=atmega644pa -o main.bin *.c
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex
	avrdude -p m644p -c usbasp -P usb -U flash:w:main.hex:i