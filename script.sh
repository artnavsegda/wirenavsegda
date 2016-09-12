#!/bin/sh
/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C /Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -c arduino -p atmega328p -P /dev/cu.usbserial-A400X396 -b 57600 -v -U eeprom:r:eepom.raw:r
./eeprom2set < eeprom.raw > settings.txt

