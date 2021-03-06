// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <TM1638.h>
#include <Wire.h>

TM1638 module(6, 5, 7);

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  char buf[100];
  Serial.println(howMany);
  /*while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }*/
  Wire.readBytes(buf,howMany);
  module.setDisplayToString(buf);
  Serial.println(buf);
}

void requestEvent() {
  Wire.write(module.getButtons());
}
