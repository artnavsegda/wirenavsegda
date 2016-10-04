#include <EEPROM.h>
#include <EtherCard.h>

byte Ethernet::buffer[300];   // a very small tcp/ip buffer is enough here
MyObject e;

void setup () {
  EEPROM.get(0, e);
  if (ether.begin(sizeof Ethernet::buffer, e.mac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(e.ip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
}
