#define I2C_IPADDRESS 100
#define I2C_MACADDRESS 101
#define I2C_LENGTHTABLE 102
#define I2C_JUMPTABLE 103
#define I2C_AD7705_SETUP_REGISTER 104
#define I2C_AD7705_CLOCK_REGISTER 105

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
  byte ad7705_setup_register;
  byte ad7705_clock_register;
};

