#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include "settings.h"

ModbusIP mb;
MyObject e;
int memaddr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ADC unit test");
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, e);
  mb.config(e.mac, e.ip);
  for (int i=0;i<16;i++)
    mb.addIreg(i);
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
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
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
      Wire.write(e.ip,4);
    break;
    case I2C_MACADDRESS:
      Wire.write(e.mac,6);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
