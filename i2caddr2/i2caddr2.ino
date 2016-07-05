// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#define MSB(u16) (((uint8_t* )&u16)[1])
#define LSB(u16) (((uint8_t* )&u16)[0])

#include <Wire.h>

int x, y;
int memaddr;
int firstbyte;
int secondbyte;
int massive[255];

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  /*while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }*/
  if (Wire.available())
  {
    Serial.println("memory address recieved");
    memaddr = Wire.read();
  }
  if (Wire.available())
  {
    Serial.println("first content byte recieved");
    firstbyte = Wire.read();
  }
  if (Wire.available())
  {
    Serial.println("second content byte recieved");
    secondbyte = Wire.read();
  }
  if (howMany == 2)
  {
    massive[memaddr] = firstbyte;
  }
  if (howMany == 3)
  {
    LSB(massive[memaddr]) = firstbyte;
    MSB(massive[memaddr]) = secondbyte;
  }
  Serial.println(howMany);         // print the integer
  Serial.println(Wire.available());
  //x = Wire.read();    // receive byte as an integer

}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  //Wire.write(massive[memaddr]);
  //Wire.write(0x00);
  
  //int x = 0x1678;
  
  //Wire.write(x);
  //Wire.write(x>>8);
  
  //Wire.write(massive[memaddr]);
  //Wire.write(massive[memaddr]>>8);

  Wire.write(LSB(massive[memaddr]));
  Wire.write(MSB(massive[memaddr]));
}

