#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include <Wire.h>

//Modbus Registers Offsets (0-9999)
const int SENSOR_HREG = 100;

//ModbusIP object
ModbusIP mb;

long ts;

void setup() {
    Wire.begin();        // join i2c bus (address optional for master)
    
  Wire.beginTransmission(0x1a); // transmit to device #8
  Wire.write(0x03);        // sends five bytes
  Wire.write(0x00);              // sends one byte
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

    ts = millis();

  Wire.beginTransmission(0x1a); // transmit to device #8
  Wire.write(0x01);        // sends five bytes
  Wire.write(0xFF);              // sends one byte
  Wire.endTransmission();    // stop transmitting
}

uint16_t readvalue(uint8_t addr)
{
  Wire.beginTransmission(0x09); // transmit to device #4
  Wire.write(addr);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(0x09, 2);    // request 6 bytes from slave device #2
  return Wire.read()|Wire.read()<<8; // receive a byte as character
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
}
