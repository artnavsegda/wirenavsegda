#include <Wire.h>

struct MyObject {
  char zero[4];
  char one[6];
  char two[26];
  char three[13];
};

struct MyObject e = {
  "1234",
  "123456",
  "abcdefghijklmnopqrstuwxyz",
  "0123456789abc"
};

int memaddr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("I2C unit test");
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

char i;
int x;

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case 0:
        Wire.readBytes(e.zero, 4);
        Serial.println(e.zero);
      break;
      case 1:
        Wire.readBytes(e.one, 6);
        Serial.println(e.one);
      break;
      case 2:
        Wire.readBytes(e.two, 26);
        Serial.println(e.two);
      break;
      case 4:
        Wire.readBytes(e.three, 13);
        Serial.println(e.three);
      break;
      case 5:
        i = Wire.read();
        Serial.println(i);
      case 6:
        Wire.readBytes((byte *)&x,2);
        Serial.println(x);
      default:
      break;
    }
}

void requestEvent() {
  switch (memaddr) {
    case 0:
      Wire.write(e.zero,4);
    break;
    case 1:
      Wire.write(e.one,6);
    break;
    case 2:
      Wire.write(e.two,26);
    break;
    case 3:
      Wire.write(e.three,13);
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
