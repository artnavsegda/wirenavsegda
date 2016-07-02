#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>
#include <Wire.h>
#include "logic.h"

ModbusIP mb;
uint8_t configuration[256];
uint8_t value[256];

void setup() {
  pinMode(2, INPUT_PULLUP);
  Wire.begin();        // join i2c bus (address optional for master)
  pca9557init(0x18);
  pca9557pinMode(0x18, SERVO_1_LEFT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_1_RIGHT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_1_LEFT_IN, INPUT);
  pca9557pinMode(0x18, SERVO_1_RIGHT_IN, INPUT);
  pca9557pinMode(0x18, SERVO_2_LEFT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_2_RIGHT_OUT, OUTPUT);
  pca9557pinMode(0x18, SERVO_2_LEFT_IN, INPUT);
  pca9557init(0x19);
  pca9557pinMode(0x19, SERVO_2_RIGHT_IN, INPUT);
  pca9557pinMode(0x19, SERVO_3_LEFT_OUT, OUTPUT);
  pca9557pinMode(0x19, SERVO_3_RIGHT_OUT, OUTPUT);
  pca9557pinMode(0x19, SERVO_3_LEFT_IN, INPUT);
  pca9557pinMode(0x19, SERVO_3_RIGHT_IN, INPUT);
  pca9557pinMode(0x19, SERVO_4_LEFT_OUT, OUTPUT);
  pca9557pinMode(0x19, SERVO_4_RIGHT_OUT, OUTPUT);
  pca9557init(0x1a);
  pca9557pinMode(0x1a, SERVO_4_LEFT_IN, INPUT);
  pca9557pinMode(0x1a, SERVO_4_RIGHT_IN, INPUT);
  pca9557pinMode(0x1a, U3_IGNIT, OUTPUT);
      
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
  mb.addHreg(103); // temp
  mb.addHreg(104);
  mb.addHreg(105);
  mb.addHreg(106);
  mb.addHreg(107);
  mb.addHreg(108);
  mb.addHreg(109);
  mb.addHreg(110);
  mb.addHreg(111);

  mb.addHreg(200);
  mb.addHreg(201);
  mb.addHreg(202);
  mb.addHreg(203); 
  mb.addHreg(204);
  mb.addHreg(205);
  mb.addHreg(206); // temp in v
  mb.addHreg(207); // temp in v
  mb.addHreg(208);
  mb.addHreg(209);
  mb.addHreg(210);
  mb.addHreg(211);
  mb.addHreg(212);
  mb.addHreg(213);
  mb.addHreg(214);
  mb.addHreg(215);
  mb.addHreg(216); // temp in c
  mb.addHreg(217); // temp in c

  mb.addCoil(100);

  /*mb.addIsts(100);
  mb.addIsts(101);
  mb.addIsts(102);
  mb.addIsts(103);
  mb.addIsts(104); // SERVO_1_RIGHT_IN
  mb.addIsts(105); // SERVO_1_LEFT_IN
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

  mb.addCoil(100);
  mb.addCoil(101);
  mb.addCoil(102);
  mb.addCoil(103);
  mb.addCoil(104); // SERVO_1_RIGHT_IN
  mb.addCoil(105); // SERVO_1_LEFT_IN
  mb.addCoil(106); // SERVO_1_RIGHT_OUT
  mb.addCoil(107); // SERVO_1_LEFT_OUT
  mb.addCoil(108);
  mb.addCoil(109);
  mb.addCoil(110);
  mb.addCoil(111);
  mb.addCoil(112);
  mb.addCoil(113);
  mb.addCoil(114);
  mb.addCoil(115);
  mb.addCoil(116);
  mb.addCoil(117, HIGH); //U3_IGNIT
  mb.addCoil(118);
  mb.addCoil(119);
  mb.addCoil(120);
  mb.addCoil(121);
  mb.addCoil(122);
  mb.addCoil(123);*/
  
  //for (int i = 100; i <= 123; i++)
  //{
  //  mb.addIsts(i);
  //}

  pca9557digitalWrite(0x1a, U3_IGNIT, HIGH);

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

void modbus_set_float_abcd(float f, int location)
{
    uint32_t i;

    memcpy(&i, &f, sizeof(uint32_t));
    mb.Hreg(location+1, (uint16_t)(i >> 16));
    //location++;
    mb.Hreg(location, (uint16_t)i);
}

const float popugai = 0.49487e-3;
const int adczero = 178;

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

  modbus_set_float_abcd((readvalue(0x00)-adczero)*popugai,200);
  modbus_set_float_abcd((readvalue(0x01)-adczero)*popugai,202);
  modbus_set_float_abcd((readvalue(0x02)-adczero)*popugai,204);
  modbus_set_float_abcd((readvalue(0x03)-adczero)*popugai,206);
  modbus_set_float_abcd((readvalue(0x04)-adczero)*popugai,208);
  modbus_set_float_abcd((readvalue(0x05)-adczero)*popugai,210);
  modbus_set_float_abcd((readvalue(0x06)-adczero)*popugai,212);
  modbus_set_float_abcd((readvalue(0x07)-adczero)*popugai,214);
  modbus_set_float_abcd((((readvalue(0x03)-adczero)*popugai)-0.5)*100,216);

  /*mb.Ists(100, pca9557digitalRead(0x18, 0));
  mb.Ists(101, pca9557digitalRead(0x18, 1));
  mb.Ists(102, pca9557digitalRead(0x18, 2));
  mb.Ists(103, pca9557digitalRead(0x18, 3));
  mb.Ists(104, pca9557digitalRead(0x18, 4)); // SERVO_1_RIGHT_IN
  mb.Ists(105, pca9557digitalRead(0x18, 5)); // SERVO_1_LEFT_IN
  mb.Ists(106, pca9557digitalRead(0x18, 6)); // SERVO_1_RIGHT_OUT
  mb.Ists(107, pca9557digitalRead(0x18, 7)); // SERVO_1_LEFT_OUT

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
  mb.Ists(123, pca9557digitalRead(0x1a, 7));*/

  //int x;
  //for (int i = 0, i <= 7, i++)
  //{
  //  mb.Ists(x++, pca9557digitalRead(0x18,i);
  //}

  //mb.Coil(99, digitalRead(13));
  /*pca9557digitalWrite(0x18, 0, mb.Coil(100));
  pca9557digitalWrite(0x18, 1, mb.Coil(101));
  pca9557digitalWrite(0x18, 2, mb.Coil(102));
  pca9557digitalWrite(0x18, 3, mb.Coil(103));
  pca9557digitalWrite(0x18, 4, mb.Coil(104));
  pca9557digitalWrite(0x18, 5, mb.Coil(105));
  pca9557digitalWrite(0x18, 6, mb.Coil(106));
  pca9557digitalWrite(0x18, 7, mb.Coil(107));

  pca9557digitalWrite(0x19, 0, mb.Coil(108));
  pca9557digitalWrite(0x19, 1, mb.Coil(109));
  pca9557digitalWrite(0x19, 2, mb.Coil(110));
  pca9557digitalWrite(0x19, 3, mb.Coil(111));
  pca9557digitalWrite(0x19, 4, mb.Coil(112));
  pca9557digitalWrite(0x19, 5, mb.Coil(113));
  pca9557digitalWrite(0x19, 6, mb.Coil(114));
  pca9557digitalWrite(0x19, 7, mb.Coil(115));

  pca9557digitalWrite(0x1a, 0, mb.Coil(116));
  pca9557digitalWrite(0x1a, 1, mb.Coil(117));
  pca9557digitalWrite(0x1a, 2, mb.Coil(118));
  pca9557digitalWrite(0x1a, 3, mb.Coil(119));
  pca9557digitalWrite(0x1a, 4, mb.Coil(120));
  pca9557digitalWrite(0x1a, 5, mb.Coil(121));
  pca9557digitalWrite(0x1a, 6, mb.Coil(122));
  pca9557digitalWrite(0x1a, 7, mb.Coil(123));*/
  
  if (!digitalRead(2) || mb.Coil(100))
  {
    pca9557digitalWrite(0x18, SERVO_1_LEFT_OUT, LOW);
    pca9557digitalWrite(0x18, SERVO_1_RIGHT_OUT, HIGH);
  }
  else
  {
    pca9557digitalWrite(0x18, SERVO_1_RIGHT_OUT, LOW);
    pca9557digitalWrite(0x18, SERVO_1_LEFT_OUT, HIGH);
  }
}
