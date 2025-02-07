#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  delay(1000);
  Serial.println("Bluetooth communication ready...");
}

void loop() {
  // Forward data from Bluetooth to Serial Monitor
  if (BTSerial.available()) {
    char data = BTSerial.read();
    // Print data to serial monitor
    Serial.write(data);
  }

  // Forward data from Serial Monitor to Bluetooth
  if (Serial.available()) {
    char data = Serial.read();
    // Send data to bluetooth
    BTSerial.write(data);
  }
}
