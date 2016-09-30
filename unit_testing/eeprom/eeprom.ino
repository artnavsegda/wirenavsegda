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
  int startlevel;
  int celldelay;
  int celllevel;
  int zerodelay;
  int zerotest;
  int purge;
  int totalmercurydelay;
  int totalmercury;
  int elementalmercurydelay;
  int elementalmercury;
  int precalibrationdelay;
  int calibration;
  int postcalibrationdelay;
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
