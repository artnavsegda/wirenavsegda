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
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ADC unit test");
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, myeeprom);
  printeeprom(myeeprom);
  mb.config(myeeprom.mac, myeeprom.ip);
  for (int i=0;i<16;i++)
    mb.addIreg(i,666);
}

int i;
int x;
float y;
char z[5];
uint16_t adc_scan_results[16];

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case I2C_ADC0:
      case I2C_ADC1:
      case I2C_ADC2:
      case I2C_ADC3:
      case I2C_ADC4:
      case I2C_ADC5:
      case I2C_ADC6:
      case I2C_ADC7:
      case I2C_ADC8:
      case I2C_ADC9:
      case I2C_ADC10:
      case I2C_ADC11:
      case I2C_ADC12:
      case I2C_ADC13:
      case I2C_ADC14:
      case I2C_ADC15:
        Wire.readBytes((byte *)&adc_scan_results[memaddr], 2);
        mb.Ireg(memaddr,adc_scan_results[memaddr]);
        Serial.print("ADC");
        Serial.print(memaddr);
        Serial.print(" ");
        Serial.println(adc_scan_results[memaddr]);
      break;
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

void loop() {
  mb.task();
}
