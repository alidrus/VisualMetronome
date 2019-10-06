all: compile

upload:
	arduino-cli upload --verbose -b arduino:avr:uno -p /dev/tty.usbserial-A5XK3RJT .

compile:
	arduino-cli compile --verbose -b arduino:avr:uno .

clean:
	rm -f ..arduino.avr.uno.elf ..arduino.avr.uno.hex
