#include <Wire.h>
#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

#define MSB(u16) (((uint8_t* )&u16)[1])
#define LSB(u16) (((uint8_t* )&u16)[0])

#define STARTLEVEL 5
#define NODATA 1

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
  mb.addHreg(8,STARTLEVEL);//code of current mode
  mb.addHreg(9);//code of current mode - blank ?
  mb.addHreg(10); mb.addHreg(11);//total
  mb.addHreg(12); mb.addHreg(13);//oxidized
  mb.addHreg(14); mb.addHreg(15);//monitor flow
  mb.addHreg(16); mb.addHreg(17);//vacuum
  mb.addHreg(18); mb.addHreg(19);//dilution pressure
  mb.addHreg(20); mb.addHreg(21);//bypass pressure
  mb.addHreg(22); mb.addHreg(23);//temp
  mb.addHreg(28,NODATA);//errors and warnings
  mb.addHreg(30); mb.addHreg(31);//vacuum
  mb.addCoil(1,false);//status of spectrometer
  mb.addCoil(2,true);//status of thermocontrollers
  mb.addCoil(3,false);//availibility for external request
  mb.addCoil(4,false);//status of zero test
  mb.addCoil(5,false);//status of calibration
  mb.addCoil(99,false);//run calibration
  mb.addCoil(100,false);//run zero test
  mb.addCoil(101,false);//run elemental
  mb.addCoil(102,false);//start purge
  mb.addCoil(103,false);//end purge
}

void loop() {
  // put your main code here, to run repeatedly:
  mb.task();
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    firstbyte = Wire.read();
  if (Wire.available())
    secondbyte = Wire.read();
  if (howMany == 2)
    mb.Coil(memaddr,firstbyte);
  if (howMany == 3) {
    LSB(regdata) = firstbyte;
    MSB(regdata) = secondbyte;
    mb.Hreg(memaddr,regdata);
  }
}

void requestEvent() {
  uint8_t buf[2];
  uint16_t replymessage;
  if (memaddr<=5||memaddr>=99)
      Wire.write(mb.Coil(memaddr));
  else {
    replymessage = mb.Hreg(memaddr);
    buf[0] = LSB(replymessage);
    buf[1] = MSB(replymessage);
    Wire.write(buf,2);
  }
}
