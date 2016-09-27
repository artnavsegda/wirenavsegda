#include <EEPROM.h>
#include <Wire.h>

#define I2C_IPADDRESS 100
#define I2C_MACADDRESS 101
#define I2C_LENGTHTABLE 102

struct MyObject {
  byte ip[4];
  byte mac[6];
  unsigned short length_table[13];
  byte jump_table[13];
};

int memaddr;
MyObject e;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(0, e);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
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
    case I2C_LENGTHTABLE:
      Wire.write((byte *)e.length_table,26);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
