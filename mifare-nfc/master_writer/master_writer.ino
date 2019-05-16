// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void extenderWrite(uint8_t pin, uint8_t val)
{
  Wire.beginTransmission(0x3C); // !!!!!!!!!!!!!!
  if (val == HIGH)
    Wire.write(0xFF);
  if (val == LOW)
    Wire.write(~bit(pin));
  Wire.endTransmission(); 
}

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop() {
  extenderWrite(0,HIGH);
  delay(500);
  extenderWrite(0,LOW);
  delay(500);
}
