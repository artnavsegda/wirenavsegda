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
  addcoils();
  addfloats();
  mb.addIreg(6,123);
}

void loop() {
  mb.task();
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case STATUSOFSPECTROMETER: mb.Coil(myeeprom.modbustable.statusofspectrometer,Wire.read()); break;
      case STATUSOFTHERMOCONTROLLERS: mb.Coil(myeeprom.modbustable.statusofthermocontrollers,Wire.read()); break;
      case AVAILABILITYOFEXTERNALREQUEST: mb.Coil(myeeprom.modbustable.availabilityforexternalrequest,Wire.read()); break;
      case STATUSOFZEROTEST: mb.Coil(myeeprom.modbustable.statusofzerotest,Wire.read()); break;
      case STATUSOFCALIBRATION: mb.Coil(myeeprom.modbustable.statusofcalibration,Wire.read()); break;
      case REQUESTTOSTARTCALIBRATION: mb.Coil(myeeprom.modbustable.runcalibration,Wire.read()); break;
      case REQUESTTOSTARTZEROTEST: mb.Coil(myeeprom.modbustable.runzerotest,Wire.read()); break;
      case REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY: mb.Coil(myeeprom.modbustable.runelemental,Wire.read()); break;
      case REQUESTTOSTARTPURGE: mb.Coil(myeeprom.modbustable.startpurge,Wire.read()); break;
      case REQUESTTOENDPURGE: mb.Coil(myeeprom.modbustable.endpurge,Wire.read()); break;
      case 2:
        Wire.readBytes((byte *)&x,sizeof(x));
        Serial.println(x);
        mb.Ireg(6,x);
       break;
      case 3:
        Wire.readBytes((byte *)&y,sizeof(y));
        Serial.println(y);
      break;
      case 4:
        Wire.readBytes(z,sizeof(z));
        Serial.println(z);
      default:
      break;
    }
}

void requestEvent() {
  switch (memaddr) {
    case I2C_IPADDRESS: Wire.write(myeeprom.ip,4); break;
    case I2C_MACADDRESS: Wire.write(myeeprom.mac,6); break;
    case I2C_LENGTHTABLE: Wire.write((byte *)&myeeprom.length_table,26); break;
    case I2C_JUMPTABLE: Wire.write((byte *)&myeeprom.jump_table,13); break;
    case I2C_AD7705_SETUP_REGISTER: Wire.write(myeeprom.ad7705_setup_register); break;
    case I2C_AD7705_CLOCK_REGISTER: Wire.write(myeeprom.ad7705_clock_register); break;
    case STATUSOFSPECTROMETER: Wire.write(mb.Coil(myeeprom.modbustable.statusofspectrometer); break;
    case STATUSOFTHERMOCONTROLLERS: Wire.write(mb.Coil(myeeprom.modbustable.statusofthermocontrollers); break;
    case AVAILABILITYOFEXTERNALREQUEST: Wire.write(mb.Coil(myeeprom.modbustable.availabilityforexternalrequest); break;
    case STATUSOFZEROTEST: Wire.write(mb.Coil(myeeprom.modbustable.statusofzerotest); break;
    case STATUSOFCALIBRATION: Wire.write(mb.Coil(myeeprom.modbustable.statusofcalibration); break;
    case REQUESTTOSTARTCALIBRATION: Wire.write(mb.Coil(myeeprom.modbustable.runcalibration); break;
    case REQUESTTOSTARTZEROTEST: Wire.write(mb.Coil(myeeprom.modbustable.runzerotest); break;
    case REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY: Wire.write(mb.Coil(myeeprom.modbustable.runelemental); break;
    case REQUESTTOSTARTPURGE: Wire.write(mb.Coil(myeeprom.modbustable.startpurge); break;
    case REQUESTTOENDPURGE:Wire.write(mb.Coil(myeeprom.modbustable.endpurge); break;
    default:
    break;
  }
}
