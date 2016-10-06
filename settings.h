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

struct jumptablestruct startstate = {
	.startlevel = CELLDELAY,
	.celldelay = CELLLEVEL,
	.celllevel = TOTALMERCURYDELAY,
	.zerodelay = ZEROTEST,
	.zerotest = TOTALMERCURYDELAY,
	.purge = TOTALMERCURYDELAY,
	.totalmercurydelay = TOTALMERCURY,
	.totalmercury = TOTALMERCURY,
	.elementalmercurydelay = ELEMENTALMERCURY,
	.elementalmercury = TOTALMERCURY,
	.precalibrationdelay = CALIBRATION,
	.calibration = POSTCALIBRATIONDELAY,
	.postcalibrationdelay = TOTALMERCURYDELAY
};

struct eeprom
{
	unsigned char ip[4];
	unsigned char mac[6];
	struct lengthtablestruct length_table;
	struct jumptablestruct jump_table;
  unsigned char ad7705_setup_register;
  unsigned char ad7705_clock_register;
  unsigned char ad7705_zeroscale_calibration_register[3];
  unsigned char ad7705_fullscale_calibration_register[3];
};
