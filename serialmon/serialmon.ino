void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent(){
  while (Serial.available())
  {
    Serial.print(millis());
    Serial.print(":RX0:");
    Serial.println(Serial.read(),HEX);
  }
}

void serialEvent1(){
  while (Serial1.available())
  {
    Serial.print(millis());
    Serial.print(":RX1:");
    Serial.println(Serial1.read(),HEX);
  }
}

void serialEvent2(){
  while (Serial2.available())
  {
    Serial.print(millis());
    Serial.print(":RX2:");
    Serial.println(Serial2.read(),HEX);
  }
}

void serialEvent3(){
  while (Serial3.available())
  {
    Serial.print(millis());
    Serial.print(":RX3:");
    Serial.println(Serial3.read(),HEX);
  }
}
