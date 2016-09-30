#include <EEPROM.h>

enum modelist {
  STARTLEVEL = 5,
  CELLDELAY = 7,
  CELLLEVEL = 8,
  ZERODELAY = 11,
  ZEROTEST = 12,
  PURGE = 13,
  TOTALMERCURYDELAY = 21,
  TOTALMERCURY = 22,
  ELEMENTALMERCURYDELAY = 26,
  ELEMENTALMERCURY = 27,
  PRECALIBRATIONDELAY = 31,
  CALIBRATION = 32,
  POSTCALIBRATIONDELAY = 33
};

struct lengthtablestruct {
  unsigned short startlevel;
  unsigned short celldelay;
  unsigned short celllevel;
  unsigned short zerodelay;
  unsigned short zerotest;
  unsigned short purge;
  unsigned short totalmercurydelay;
  unsigned short totalmercury;
  unsigned short elementalmercurydelay;
  unsigned short elementalmercury;
  unsigned short precalibrationdelay;
  unsigned short calibration;
  unsigned short postcalibrationdelay;
};

struct jumptablestruct {
  enum modelist startlevel;
  enum modelist celldelay;
  enum modelist celllevel;
  enum modelist zerodelay;
  enum modelist zerotest;
  enum modelist purge;
  enum modelist totalmercurydelay;
  enum modelist totalmercury;
  enum modelist elementalmercurydelay;
  enum modelist elementalmercury;
  enum modelist precalibrationdelay;
  enum modelist calibration;
  enum modelist postcalibrationdelay;
};

struct MyObject {
  byte ip[4];
  byte mac[6];
  lengthtablestruct length_table;
  jumptablestruct jump_table;
};

MyObject e;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(0, e);
  Serial.begin(9600);
  Serial.println("EEPROM test");
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
