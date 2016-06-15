#include <Wire.h>
#include <TM1638.h>

TM1638 module(6, 5, 7);

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial.begin(9600);  // start serial for output
  Wire.beginTransmission(0x18);
  Wire.write("\x03\x3f");
  Wire.endTransmission();

  Wire.beginTransmission(0x1a);
  Wire.write(0x03);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(0x1a);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
}

uint16_t readvalue(uint8_t addr)
{
  Wire.beginTransmission(0x09); // transmit to device #4
  Wire.write(addr);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(0x09, 2);    // request 6 bytes from slave device #2
  return Wire.read()|Wire.read()<<8; // receive a byte as character
}

void loop() {
  //Serial.println(readvalue(0x00));
  //module.setDisplayToDecNumber(readvalue(0x08)-0x17CC, 0xF0);
  /*Serial.println(readvalue(0x01));
  Serial.println(readvalue(0x02));
  Serial.println(readvalue(0x03));
  Serial.println(readvalue(0x04));
  Serial.println(readvalue(0x05));
  Serial.println(readvalue(0x06));
  Serial.println(readvalue(0x07));*/
  //Wire.beginTransmission(0x18);
  //Wire.write("\x01\x40");
  //Wire.endTransmission();
  //Wire.beginTransmission(0x18);
  //Wire.write("\x01\x80");
  //Wire.endTransmission();
  Wire.beginTransmission(0x1a);
  Wire.write(0x00);
  Wire.write(0xFF);
  Wire.endTransmission();
  delay(500);
}
