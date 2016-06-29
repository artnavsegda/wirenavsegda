#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include <Wire.h>

#define U3_IGNIT 1
#define SERVO_1_LEFT_OUT 7
#define SERVO_1_RIGHT_OUT 6
#define SERVO_1_LEFT_IN 5
#define SERVO_1_RIGHT_IN 4

ModbusIP mb;
uint8_t configuration[256];
uint8_t value[256];

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

void setup() {
  pinMode(2, INPUT_PULLUP);
  Wire.begin();        // join i2c bus (address optional for master)
  pca9557init(0x18);
  pca9557pinMode(0x18, SERVO_1_LEFT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_1_RIGHT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_1_LEFT_IN, INPUT);
  pca9557pinMode(0x18, SERVO_1_RIGHT_IN, INPUT);
  pca9557init(0x19);
  pca9557init(0x1a);
  pca9557pinMode(0x1a, U3_IGNIT, OUTPUT);
  
  Wire.beginTransmission(0x18); // transmit to device #8
  Wire.write(0x03);        // sends five bytes
  Wire.write(0x3f);              // sends one byte
  Wire.endTransmission();    // stop transmitting
    
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    // The IP address for the shield
    byte ip[] = { 192, 168, 1, 120 };
    //Config Modbus IP
    mb.config(mac, ip);

    // Add SENSOR_IREG register - Use addIreg() for analog Inputs
    mb.addHreg(100);
    mb.addHreg(101);
    mb.addHreg(102);
    mb.addHreg(103);
    mb.addHreg(104);
    mb.addHreg(105);
    mb.addHreg(106);
    mb.addHreg(107);
    mb.addHreg(108);
    mb.addHreg(109);

    mb.addCoil(100);
    /*mb.addCoil(101);
    mb.addCoil(102);
    mb.addCoil(103);
    mb.addCoil(104);
    mb.addCoil(105);
    mb.addCoil(106);
    mb.addCoil(107);
    mb.addCoil(108);
    mb.addCoil(109);
    mb.addCoil(110);
    mb.addCoil(111);
    mb.addCoil(112);
    mb.addCoil(113);
    mb.addCoil(114);
    mb.addCoil(115);
    mb.addCoil(116);
    mb.addCoil(117);
    mb.addCoil(118);
    mb.addCoil(119);
    mb.addCoil(120);
    mb.addCoil(121);
    mb.addCoil(122);
    mb.addCoil(123);*/

    mb.addIsts(100);
    mb.addIsts(101);
    mb.addIsts(102);
    mb.addIsts(103);
    mb.addIsts(104);
    mb.addIsts(105);
    mb.addIsts(106);
    mb.addIsts(107);
    mb.addIsts(108);
    mb.addIsts(109);
    mb.addIsts(110);
    mb.addIsts(111);
    mb.addIsts(112);
    mb.addIsts(113);
    mb.addIsts(114);
    mb.addIsts(115);
    mb.addIsts(116);
    mb.addIsts(117);
    mb.addIsts(118);
    mb.addIsts(119);
    mb.addIsts(120);
    mb.addIsts(121);
    mb.addIsts(122);
    mb.addIsts(123);
  //for (int i = 100; i <= 123; i++)
  //{
  //  mb.addIsts(i);
  //}
    

  Wire.beginTransmission(0x1a); // transmit to device #8
  Wire.write(0x01);        // sends five bytes
  Wire.write(0xFF);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  tone(9, 784, 100);
}

uint16_t readvalue(uint8_t addr)
{
  Wire.beginTransmission(0x09); // transmit to device #4
  Wire.write(addr);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(0x09, 2);    // request 6 bytes from slave device #2
  return Wire.read()|Wire.read()<<8; // receive a byte as character
}

int readbit(uint8_t addr, uint8_t bit)
{
  Wire.beginTransmission(addr); // transmit to device #4
  Wire.write(0x00);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(addr, 1);    // request 6 bytes from slave device #2
  if (Wire.read() & _BV(bit)) return HIGH;
  return LOW;
}

void loop() {
   //Call once inside loop() - all magic here
  mb.task();

   //Read each two seconds
   //if (millis() > ts + 2000) {
     //  ts = millis();
       //Setting raw value (0-1024)
  mb.Hreg(100, readvalue(0x00));
  mb.Hreg(101, readvalue(0x01));
  mb.Hreg(102, readvalue(0x02));
  mb.Hreg(103, readvalue(0x03));
  mb.Hreg(104, readvalue(0x04));
  mb.Hreg(105, readvalue(0x05));
  mb.Hreg(106, readvalue(0x06));
  mb.Hreg(107, readvalue(0x07));
  mb.Hreg(108, readvalue(0x08));
  mb.Hreg(109, readvalue(0x09));

  mb.Ists(100, pca9557digitalRead(0x18, 0));
  mb.Ists(101, pca9557digitalRead(0x18, 1));
  mb.Ists(102, pca9557digitalRead(0x18, 2));
  mb.Ists(103, pca9557digitalRead(0x18, 3));
  mb.Ists(104, pca9557digitalRead(0x18, 4));
  mb.Ists(105, pca9557digitalRead(0x18, 5));
  mb.Ists(106, pca9557digitalRead(0x18, 6));
  mb.Ists(107, pca9557digitalRead(0x18, 7));

  mb.Ists(108, pca9557digitalRead(0x19, 0));
  mb.Ists(109, pca9557digitalRead(0x19, 1));
  mb.Ists(110, pca9557digitalRead(0x19, 2));
  mb.Ists(111, pca9557digitalRead(0x19, 3));
  mb.Ists(112, pca9557digitalRead(0x19, 4));
  mb.Ists(113, pca9557digitalRead(0x19, 5));
  mb.Ists(114, pca9557digitalRead(0x19, 6));
  mb.Ists(115, pca9557digitalRead(0x19, 7));

  mb.Ists(116, pca9557digitalRead(0x1a, 0));
  mb.Ists(117, pca9557digitalRead(0x1a, 1));
  mb.Ists(118, pca9557digitalRead(0x1a, 2));
  mb.Ists(119, pca9557digitalRead(0x1a, 3));
  mb.Ists(120, pca9557digitalRead(0x1a, 4));
  mb.Ists(121, pca9557digitalRead(0x1a, 5));
  mb.Ists(122, pca9557digitalRead(0x1a, 6));
  mb.Ists(123, pca9557digitalRead(0x1a, 7));

  //int x;
  //for (int i = 0, i <= 7, i++)
  //{
  //  mb.Ists(x++, pca9557digitalRead(0x18,i);
  //}

       //mb.Coil(99, digitalRead(13));
       /*mb.Coil(100, readbit(0x18,0));
       mb.Coil(101, readbit(0x18,1));
       mb.Coil(102, readbit(0x18,2));
       mb.Coil(103, readbit(0x18,3));
       mb.Coil(104, readbit(0x18,4));
       mb.Coil(105, readbit(0x18,5));
       mb.Coil(106, readbit(0x18,6));
       mb.Coil(107, readbit(0x18,7));*/
  if (!digitalRead(2) || mb.Coil(100))
       //if (mb.Coil(100))
  {
    pca9557digitalWrite(0x18, SERVO_1_LEFT_OUT, HIGH);
    pca9557digitalWrite(0x18, SERVO_1_RIGHT_OUT, LOW);
    //Wire.beginTransmission(0x18);
    //Wire.write("\x01\x40");
    //Wire.endTransmission();
  }
  else
  {
    pca9557digitalWrite(0x18, SERVO_1_RIGHT_OUT, HIGH);
    pca9557digitalWrite(0x18, SERVO_1_LEFT_OUT, LOW);
    //Wire.beginTransmission(0x18);
    //Wire.write("\x01\x80");
    //Wire.endTransmission();
  }
}
