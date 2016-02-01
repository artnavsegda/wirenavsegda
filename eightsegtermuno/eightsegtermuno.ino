#include <TM1638.h>
#include <Wire.h>

TM1638 module(6, 5, 7);
byte oldkeys = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
  
  delay(1000);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x03));            // sends instruction byte
  Wire.write(byte(0x3F));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
}

void loop() {
  byte keys = module.getButtons();
  if (keys != oldkeys)
  {
    if (keys & 128)
      Serial.println("eight");
    if (keys & 64)
      Serial.println("seven");
    if (keys & 32)
    {
        Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
        // device address is specified in datasheet
        Wire.write(byte(0x01));            // sends instruction byte
        Wire.write(byte(0x80));             // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting
    }
    if (keys & 16)
    {
        Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
        // device address is specified in datasheet
        Wire.write(byte(0x01));            // sends instruction byte
        Wire.write(byte(0x40));             // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting
    }
    if (keys & 8)
      Serial.write(8);
      //Serial.println("four");
    if (keys & 4)
      Serial.write(13);
      //Serial.println("three");
    if (keys & 2)
    {
      Serial.write(0x1b);
      Serial.write(0x5b);
      Serial.write('B');
      //Serial.write(40);
      //Serial.println("two");
    }
    if (keys & 1)
    {
      Serial.write(0x1b);
      Serial.write(0x5b);
      Serial.write('A');
      //Serial.write(38);
      //Serial.println("one");
    }
    //Serial.println(String(keys));
  }
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    String i = Serial.readStringUntil('\n');
    //int x = Serial.parseInt();
    //if (x!=0)
      module.setDisplayToString(i);
    //Serial.println(i);
  }
  oldkeys = keys;
}
