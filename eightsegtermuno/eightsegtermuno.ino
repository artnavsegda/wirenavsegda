#include <TM1638.h>
TM1638 module(7, 8, 6);
byte oldkeys = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
}

void loop() {
  byte keys = module.getButtons();
  if (keys != oldkeys)
  {
    if (keys & 128)
      Serial.println("eight");
    if (keys & 64)
      Serial.println("seven");
    if (keys & 32)
      Serial.println("six");
    if (keys & 16)
      Serial.println("five");
    if (keys & 8)
      Serial.write(8);
      //Serial.println("four");
    if (keys & 4)
      Serial.write(13);
      //Serial.println("three");
    if (keys & 2)
    {
      Serial.write(0x1b);
      Serial.write(0x5b);
      Serial.write('B');
      //Serial.write(40);
      //Serial.println("two");
    }
    if (keys & 1)
    {
      Serial.write(0x1b);
      Serial.write(0x5b);
      Serial.write('A');
      //Serial.write(38);
      //Serial.println("one");
    }
    //Serial.println(String(keys));
  }
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    //String i = Serial.readStringUntil('\n');
    int x = Serial.parseInt();
    if (x!=0)
      module.setDisplayToDecNumber(x, 0xF0);
    //Serial.println(i);
  }
  oldkeys = keys;
}
