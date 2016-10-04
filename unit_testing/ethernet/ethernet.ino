#include <EEPROM.h>
#include <EtherCard.h>
#include "settings.h"

byte Ethernet::buffer[300];   // a very small tcp/ip buffer is enough here
MyObject e;

void setup () {
  Serial.begin(9600);
  EEPROM.get(0, e);
  if (ether.begin(sizeof Ethernet::buffer, e.mac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(e.ip);
  ether.printIp("My IP: ", ether.myip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
}
