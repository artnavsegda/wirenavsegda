#include <EEPROM.h>
#include <Wire.h>
#include "settings.h"

int memaddr;
MyObject e;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(0, e);
  Wire.begin(8);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.println("lentth table:");
  Serial.print("startlevel: ");Serial.println(e.length_table.startlevel);
  Serial.print("celldelay: ");Serial.println(e.length_table.celldelay);
  Serial.print("celllevel: ");Serial.println(e.length_table.celllevel);
  Serial.print("zerodelay: ");Serial.println(e.length_table.zerodelay);
  Serial.print("zerotest: ");Serial.println(e.length_table.zerotest);
  Serial.print("purge: ");Serial.println(e.length_table.purge);
  Serial.print("totalmercurydelay: ");Serial.println(e.length_table.totalmercurydelay);
  Serial.print("totalmercury: ");Serial.println(e.length_table.totalmercury);
  Serial.print("elementalmercurydelay: ");Serial.println(e.length_table.elementalmercurydelay);
  Serial.print("elementalmercury: ");Serial.println(e.length_table.elementalmercury);
  Serial.print("precalibrationdelay: ");Serial.println(e.length_table.precalibrationdelay);
  Serial.print("calibration: ");Serial.println(e.length_table.calibration);
  Serial.print("postcalibrationdelay: ");Serial.println(e.length_table.postcalibrationdelay);
  
  Serial.println("jump table:");
  Serial.print("startlevel: ");Serial.println(e.jump_table.startlevel);
  Serial.print("celldelay: ");Serial.println(e.jump_table.celldelay);
  Serial.print("celllevel: ");Serial.println(e.jump_table.celllevel);
  Serial.print("zerodelay: ");Serial.println(e.jump_table.zerodelay);
  Serial.print("zerotest: ");Serial.println(e.jump_table.zerotest);
  Serial.print("purge: ");Serial.println(e.jump_table.purge);
  Serial.print("totalmercurydelay: ");Serial.println(e.jump_table.totalmercurydelay);
  Serial.print("totalmercury: ");Serial.println(e.jump_table.totalmercury);
  Serial.print("elementalmercurydelay: ");Serial.println(e.jump_table.elementalmercurydelay);
  Serial.print("elementalmercury: ");Serial.println(e.jump_table.elementalmercury);
  Serial.print("precalibrationdelay: ");Serial.println(e.jump_table.precalibrationdelay);
  Serial.print("calibration: ");Serial.println(e.jump_table.calibration);
  Serial.print("postcalibrationdelay: ");Serial.println(e.jump_table.postcalibrationdelay);
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
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
