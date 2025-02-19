#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX, TX

const int hallAnalogPin = A0;
int hallAnalog;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(1000);
  Serial.println("Bluetooth communication ready...");
}


void loop() {
  if (BTSerial.available()) {
  hallAnalog = analogRead(hallAnalogPin);
  Serial.print("Analog: ");
  Serial.println(hallAnalog);

  if((hallAnalog>550) || (hallAnalog<500)) {
    Serial.print("Magnet nearby!!");
    BTSerial.write("Magnet nearby!!");
    delay(500);
  }
  }
}