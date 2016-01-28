#include <TM1638.h>

TM1638 module(9, 8, 10);

void setup() {
  // put your setup code here, to run once:
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
