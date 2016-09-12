#!/bin/sh
~/arduino-1.6.11/hardware/tools/avr/bin/avrdude -C ~/arduino-1.6.11/hardware/tools/avr/etc/avrdude.conf -c arduino -p atmega328p -P /dev/ttyUSB0 -b 57600 -v -U eeprom:r:eeprom.raw:r
./eeprom2set < eeprom.raw > settings.txt

