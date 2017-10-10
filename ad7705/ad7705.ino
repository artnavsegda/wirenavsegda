#include <SPI.h>

void starttimer()
{
  TCCR2A = 0x33;
  TCCR2B = 0x09;
  OCR2A = 0x02;
  OCR2B = 0x01;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.begin(9600);
  SPI.begin();
  starttimer();
  digitalWrite(10, LOW);
  SPI.transfer("\xFF\xFF\xFF\xFF\xFF", 5);
  SPI.transfer("\x20\x0C\x10\x40", 4);
  digitalWrite(10, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(9) == LOW)
  {
    digitalWrite(10, LOW);
    SPI.transfer(0x38);
    Serial.println(SPI.transfer16(0xFFFF),HEX);
    digitalWrite(10, HIGH);
  }
}

