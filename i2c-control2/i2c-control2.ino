#include <Wire.h>

uint8_t configuration[256];

void pca9557pinMode(uint8_t i2c, uint8_t pin, uint8_t mode)
{
  Wire.beginTransmission(i2c);
  Wire.write(byte(0x03));
  if (mode == OUTPUT)
  {
    configuration[i2c] &= ~bit(pin);
  }
  else
  {
    configuration[i2c] |= bit(pin);
  }
  Wire.write(configuration[i2c]);
  Wire.endTransmission();
}

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  //Wire.beginTransmission(0x1a); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  //Wire.write(byte(0x03));            // sends instruction byte
  //Wire.write(byte(0x00));             // sends potentiometer value byte
  //Wire.endTransmission();     // stop transmitting
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pca9557pinMode(0x1a, 0, OUTPUT);
  pca9557pinMode(0x1a, 1, OUTPUT);
  pca9557pinMode(0x1a, 2, OUTPUT);
  pca9557pinMode(0x1a, 3, OUTPUT);
  pca9557pinMode(0x1a, 4, OUTPUT);
  pca9557pinMode(0x1a, 5, OUTPUT);
  pca9557pinMode(0x1a, 6, OUTPUT);
  pca9557pinMode(0x1a, 7, OUTPUT);
}

uint8_t value[256];

void pca9557digitalWrite(uint8_t i2c, uint8_t pin, uint8_t val)
{
  Wire.beginTransmission(i2c);
  Wire.write(byte(0x01));
  if (val == LOW)
  {
    value[i2c] &= ~bit(pin);
  }
  else
  {
    value[i2c] |= bit(pin);
  }
  Wire.write(value[i2c]);
  Wire.endTransmission();
}

int pca9557digitalRead(uint8_t i2c, uint8_t pin)
{
  Wire.beginTransmission(i2c);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(i2c,1);
  if (Wire.read() & bit(pin)) return HIGH;
  return LOW; 
}

void loop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  pca9557digitalWrite(0x1a,0,LOW);
  pca9557digitalWrite(0x1a,1,LOW);
  pca9557digitalWrite(0x1a,2,LOW);
  pca9557digitalWrite(0x1a,3,LOW);
  pca9557digitalWrite(0x1a,4,LOW);
  pca9557digitalWrite(0x1a,5,LOW);
  pca9557digitalWrite(0x1a,6,LOW);
  pca9557digitalWrite(0x1a,7,LOW);
  delay(1000);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  pca9557digitalWrite(0x1a,0,HIGH);
  pca9557digitalWrite(0x1a,1,HIGH);
  pca9557digitalWrite(0x1a,2,HIGH);
  pca9557digitalWrite(0x1a,3,HIGH);
  pca9557digitalWrite(0x1a,4,HIGH);
  pca9557digitalWrite(0x1a,5,HIGH);
  pca9557digitalWrite(0x1a,6,HIGH);
  pca9557digitalWrite(0x1a,7,HIGH);
  delay(1000);
}

