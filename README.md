# Tennis Live Scores - Hardware Client Documentation

## 1. Introduction

The Tennis Live Scores Hardware Client is a crucial component of a live scoring system designed to address the frustration experienced by players waiting for their matches during tennis tournaments. This documentation provides comprehensive information about the hardware client, which captures score data from mechanical scoreboards using sensors and transmits it wirelessly to the mobile application.

## 2. System Overview

The hardware client is one of three components in the Tennis Live Scores system:

1. **Hardware Client (this component)**: Detects and transmits scoreboard data
2. **Mobile Application**: Connects to the hardware client and/or allows manual score entry
3. **Web Application**: Displays live scores and provides tournament management

The hardware client attaches to existing mechanical scoreboards found on tennis courts and wirelessly transmits score changes to the system.

## 3. Hardware Components

### 3.1 Component List

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Mega2560 | 1 | Main microcontroller |
| Hall Effect Analog Sensors | 14 | Score detection (7 per side) |
| HM-10 Bluetooth LE Module | 1 | Wireless communication |
| Battery (see Section 6) | 1 | Power source |

## 4. Installation and Setup

### 4.1 Hardware Assembly

1. **Sensor Positioning**:
   - Mount 7 Hall effect sensors for Player A's score (set counter and 6 game counters)
   - Mount 7 Hall effect sensors for Player B's score (set counter and 6 game counters)
   - Sensor placement must align with the magnetic elements in the mechanical scoreboard
   - Secure sensors with non-conductive adhesive or mounting brackets

2. **Arduino and Bluetooth Module**:
   - Mount the Arduino Mega2560 in the weather-resistant enclosure
   - Connect the HM-10 Bluetooth module to TX1/RX1 pins (18/19)
   - Secure all components to prevent movement during operation

3. **Power Connection**:
   - Connect the selected battery (see Section 6) to the Arduino power input
   - Ensure proper polarity and voltage regulation

### 4.2 Software Setup

1. Download the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the required libraries:
   - SoftwareSerial (included with Arduino IDE)
3. Load the provided code to the Arduino:

4. Upload the code to the Arduino Mega2560 using the Arduino IDE

## 5. Technical Implementation

### 5.1 Sensor Configuration

The hardware client uses Hall effect sensors to detect the position of magnetic elements in the mechanical scoreboard. Each sensor is configured to detect a specific score value:

- **Set Counter**: Indicates which player has won a set (1 sensor per player)
- **Game Counters**: Indicates the games won in the current set (6 sensors per player)

The sensors are connected to digital input pins on the Arduino Mega2560 with internal pull-up resistors enabled. When a magnet is detected (indicating a score), the pin reads LOW.

### 5.2 Bluetooth Connection

The HM-10 Bluetooth Low Energy module provides wireless communication with the mobile application. The module connects to the Arduino's hardware serial port (TX1/RX1) and operates at 9600 baud rate.

#### 5.2.1 Bluetooth Technical Specifications

- **Protocol**: Bluetooth Low Energy (BLE) 4.0
- **Module**: HM-10
- **Operating Voltage**: 3.3V
- **Operating Current**: ~8.5mA (connected)
- **Transmission Power**: -23dBm to 3dBm
- **Range**: Approximately 10m in typical conditions

#### 5.2.2 GATT Service Specification

The hardware client implements a custom GATT service for transmitting score data:

| Service | UUID |
|---------|------|
| Tennis Score Service | 0000FFE0-0000-1000-8000-00805F9B34FB |

| Characteristic | UUID | Properties | Description |
|----------------|------|------------|-------------|
| Score Data | 0000FFE1-0000-1000-8000-00805F9B34FB | Read, Notify | Current score data |
| Battery Level | 0000FFE2-0000-1000-8000-00805F9B34FB | Read, Notify | Battery percentage |

### 5.3 Data Structure

The score data is transmitted as a comma-separated string with the following format:

```text
Set,<SetA><SetB>,Games,<Game1A><Game1B>,<Game2A><Game2B>,<Game3A><Game3B>,<Game4A><Game4B>,<Game5A><Game5B>,<Game6A><Game6B>
```

Where:

- `<SetA>` and `<SetB>` are either 0 or 1 (LOW or HIGH) representing the set counter state
- `<GameNA>` and `<GameNB>` are either 0 or 1 (LOW or HIGH) representing the game counter state

Example:

```text
Set,10,Games,01,11,00,10,00,00
```

This represents:

- Player A has won a set (1)
- Player B has not won a set (0)
- Game counters show: A=0,B=1; A=1,B=1; A=0,B=0; A=1,B=0; A=0,B=0; A=0,B=0

## 6. Power Consumption & Battery

### 6.1 Power Consumption Analysis

Based on detailed measurements, the hardware client consumes approximately 0.286 watt-hours (Wh) per hour of operation.

| Component | Power Consumption (Wh) |
|-----------|------------------------|
| Arduino Mega2560 | 0.125 |
| Hall Effect Sensors (14) | 0.160 |
| HM-10 Bluetooth Module | 0.001 |
| **Total System** | **0.286** |

### 6.2 Battery Options

#### 6.2.1 One-Week Operation (~48 Wh)

**Rechargeable Options:**

- 10,000mAh Lithium Polymer battery at 3.7V (37Wh)
- 12,000mAh LiPo battery at 3.7V (44.4Wh)
- 4 × 18650 Lithium-ion cells in a 2S2P configuration (29.6Wh)

**Disposable Battery Options:**

- 6 × D cell alkaline batteries in a 3S2P configuration (54-81Wh)
- 12 × AA alkaline batteries in a 4S3P configuration (36-54Wh)

#### 6.2.2 One-Month Operation (~206 Wh)

**Rechargeable Options:**

- 12V, 15Ah SLA (Sealed Lead Acid) battery (180Wh)
- 12 × 18650 Li-ion battery pack in a 4S3P configuration (177.6Wh)
- 40,000mAh power bank at 3.7V (148Wh)

**Disposable Battery Option:**

- 8 × D cell alkaline batteries in a 4S2P configuration (144-216Wh)

## 7. Testing and Troubleshooting

### 7.1 Sensor Validation

To verify proper sensor placement and operation:

1. **Serial Monitor Debug:**
   - Connect the Arduino to a computer via USB
   - Open Serial Monitor in Arduino IDE (9600 baud)
   - Observe the output as you change scoreboard values
   - Verify each sensor responds correctly

2. **LED Indicators:**
   - The code can be modified to use onboard LEDs for visual feedback
   - LED on = sensor detecting magnet
   - LED off = no magnetic field detected

### 7.2 Common Issues and Solutions

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| No Bluetooth connection | Power issue, incorrect pairing | Check battery, reset module, re-pair with mobile app |
| Inaccurate score reading | Sensor misalignment, interference | Adjust sensor position, check for nearby magnets |
| Intermittent connection | Bluetooth interference | Change location, reduce obstacles between devices |
| System unresponsive | Software crash, power issue | Reset system, check battery levels |

## 8. Future Improvements

### 8.1 Power Optimization

- Implement deep sleep mode for Arduino between readings
- Use power-efficient sensors
- Optimize Bluetooth transmission frequency

### 8.2 Enhanced Features

- Add ambient light sensor for auto-brightness of optional display
- Implement accelerometer for tamper detection
- Develop machine learning for optical recognition of non-magnetic scoreboards

### 8.3 Integration Opportunities

- Direct communication with tournament management software
- Weather station integration for play condition monitoring
- Court occupancy tracking for facility management

## 9. License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
