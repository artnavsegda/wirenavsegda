#define I2C_IPADDRESS 100
#define I2C_MACADDRESS 101
#define I2C_LENGTHTABLE 102
#define I2C_JUMPTABLE 103
#define I2C_AD7705_SETUP_REGISTER 104
#define I2C_AD7705_CLOCK_REGISTER 105

//coil register addressing
#define STATUSOFSPECTROMETER 200
#define STATUSOFTHERMOCONTROLLERS 201
#define AVAILABILITYOFEXTERNALREQUEST 202
#define STATUSOFZEROTEST 203
#define STATUSOFCALIBRATION 204
#define REQUESTTOSTARTCALIBRATION 205
#define REQUESTTOSTARTZEROTEST 206
#define REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY 207
#define REQUESTTOSTARTPURGE 208
#define REQUESTTOENDPURGE 209

//holding register addressing
#define ELEMENTALMERCURYROW 128
#define TOTALMERCURYROW 129
#define OXIDIZEDMERCURYROW 130
#define MONITORFLOW 131
#define VACUUM 132
#define DILUTIONPRESSURE 133
#define BYPASSPRESSURE 134
#define TEMPERATUREOFSPECTROMETER 135
#define CODEOFACURRENTMODE 136
#define ERRORSANDWARNINGS 137
#define TOTALMERCURYCOEFFICENT 138

/* enum i2clocation {
  //i2c settings location
  I2C_IPADDRESS = 100,
  I2C_MACADDRESS = 101,
  I2C_LENGTHTABLE = 102,
  I2C_JUMPTABLE = 103,
  I2C_AD7705_SETUP_REGISTER = 104,
  I2C_AD7705_CLOCK_REGISTER = 105,
  
  //coil register addressing
  ELEMENTALMERCURYROW = 128,
  TOTALMERCURYROW = 129,
  OXIDIZEDMERCURYROW = 130,
  MONITORFLOW = 131,
  VACUUM = 132,
  DILUTIONPRESSURE = 133,
  BYPASSPRESSURE = 134,
  TEMPERATUREOFSPECTROMETER = 135,
  CODEOFACURRENTMODE = 136,
  ERRORSANDWARNINGS = 137,
  TOTALMERCURYCOEFFICENT = 138,
  
  //holding register addressing
  STATUSOFSPECTROMETER = 200,
  STATUSOFTHERMOCONTROLLERS = 201,
  AVAILABILITYOFEXTERNALREQUEST = 202,
  STATUSOFZEROTEST = 203,
  STATUSOFCALIBRATION = 204,
  REQUESTTOSTARTCALIBRATION = 205,
  REQUESTTOSTARTZEROTEST = 206,
  REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY = 207,
  REQUESTTOSTARTPURGE = 208,
  REQUESTTOENDPURGE = 209
} */

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

struct flowaddress {
  unsigned short msw;
  unsigned short lsw;
};

struct modbustablestruct {
   unsigned short statusofspectrometer;
   unsigned short statusofthermocontrollers;
   unsigned short availabilityforexternalrequest;
   unsigned short statusofzerotest;
   unsigned short statusofcalibration;
   flowaddress elementalmercury;
   flowaddress totalmercury;
   flowaddress oxidizedmercury;
   flowaddress monitorflow;
   flowaddress vacuum;
   flowaddress dilutionpressure;
   flowaddress bypasspressure;
   flowaddress temperatureofspectrometer;
   flowaddress codeofacurrentmode;
   flowaddress errorsandwarnings;
   flowaddress calibrationcoefficent;
   unsigned short runcalibration;
   unsigned short runzerotest;
   unsigned short runelemental;
   unsigned short startpurge;
   unsigned short endpurge;
};

struct MyObject {
  byte ip[4];
  byte mac[6];
  lengthtablestruct length_table;
  jumptablestruct jump_table;
  byte ad7705_setup_register;
  byte ad7705_clock_register;
  modbustablestruct modbustable;
};

