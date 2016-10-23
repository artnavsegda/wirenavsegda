void addcoils(void) {
  mb.addCoil(myeeprom.modbustable.statusofspectrometer);
  mb.addCoil(myeeprom.modbustable.statusofthermocontrollers);
  mb.addCoil(myeeprom.modbustable.availabilityforexternalrequest);
  mb.addCoil(myeeprom.modbustable.statusofzerotest);
  mb.addCoil(myeeprom.modbustable.statusofcalibration);
  mb.addCoil(myeeprom.modbustable.runcalibration);
  mb.addCoil(myeeprom.modbustable.runcalibration);
  mb.addCoil(myeeprom.modbustable.runelemental);
  mb.addCoil(myeeprom.modbustable.startpurge);
  mb.addCoil(myeeprom.modbustable.endpurge);
}

void addfloat(flowaddress address) {
  mb.addHreg(address.msw);
  mb.addHreg(address.lsw);
}

void addfloats(void) {
  addfloat(myeeprom.modbustable.elementalmercury);
  addfloat(myeeprom.modbustable.totalmercury);
  addfloat(myeeprom.modbustable.oxidizedmercury);
  addfloat(myeeprom.modbustable.monitorflow);
  addfloat(myeeprom.modbustable.vacuum);
  addfloat(myeeprom.modbustable.dilutionpressure);
  addfloat(myeeprom.modbustable.bypasspressure);
  addfloat(myeeprom.modbustable.temperatureofspectrometer);
  addfloat(myeeprom.modbustable.codeofacurrentmode);
  addfloat(myeeprom.modbustable.errorsandwarnings);
  addfloat(myeeprom.modbustable.calibrationcoefficent);
}
