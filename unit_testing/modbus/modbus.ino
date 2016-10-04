#include <EEPROM.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

ModbusIP mb;
MyObject e;

void setup() {
  EEPROM.get(0, e);
  mb.config(e.mac, e.ip);
}

void loop() {
  //Call once inside loop() - all magic here
  mb.task();
}
