#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include "settings.h"

byte Ethernet::buffer[300];   // a very small tcp/ip buffer is enough here
MyObject e;
int memaddr;

void setup () {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, e);
  if (ether.begin(sizeof Ethernet::buffer, e.mac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(e.ip);
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
      Wire.write(e.ip,4);
    break;
    case I2C_MACADDRESS:
      Wire.write(e.mac,6);
    break;
    default:
    break;
  }
}
