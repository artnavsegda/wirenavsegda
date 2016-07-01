void pca9557init(uint8_t i2c)
{
  Wire.beginTransmission(i2c);
  Wire.write(byte(0x02));
  Wire.write(0x00);
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
