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
  Serial.println("ADC unit test");
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

int i;
int x;
float y;
char z[5];
uint16_t adc_scan_results[16];

void receiveEvent(int howMany) {
  if (Wire.available())
    memaddr = Wire.read();
  if (Wire.available())
    switch (memaddr) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        Wire.readBytes((byte *)&adc_scan_results[memaddr], 2);
        Serial.print("ADC");
        Serial.print(memaddr);
        Serial.print(" ");
        Serial.println(adc_scan_results[memaddr]);
      break;
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
