/*
  Digital Pot Control

  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.

 The AD5206 is SPI-compatible,and to command it, you send two bytes,
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).

 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)

 created 10 Aug 2010
 by Tom Igoe

 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005

*/


// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 8;

void setup() {
  Serial.begin(9600);
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  digitalWrite(12, HIGH); 
  // initialize SPI:
  SPI.begin();
  //SPI.beginTransaction(SPISettings(50000, MSBFIRST, SPI_MODE3));
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE3);
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0x20);
  SPI.transfer(0x0C);
  SPI.transfer(0x10);
  SPI.transfer(0x40);
  digitalWrite(slaveSelectPin, HIGH);
}

void loop() {
  byte value;
  int one, two;
  digitalWrite(slaveSelectPin, LOW);
  SPI.transfer(0x00);
  SPI.transfer(0x08);
  //delay(1);
  value = SPI.transfer(0x00);
  Serial.println(String(value));
  /*if (value == 0)
  {
    SPI.transfer((void *)"\0\0\0\0\0\0\0\0\0\0\0",10);
    delay(100);
  }*/
  if (value == 8)
  {
    SPI.transfer(0x38);
    one = SPI.transfer(0x00);
    two = SPI.transfer(0x00);
    Serial.println(String(one));
    Serial.println(String(two));
    delay(100);
  }
  digitalWrite(slaveSelectPin, HIGH);
  delay(100);

}
