#include <EEPROM.h>
#include <Wire.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include "settings.h"

ModbusIP mb;
MyObject myeeprom;
uint8_t memaddr;

void addcoils(void) {
  for (int i; i < sizeof(i2c_coils);i++)
    mb.addCoil(i2c_address_to_modbus_number(i2c_coils[i]);
}

void addfloat(uint16_t address) {
  mb.addHreg(address);
  mb.addHreg(address+1);
}

void addfloats(void) {
  for (int i; i < sizeof(i2c_floats);i++)
    addfloat(i2c_address_to_modbus_number(i2c_floats[i]);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  EEPROM.get(0, myeeprom);
  printeeprom(myeeprom);
  mb.config(myeeprom.mac, myeeprom.ip);
  addcoils();
  addfloats();
  mb.addIreg(6,123);
}

void loop() {
  mb.task();
}

enum what_i2c_data_is_that(uint8_t i2caddr) {
  if (rawmemchr(i2c_coils,i2caddr)!=NULL)
    return MODBUS_COIL;
  else if (rawmemchr(i2c_floats,i2caddr)!=NULL)
    return MODBUS_FLOAT;
  else
    return MODBUS_UNKNOWN;
}

uint16_t i2c_address_to_modbus_number(uint8_t i2caddr) {
  return modbus_position[i2caddr];
}

void write_double_modbus_registers(uint8_t i2caddr) {
  float datatowrite;
  Wire.readBytes((byte *)&datatowrite,sizeof(datatowrite));
  uint16_t registertouse = i2c_address_to_modbus_number[i2caddr];
  mb.Hreg(registertouse,LSW(datatowrite);
  mb.Hreg(registertouse+1,MSW(datatowrite);
}

void read_double_modbus_registers(uint8_t i2caddr) {
  float datatoread;
  uint16_t registertouse = i2c_address_to_modbus_number[i2caddr];
  LSW(datatoread) = mb.Hreg(registertouse);
  MSW(datatoread) = mb.Hreg(registertouse+1);
  Wire.write((byte *)&datatoread,4);
}

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
  {
    switch (memaddr) {
    case I2C_IPADDRESS:
      Wire.readBytes(myeeprom.ip,4);
    break;
    case I2C_MACADDRESS:
      Wire.readBytes(myeeprom.mac,6);
    break;
    case I2C_LENGTHTABLE:
      Wire.readBytes((byte *)&myeeprom.length_table,26);
    break;
    case I2C_JUMPTABLE:
      Wire.readBytes((byte *)&myeeprom.jump_table,13);
    break;
    case I2C_AD7705_SETUP_REGISTER:
      myeeprom.ad7705_setup_register = Wire.read();
    break;
    case I2C_AD7705_CLOCK_REGISTER:
      myeeprom.ad7705_clock_register = Wire.read();
    break;
    default:
      switch (what_i2c_data_is_that(memaddr)) {
        case MODBUS_COIL:
          mb.Coil(i2c_address_to_modbus_number(memaddr),Wire.read());
        break;
        case MODBUS_FLOAT:
          write_double_modbus_registers(memaddr);
        default:
        break;
      }
    break;
  }
}

void requestEvent() {
  switch (memaddr) {
    case I2C_IPADDRESS:
      Wire.write(myeeprom.ip,4);
    break;
    case I2C_MACADDRESS:
      Wire.write(myeeprom.mac,6);
    break;
    case I2C_LENGTHTABLE:
      Wire.write((byte *)&myeeprom.length_table,26);
    break;
    case I2C_JUMPTABLE:
      Wire.write((byte *)&myeeprom.jump_table,13);
    break;
    case I2C_AD7705_SETUP_REGISTER:
      Wire.write(myeeprom.ad7705_setup_register);
    break;
    case I2C_AD7705_CLOCK_REGISTER:
      Wire.write(myeeprom.ad7705_clock_register);
    break;
    default:
      switch (what_i2c_data_is_that(memaddr)) {
        case MODBUS_COIL:
          Wire.write(mb.Coil(i2c_address_to_modbus_number(memaddr));
        break;
        case MODBUS_FLOAT:
          read_double_modbus_registers(memaddr);
        default:
        break;
      }
    break;
  }
}
