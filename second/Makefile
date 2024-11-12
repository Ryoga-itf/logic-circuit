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

compile:
		$(ARDUINO_CLI) compile --fqbn $(BOARD) $(SKETCH_NAME)

upload:
		$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD) $(SKETCH_NAME)
