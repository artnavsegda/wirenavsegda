#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(0x1a); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x03));            // sends instruction byte
  Wire.write(byte(0x00));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  Wire.beginTransmission(0x1a); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x01));            // sends instruction byte
  Wire.write(byte(0x00));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(1000);
  Wire.beginTransmission(0x1a); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x01));            // sends instruction byte
  Wire.write(byte(0xFF));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(1000);
}

