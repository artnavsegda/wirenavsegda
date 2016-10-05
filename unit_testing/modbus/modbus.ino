#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include "settings.h"

ModbusIP mb;
MyObject myeeprom;
int memaddr;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, myeeprom);
  printeeprom(myeeprom);
  mb.config(myeeprom.mac, myeeprom.ip);
  mb.addIreg(6,123);
}

void loop() {
  mb.task();
}

int i;
int x;
float y;
char z[5];

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case 5:
        i = Wire.read();
        Serial.println(i);
      break;
      case 6:
        Wire.readBytes((byte *)&x,sizeof(x));
        Serial.println(x);
        mb.Ireg(6,x);
       break;
      case 7:
        Wire.readBytes((byte *)&y,sizeof(y));
        Serial.println(y);
      break;
      case 8:
        Wire.readBytes(z,sizeof(z));
        Serial.println(z);
      default:
      break;
    }
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
