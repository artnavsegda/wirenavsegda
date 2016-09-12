#include <EEPROM.h>

struct MyObject {
  byte ip[4];
  byte mac[6];
  unsigned short length_table[13];
  byte jump_table[13];
};

void setup() {
  // put your setup code here, to run once:
  MyObject e;
  EEPROM.get(0, e);
  Serial.begin(9600);
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
