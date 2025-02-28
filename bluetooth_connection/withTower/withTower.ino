const int numberOfSensorsPerSide = 7;
const int pinsSideA[] = { 8, 7, 6, 5, 4, 3, 2 };   // [Set, Game1-6]
const int pinsSideB[] = { 34, 32, 30, 28, 26, 24, 22 }; // [Set, Game1-6]

void setup() {
  // Initialize all pins as INPUT_PULLUP
  for (int i = 0; i < numberOfSensorsPerSide; i++) {
    pinMode(pinsSideA[i], INPUT_PULLUP);
    pinMode(pinsSideB[i], INPUT_PULLUP);
  }
  Serial1.begin(9600);  // Hardware serial for HM-10 (pins 18/TX1, 19/RX1)
}

void loop() {
  // Read set status
  int setA = digitalRead(pinsSideA[0]);
  int setB = digitalRead(pinsSideB[0]);
  
  // Build combined data string
  String data = String("Set,") + setA + setB + ",Games";
  
  // Append game results (SideA-SideB pairs)
  for (int i = 1; i < numberOfSensorsPerSide; i++) {
    int a = digitalRead(pinsSideA[i]);
    int b = digitalRead(pinsSideB[i]);
    data += "," + String(a) + String(b);
  }

  // Send data over Bluetooth
  Serial1.println(data);
  delay(2000);
}