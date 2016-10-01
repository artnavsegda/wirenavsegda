#include <EEPROM.h>
#include <Wire.h>

#define I2C_IPADDRESS 100
#define I2C_MACADDRESS 101
#define I2C_LENGTHTABLE 102
#define I2C_JUMPTABLE 103

#define I2C_ELEMENTALMERCURYROW 128
#define I2C_TOTALMERCURYROW 129
#define I2C_OXIDIZEDMERCURYROW 130
#define I2C_MONITORFLOW 131
#define I2C_VACUUM 132
#define I2C_DILUTIONPRESSURE 133
#define I2C_BYPASSPRESSURE 134
#define I2C_TEMPERATUREOFSPECTROMETER 135
#define I2C_CODEOFACURRENTMODE 136
#define I2C_ERRORSANDWARNINGS 137
#define I2C_TOTALMERCURYCOEFFICENT 138

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

int memaddr;
MyObject e;
float totalmercuryrow;
float monitorflow;

void setup() {
  // put your setup code here, to run once:
  EEPROM.get(0, e);
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case I2C_TOTALMERCURYROW:
        Wire.readBytes((byte *)&totalmercuryrow, 4);
        Serial.println(totalmercuryrow);
      break;
      case I2C_MONITORFLOW:
        Wire.readBytes((byte *)&monitorflow, 4);
        Serial.println(monitorflow);
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
    case I2C_LENGTHTABLE:
      Wire.write((byte *)&e.length_table,26);
    break;
    case I2C_JUMPTABLE:
      Wire.write((byte *)&e.jump_table,26);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
