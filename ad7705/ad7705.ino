#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  SPI.transfer("\xFF\xFF\xFF\xFF\xFF", 5);
  SPI.transfer("\x20\x0C\x10\x40", 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  SPI.transfer(0x38);
  Serial.println(SPI.transfer16(0xFFFF),HEX);
}

