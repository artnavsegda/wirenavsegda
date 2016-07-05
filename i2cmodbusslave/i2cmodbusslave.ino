#include <Wire.h>
#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

#define MSB(u16) (((uint8_t* )&u16)[1])
#define LSB(u16) (((uint8_t* )&u16)[0])

ModbusIP mb;
int memaddr;
int firstbyte;
int secondbyte;
int regdata;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
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
  }
  if (Wire.available()) {
    secondbyte = Wire.read();
  }
  if (howMany == 2)
  {
    mb.Hreg(memaddr,firstbyte);
  }
  if (howMany == 3)
  {
    LSB(regdata) = firstbyte;
    MSB(regdata) = secondbyte;
    mb.Hreg(memaddr,regdata);
  }
}

void requestEvent() {
  //Wire.write(mb.Hreg(memaddr));
  regdata = mb.Hreg(memaddr);
  Wire.write(LSB(regdata));
  Wire.write(MSB(regdata));
}

