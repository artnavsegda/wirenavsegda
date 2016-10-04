#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include "settings.h"

ModbusIP mb;
int memaddr;
unsigned int adcdata;
MyObject e;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("AD7705 unit test");
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, e);
  mb.config(e.mac, e.ip);
  mb.addIreg(0);
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case 0:
        Wire.readBytes((byte *)&adcdata, 2);
        mb.Ireg(0,adcdata);
        Serial.print("AD7705");
        Serial.print(" ");
        Serial.println(adcdata);
      break;
      default:
      break;
    }
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
      Wire.write((byte *)&e.length_table,26);
    break;
    case I2C_JUMPTABLE:
      Wire.write((byte *)&e.jump_table,13);
    break;
    case I2C_AD7705_SETUP_REGISTER:
      Wire.write(e.ad7705_setup_register);
    break;
    case I2C_AD7705_CLOCK_REGISTER:
      Wire.write(e.ad7705_clock_register);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
