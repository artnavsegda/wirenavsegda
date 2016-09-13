#include <EEPROM.h>
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

struct MyObject {
  byte ip[4];
  byte mac[6];
  unsigned short length_table[13];
  byte jump_table[13];
};

//ModbusIP object
ModbusIP mb;

void setup() {
  // put your setup code here, to run once:
  MyObject e;
  EEPROM.get(0, e);
  Serial.begin(9600);
  mb.config(e.mac, e.ip);
  Serial.print("IP: "); Serial.print(e.ip[0],DEC);  Serial.print(e.ip[1],DEC);  Serial.print(e.ip[2],DEC);  Serial.println(e.ip[3],DEC);
  Serial.print("Mac: ");Serial.print(e.mac[0],HEX);Serial.print(e.mac[1],HEX);Serial.print(e.mac[2],HEX);Serial.print(e.mac[3],HEX);Serial.print(e.mac[4],HEX);Serial.println(e.mac[5],HEX);
  Serial.print("Start Level: "); Serial.println(e.length_table[0],DEC);
  Serial.print("Cell Delay: "); Serial.println(e.length_table[1],DEC);
  Serial.print("Cell Level: "); Serial.println(e.length_table[2],DEC);
  Serial.print("Zero Delay: "); Serial.println(e.length_table[3],DEC);
  Serial.print("Zero Test: "); Serial.println(e.length_table[4],DEC);
  Serial.print("Total Mercury Delay: "); Serial.println(e.length_table[5],DEC);
  Serial.print("Total Mercury: "); Serial.println(e.length_table[6],DEC);
  Serial.print("Elemental Mercury Delay: "); Serial.println(e.length_table[7],DEC);
  Serial.print("Elemental Mercury: "); Serial.println(e.length_table[8],DEC);
  Serial.print("Pre-Calibration Delay: "); Serial.println(e.length_table[9],DEC);
  Serial.print("Calibration: "); Serial.println(e.length_table[10],DEC);
  Serial.print("Post-Calibration Delay: "); Serial.println(e.length_table[11],DEC);
  Serial.print("Purge: "); Serial.println(e.length_table[12],DEC);

  mb.addHreg(100, ((uint16_t)e.ip[0]<<8)|e.ip[1]);
  mb.addHreg(101, ((uint16_t)e.ip[2]<<8)|e.ip[3]);
  mb.addHreg(102, ((uint16_t)e.mac[0]<<8)|e.mac[1]);
  mb.addHreg(103, ((uint16_t)e.mac[2]<<8)|e.mac[3]);
  mb.addHreg(104, ((uint16_t)e.mac[4]<<8)|e.mac[5]);
  
  mb.addHreg(105, e.length_table[0]);
  mb.addHreg(106, e.length_table[1]);
  mb.addHreg(107, e.length_table[2]);
  mb.addHreg(108, e.length_table[3]);
  mb.addHreg(109, e.length_table[4]);
  mb.addHreg(110, e.length_table[5]);
  mb.addHreg(111, e.length_table[6]);
  mb.addHreg(112, e.length_table[7]);
  mb.addHreg(113, e.length_table[8]);
  mb.addHreg(114, e.length_table[9]);
  mb.addHreg(115, e.length_table[10]);
  mb.addHreg(116, e.length_table[11]);
  mb.addHreg(117, e.length_table[12]);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();

}
