#include <EEPROM.h>
#include <Wire.h>

struct MyObject {
  byte ip[4];
  byte mac[6];
  byte length_table[26];
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
    case 100:
      Wire.write(e.ip,4);
    break;
    case 101:
      Wire.write(e.mac,6);
    break;
    case 102:
      Wire.write(e.length_table,26);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
