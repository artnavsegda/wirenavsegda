#include <TM1638.h>
#include <Wire.h>
#include <EtherCard.h>

TM1638 module(6, 5, 7);
byte oldkeys = 0;

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,1,203 };

byte Ethernet::buffer[500];
BufferFiller bfill;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  module.setDisplayToHexNumber(0x1234ABCD, 0xF0);

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  ether.staticSetup(myip);
  
  delay(1000);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
  // device address is specified in datasheet
  Wire.write(byte(0x03));            // sends instruction byte
  Wire.write(byte(0x3F));             // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting
}

String i;

static word homePage() {
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<meta http-equiv='refresh' content='1'/>"
    "<title>RBBB server</title>" 
    "<h1>$D$D:$D$D:$D$D analog - $D string $S</h1>"),
      h/10, h%10, m/10, m%10, s/10, s%10, analogRead(A0), i.c_str());
  return bfill.position();
}

void loop() {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  if (pos)  // check if valid tcp data is received
    ether.httpServerReply(homePage()); // send web page data
  
  byte keys = module.getButtons();
  if (keys != oldkeys)
  {
    if (keys & 128)
      Serial.println("eight");
    if (keys & 64)
      Serial.println("seven");
    if (keys & 32)
    {
        Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
        // device address is specified in datasheet
        Wire.write(byte(0x01));            // sends instruction byte
        Wire.write(byte(0x80));             // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting
    }
    if (keys & 16)
    {
        Wire.beginTransmission(0x18); // transmit to device #44 (0x2c)
        // device address is specified in datasheet
        Wire.write(byte(0x01));            // sends instruction byte
        Wire.write(byte(0x40));             // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting
    }
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
    i = Serial.readStringUntil('\n');
    //int x = Serial.parseInt();
    //if (x!=0)
      module.setDisplayToString(i);
    //Serial.println(i);
  }
  oldkeys = keys;
}
