#define CLOCK_PIN 4
#define DATA_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  TCCR2A = 0x33;
  TCCR2B = 0x09;
  OCR2A = 0x06;
  OCR2B = 0x03;
}

void loop() {
  while (digitalRead(DATA_PIN) == HIGH); // wait for data ready
  uint32_t value = shiftIn(DATA_PIN, CLOCK_PIN, MSBFIRST);
  value <<= 8;
  value |= shiftIn(DATA_PIN, CLOCK_PIN, MSBFIRST);
  value <<= 8;
  value |= shiftIn(DATA_PIN, CLOCK_PIN, MSBFIRST);
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW); // 25th pulse to keep DATA high till next data ready

  Serial.println(value);
}
