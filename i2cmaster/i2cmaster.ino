#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
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
  Serial.println(readvalue(0x00));
  /*Serial.println(readvalue(0x01));
  Serial.println(readvalue(0x02));
  Serial.println(readvalue(0x03));
  Serial.println(readvalue(0x04));
  Serial.println(readvalue(0x05));
  Serial.println(readvalue(0x06));
  Serial.println(readvalue(0x07));*/
  delay(500);
}
