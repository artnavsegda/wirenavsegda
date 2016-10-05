#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include "settings.h"

byte Ethernet::buffer[300];   // a very small tcp/ip buffer is enough here
MyObject myeeprom;
int memaddr;

void setup () {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, myeeprom);
  printeeprom(myeeprom);
  if (ether.begin(sizeof Ethernet::buffer, myeeprom.mac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(myeeprom.ip);
  ether.printIp("My IP: ", ether.myip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
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
