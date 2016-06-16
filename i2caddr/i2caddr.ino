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
  analogReadResolution(12);
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

void sendInt(int num){

  // Send low byte
  Wire.write((uint8_t)num);

  // Send high byte
  num >>= 8;
  Wire.write((uint8_t)num);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  switch(x)
  {
    case 0x00:
      sendInt(analogRead(A0));
      break;
    case 0x01:
      sendInt(analogRead(A1));
      break;
    case 0x02:
      sendInt(analogRead(A2));
      break;
    case 0x03:
      sendInt(analogRead(A3));
      break;
    case 0x04:
      sendInt(analogRead(A4));
      break;
    case 0x05:
      sendInt(analogRead(A5));
      break;
    case 0x06:
      sendInt(analogRead(A6));
      break;
    case 0x07:
      sendInt(analogRead(A7));
      break;
    case 0x08:
      sendInt(analogRead(A8));
      break;
    case 0x09:
      sendInt(analogRead(A9));
      break;
    case 0x0a:
      sendInt(analogRead(A10));
      break;
    case 0x0b:
      sendInt(analogRead(A11));
      break;
    default:
      break;
  }
}
