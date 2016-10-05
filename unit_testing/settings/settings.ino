#include <EEPROM.h>
#include <Wire.h>
#include "settings.h"

int memaddr;
MyObject myeeprom;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, myeeprom);
  printeeprom(myeeprom);
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
}

void requestEvent() {
  switch (memaddr) {
    case I2C_IPADDRESS:
      Wire.write(myeeprom.ip,4);
    break;
    case I2C_MACADDRESS:
      Wire.write(myeeprom.mac,6);
    break;
    case I2C_LENGTHTABLE:
      Wire.write((byte *)&myeeprom.length_table,26);
    break;
    case I2C_JUMPTABLE:
      Wire.write((byte *)&myeeprom.jump_table,13);
    break;
    case I2C_AD7705_SETUP_REGISTER:
      Wire.write(myeeprom.ad7705_setup_register);
    break;
    case I2C_AD7705_CLOCK_REGISTER:
      Wire.write(myeeprom.ad7705_clock_register);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
