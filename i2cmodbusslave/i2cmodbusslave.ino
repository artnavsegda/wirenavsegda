#include <Wire.h>
#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

ModbusIP mb;
int memaddr;
int firstbyte;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  byte ip[] = { 192, 168, 1, 120 };
  mb.config(mac, ip);
  mb.addHreg(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  mb.task();
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    memaddr = Wire.read();
  }
  if (Wire.available()) {
    firstbyte = Wire.read();
    mb.Hreg(memaddr,firstbyte);
  }
}

