#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include <Wire.h>

//Modbus Registers Offsets (0-9999)
const int SENSOR_HREG = 100;

//ModbusIP object
ModbusIP mb;

long ts;

byte state = LOW;

void blink() {
  state = digitalRead(2);
  if (state)
    tone(9, 880, 100);
  else
    tone(9, 659, 100);

     if (state)
   {
      Wire.beginTransmission(0x18);
      Wire.write("\x01\x40");
      Wire.endTransmission();
   }
   else
   {
      Wire.beginTransmission(0x18);
      Wire.write("\x01\x80");
      Wire.endTransmission();
   }
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
    Wire.begin();        // join i2c bus (address optional for master)
    
  Wire.beginTransmission(0x1a); // transmit to device #8
  Wire.write(0x03);        // sends five bytes
  Wire.write(0x00);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  
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
    mb.addCoil(123);

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
    mb.addIsts(123);*/
    
    //ts = millis();

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
      Wire.beginTransmission(0x18);
      Wire.write("\x01\x40");
      Wire.endTransmission();
   }
   else
   {
      Wire.beginTransmission(0x18);
      Wire.write("\x01\x80");
      Wire.endTransmission();
   }
}
