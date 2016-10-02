#include <Wire.h>

struct MyObject {
  char zero[4];
  char one[6];
  char two[26];
  char three[13];
};

struct MyObject e = {
  "123",
  "12345",
  "abcdefghijklmnopqrst",
  "0123456789ab"
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

int i;
int x;
float y;
char z[5];

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
        Wire.readBytes(e.two, 20);
        Serial.println(e.two);
      break;
      case 3:
        Wire.readBytes(e.three, 13);
        Serial.println(e.three);
      break;
      case 5:
        i = Wire.read();
        Serial.println(i);
      break;
      case 6:
        Wire.readBytes((byte *)&x,sizeof(x));
        Serial.println(x);
       break;
      case 7:
        Wire.readBytes((byte *)&y,sizeof(y));
        Serial.println(y);
      break;
      case 8:
        Wire.readBytes(z,sizeof(z));
        Serial.println(z);
      default:
      break;
    }
}

int xsend = 420;
float ysend = 4.20;
char zstring[] = "hello";

void requestEvent() {
  switch (memaddr) {
    case 0:
      Wire.write(e.zero,4);
    break;
    case 1:
      Wire.write(e.one,6);
    break;
    case 2:
      Wire.write(e.two,20);
    break;
    case 3:
      Wire.write(e.three,13);
    break;
    case 5:
      Wire.write(42);
    break;
    case 6:
      Wire.write((byte *)&xsend,sizeof(xsend));
    break;
    case 7:
      Wire.write((byte *)&ysend,sizeof(ysend));
    break;
    case 8:
      Wire.write(zstring,sizeof(zstring));
    break;
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
