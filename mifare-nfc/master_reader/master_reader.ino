// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

bool extenderRead(byte bitnumber) {
  Wire.requestFrom(0x3F, 1);

  while (Wire.available()) { // slave may send less than requested
    byte c = Wire.read(); // receive a byte as character
    if (bitRead(c,bitnumber) == 0)
      return LOW;
    if (bitRead(c,bitnumber) == 1)
      return HIGH;
  }
}

void loop() {
    if (extenderRead(6) == LOW)
      Serial.println("NFC is not busy");
    if (extenderRead(6) == HIGH)
      Serial.println("NFC is busy");
  delay(500);
}
