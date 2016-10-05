#include <EEPROM.h>
#include "settings.h"

MyObject e;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(0, e);
  Serial.begin(9600);
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

void loop() {
  // put your main code here, to run repeatedly:

}
