ARDUINO_CLI = arduino-cli
BOARD = arduino:avr:nano:cpu=atmega328old
PORT = /dev/ttyUSB0

SKETCH_DIR = .
SKETCH_NAME = $(wordlist 2, $(words $(MAKECMDGOALS) - 2), $(MAKECMDGOALS))
SKETCH_PATH = $(SKETCH_DIR)/$(SKETCH_NAME)/$(SKETCH_NAME).ino

.PHONY: setup compile upload

setup:
		echo "setup..."
		$(ARDUINO_CLI) core update-index
		$(ARDUINO_CLI) core install arduino:avr
		$(ARDUINO_CLI) lib install timerone
		
		echo "-I${HOME}/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino" > compile_flags.txt
		echo "-I${HOME}/.arduino15/packages/arduino/hardware/avr/1.8.6/variants/standard" >> compile_flags.txt
		echo "-I${HOME}/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/avr/include" >> compile_flags.txt
		echo "-I${HOME}/.arduino15/packages/arduino/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino" >> compile_flags.txt
		echo "-I${HOME}/Arduino/libraries/TimerOne" >> compile_flags.txt
		echo "-DARDUINO=10607" >> compile_flags.txt
		echo "-D__AVR__" >> compile_flags.txt
		echo "-DUBRRH" >> compile_flags.txt


compile:
		$(ARDUINO_CLI) compile --fqbn $(BOARD) $(SKETCH_NAME)

upload:
		$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD) $(SKETCH_NAME)
