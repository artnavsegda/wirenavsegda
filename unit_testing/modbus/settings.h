enum modbustype {
  MODBUS_COIL,
  MODBUS_FLOAT,
  MODBUS_UNKNOWN,
}

enum i2c_location {
  //coil register addressing 1
  I2C_STATUSOFSPECTROMETER,
  I2C_STATUSOFTHERMOCONTROLLERS,
  I2C_AVAILABILITYOFEXTERNALREQUEST,
  I2C_STATUSOFZEROTEST,
  I2C_STATUSOFCALIBRATION,
  //holding register addressing
  I2C_ELEMENTALMERCURYROW,
  I2C_TOTALMERCURYROW,
  I2C_OXIDIZEDMERCURYROW,
  I2C_MONITORFLOW,
  I2C_VACUUM,
  I2C_DILUTIONPRESSURE,
  I2C_BYPASSPRESSURE,
  I2C_TEMPERATUREOFSPECTROMETER,
  I2C_CODEOFACURRENTMODE,
  I2C_ERRORSANDWARNINGS,
  I2C_TOTALMERCURYCOEFFICENT,
  //coil register addressing 2
  I2C_REQUESTTOSTARTCALIBRATION,
  I2C_REQUESTTOSTARTZEROTEST,
  I2C_REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY,
  I2C_REQUESTTOSTARTPURGE,
  I2C_REQUESTTOENDPURGE,
  //settings
  I2C_IPADDRESS,
  I2C_MACADDRESS,
  I2C_LENGTHTABLE,
  I2C_JUMPTABLE,
  I2C_AD7705_SETUP_REGISTER,
  I2C_AD7705_CLOCK_REGISTER,
};

enum modbus_location {
  //coil register addressing 1
  MB_STATUSOFSPECTROMETER = 0,
  MB_STATUSOFTHERMOCONTROLLERS = 1,
  MB_AVAILABILITYOFEXTERNALREQUEST = 2,
  MB_STATUSOFZEROTEST = 3,
  MB_STATUSOFCALIBRATION = 4,
  //holding register addressing
  MB_CODEOFACURRENTMODE = 8,
  MB_TOTALMERCURYROW = 10,
  MB_OXIDIZEDMERCURYROW = 12,
  MB_MONITORFLOW = 14,
  MB_VACUUM = 16,
  MB_DILUTIONPRESSURE = 18,
  MB_BYPASSPRESSURE = 20,
  MB_TEMPERATUREOFSPECTROMETER = 22,
  MB_ELEMENTALMERCURYROW = 24,
  MB_ERRORSANDWARNINGS = 28,
  MB_TOTALMERCURYCOEFFICENT = 30,
  //coil register addressing 2
  MB_REQUESTTOSTARTCALIBRATION = 99,
  MB_REQUESTTOSTARTZEROTEST = 100,
  MB_REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY = 101,
  MB_REQUESTTOSTARTPURGE = 102,
  MB_REQUESTTOENDPURGE = 103,
};

const enum modbus_position[] = {
  //coil register addressing 1
  MB_STATUSOFSPECTROMETER,
  MB_STATUSOFTHERMOCONTROLLERS,
  MB_AVAILABILITYOFEXTERNALREQUEST,
  MB_STATUSOFZEROTEST,
  MB_STATUSOFCALIBRATION,
  //holding register addressing
  MB_CODEOFACURRENTMODE,
  MB_TOTALMERCURYROW,
  MB_OXIDIZEDMERCURYROW,
  MB_MONITORFLOW,
  MB_VACUUM,
  MB_DILUTIONPRESSURE,
  MB_BYPASSPRESSURE,
  MB_TEMPERATUREOFSPECTROMETER,
  MB_ELEMENTALMERCURYROW,
  MB_ERRORSANDWARNINGS,
  MB_TOTALMERCURYCOEFFICENT,
  //coil register addressing 2
  MB_REQUESTTOSTARTCALIBRATION,
  MB_REQUESTTOSTARTZEROTEST,
  MB_REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY,
  MB_REQUESTTOSTARTPURGE,
  MB_REQUESTTOENDPURGE,
};

const enum i2c_coils[] = {
  I2C_STATUSOFSPECTROMETER,
  I2C_STATUSOFTHERMOCONTROLLERS,
  I2C_AVAILABILITYOFEXTERNALREQUEST,
  I2C_STATUSOFZEROTEST,
  I2C_STATUSOFCALIBRATION,
  I2C_REQUESTTOSTARTCALIBRATION,
  I2C_REQUESTTOSTARTZEROTEST,
  I2C_REQUESTTOSTARTMEASURMENTOFELEMENTALMERCURY,
  I2C_REQUESTTOSTARTPURGE,
  I2C_REQUESTTOENDPURGE,
}

const enum i2c_floats[] = {
  I2C_ELEMENTALMERCURYROW,
  I2C_TOTALMERCURYROW,
  I2C_OXIDIZEDMERCURYROW,
  I2C_MONITORFLOW,
  I2C_VACUUM,
  I2C_DILUTIONPRESSURE,
  I2C_BYPASSPRESSURE,
  I2C_TEMPERATUREOFSPECTROMETER,
  I2C_CODEOFACURRENTMODE,
  I2C_ERRORSANDWARNINGS,
  I2C_TOTALMERCURYCOEFFICENT,
}

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

