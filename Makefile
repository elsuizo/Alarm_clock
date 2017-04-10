# Makefile for compile the arduino board from command line or better from neovim
ARDUINO_DIR = /home/elsuizo/.arduino_ide
ARDMK_DIR = /home/elsuizo/.arduino_mk
BOARD_TAG = uno
# external dependences
ARDUINO_LIBS = Wire RTClib LiquidCrystal


include $(ARDMK_DIR)/Arduino.mk
