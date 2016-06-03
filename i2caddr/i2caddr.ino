// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int x = 0x00;

void setup()
{
  Wire.begin(9);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  x = Wire.read();    // receive byte as an integer
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  switch(x)
  {
    case 0x00:
      Wire.write(analogRead(A0));
      break;
    case 0x01:
      Wire.write(analogRead(A1));
      break;
    case 0x02:
      Wire.write(analogRead(A2));
      break;
    case 0x03:
      Wire.write(analogRead(A3));
      break;
    case 0x04:
      Wire.write(analogRead(A4));
      break;
    case 0x05:
      Wire.write(analogRead(A5));
      break;
    default:
      break;
  }
}
