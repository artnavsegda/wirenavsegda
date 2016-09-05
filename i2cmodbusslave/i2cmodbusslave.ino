#include <EEPROM.h>
#include <Wire.h>
#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

float STARTCODE=5.0;
float STARTTOTAL=1.0;
float STARTOXIDIZED=1.0;
float STARTMONITOR=1.0;
float STARTVACUUM=1.0;
float STARTDILUTION=1.0;
float STARTBYPASS=1.0;
float STARTTEMP=1.0;
float STARTELEMENTAL=1.0;
float STARTERROR=1.0;
float STARTCOEFF=1.0;

#define MSB(u16) (((uint8_t* )&u16)[1])
#define LSB(u16) (((uint8_t* )&u16)[0])

#define  MSW(u32)          (((uint16_t*)&u32)[1])
#define  LSW(u32)          (((uint16_t*)&u32)[0])

ModbusIP mb;
int memaddr;
int regdata;

void setcoils(int start, int amount)
{
  for (int i = start; i < amount; i++)
    mb.addCoil(i);
}

void sethregs(int start, int amount)
{
  for (int i = start; i < amount; i++)
    mb.addHreg(i);
}

void savepermanent(void)
{
  LSW(STARTCODE) = mb.Hreg(8); MSW(STARTCODE) = mb.Hreg(9); EEPROM.put(100, STARTCODE);
  LSW(STARTTOTAL) = mb.Hreg(10); MSW(STARTTOTAL) = mb.Hreg(11); EEPROM.put(104, STARTTOTAL);
  LSW(STARTOXIDIZED) = mb.Hreg(12); MSW(STARTOXIDIZED) = mb.Hreg(13); EEPROM.put(108, STARTOXIDIZED);
  LSW(STARTMONITOR) = mb.Hreg(14); MSW(STARTMONITOR) = mb.Hreg(15); EEPROM.put(112, STARTMONITOR);
  LSW(STARTVACUUM) = mb.Hreg(16); MSW(STARTVACUUM) = mb.Hreg(17); EEPROM.put(116, STARTVACUUM);
  LSW(STARTDILUTION) = mb.Hreg(18); MSW(STARTDILUTION) = mb.Hreg(19); EEPROM.put(120, STARTDILUTION);
  LSW(STARTBYPASS) = mb.Hreg(20); MSW(STARTBYPASS) = mb.Hreg(21); EEPROM.put(124, STARTBYPASS);
  LSW(STARTTEMP) = mb.Hreg(22); MSW(STARTTEMP) = mb.Hreg(23); EEPROM.put(128, STARTTEMP);
  LSW(STARTELEMENTAL) = mb.Hreg(24); MSW(STARTELEMENTAL) = mb.Hreg(25); EEPROM.put(132, STARTELEMENTAL);
  LSW(STARTERROR) = mb.Hreg(28); MSW(STARTERROR) = mb.Hreg(29); EEPROM.put(140, STARTERROR);
  LSW(STARTCOEFF) = mb.Hreg(30); MSW(STARTCOEFF) = mb.Hreg(31); EEPROM.put(144, STARTCOEFF);
}

void startvalues(void)
{
  mb.Coil(0,false);//status of spectrometer
  mb.Coil(1,true);//status of thermocontrollers
  mb.Coil(2,false);//availability for external request
  mb.Coil(3,false);//status of zero test
  mb.Coil(4,false);//status of calibration
  /*EEPROM.get(100, STARTCODE);
  EEPROM.get(104, STARTTOTAL);
  EEPROM.get(108, STARTOXIDIZED);
  EEPROM.get(112, STARTMONITOR);
  EEPROM.get(116, STARTVACUUM);
  EEPROM.get(120, STARTDILUTION);
  EEPROM.get(124, STARTBYPASS);
  EEPROM.get(128, STARTTEMP);
  EEPROM.get(132, STARTELEMENTAL);
  EEPROM.get(140, STARTERROR);
  EEPROM.get(144, STARTCOEFF);*/
  mb.Hreg(8,LSW(STARTCODE));mb.Hreg(9,MSW(STARTCODE));//code of current mode
  mb.Hreg(10,LSW(STARTTOTAL)); mb.Hreg(11,MSW(STARTTOTAL));//total
  mb.Hreg(12,LSW(STARTOXIDIZED)); mb.Hreg(13,MSW(STARTOXIDIZED));//oxidized
  mb.Hreg(14,LSW(STARTMONITOR)); mb.Hreg(15,MSW(STARTMONITOR));//monitor flow
  mb.Hreg(16,LSW(STARTVACUUM)); mb.Hreg(17,MSW(STARTVACUUM));//vacuum
  mb.Hreg(18,LSW(STARTDILUTION)); mb.Hreg(19,MSW(STARTDILUTION));//dilution pressure
  mb.Hreg(20,LSW(STARTBYPASS)); mb.Hreg(21,MSW(STARTBYPASS));//bypass pressure
  mb.Hreg(22,LSW(STARTTEMP)); mb.Hreg(23,MSW(STARTTEMP));//temp
  mb.Hreg(24,LSW(STARTELEMENTAL)); mb.Hreg(25,MSW(STARTELEMENTAL));//elemental
  mb.Hreg(26); mb.Hreg(27);//not used
  mb.Hreg(28,LSW(STARTERROR)); mb.Hreg(29,MSW(STARTERROR));//errors and warnings
  mb.Hreg(30,LSW(STARTCOEFF)); mb.Hreg(31,MSW(STARTCOEFF));//coefficient
  mb.Hreg(32); mb.Hreg(33);//PMT current
  mb.Hreg(40); mb.Hreg(41);//PMT voltage arb
  mb.Hreg(42); mb.Hreg(43);//PMT voltage V
  mb.Coil(99,false);//run calibration
  mb.Coil(100,false);//run zero test
  mb.Coil(101,false);//run elemental
  mb.Coil(102,false);//start purge
  mb.Coil(103,false);//end purge
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  byte ip[] = { 192, 168, 1, 120 };
  mb.config(mac, ip);
  setcoils(0,6);
  sethregs(8,52);
  setcoils(99,104);
  startvalues();
}

void loop() {
  // put your main code here, to run repeatedly:
  mb.task();
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  switch (howMany) {
    case 2:
      mb.Coil(memaddr,Wire.read());
    break;
    case 3:
      LSB(regdata) = Wire.read();
      MSB(regdata) = Wire.read();
      mb.Hreg(memaddr,regdata);
    break;
    case 5:
      LSB(regdata) = Wire.read();
      MSB(regdata) = Wire.read();
      mb.Hreg(memaddr,regdata);
      LSB(regdata) = Wire.read();
      MSB(regdata) = Wire.read();
      mb.Hreg(memaddr+1,regdata);
    break;
    default:
    break;
  }
}

void requestEvent() {
  if (memaddr<=5||memaddr>=99)
    Wire.write(mb.Coil(memaddr));
  else {
    uint16_t replymessage = mb.Hreg(memaddr);
    uint8_t buf[2];
    buf[0] = LSB(replymessage);
    buf[1] = MSB(replymessage);
    Wire.write(buf,2);
  }
}

