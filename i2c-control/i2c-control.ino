#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x03));            // sends instruction byte
  Wire.write(byte(0x3F));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
}

void loop() {
  Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x01));            // sends instruction byte
  Wire.write(byte(0x40));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
  delay(5000);
  Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x01));            // sends instruction byte
  Wire.write(byte(0x80));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
  delay(5000);
}

