# Smart Temperature Monitoring and Automated Cooling System

## Overview
This project implements a real-time temperature monitoring and automated cooling system using the LM35 sensor and Arduino. The system continuously measures temperature and activates a cooling mechanism when a predefined threshold is exceeded.

## Features
- Real-time temperature sensing using LM35
- Analog-to-digital conversion and calibration
- Threshold-based control system
- Automatic fan/relay activation
- Serial monitoring for debugging and visualization

## Components Used
- Arduino (Uno/Nano)
- LM35 Temperature Sensor
- Relay Module / DC Fan
- Resistors and connecting wires
- Power supply

## Working Principle
The LM35 sensor outputs a voltage proportional to temperature (10mV/°C).  
The Arduino reads this analog signal, converts it into temperature values, and compares it with a predefined threshold.  
If the temperature exceeds the limit, the system activates a cooling device (fan/relay). Otherwise, it remains off.

## Circuit Diagram
<img width="1536" height="1024" alt="ChatGPT Image Mar 19, 2026, 04_11_03 PM" src="https://github.com/user-attachments/assets/048936cd-49c3-409c-8471-755b391576b4" />


## Code
```cpp
#include <LiquidCrystal.h>

// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int lm35Pin = A0;
const int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(lm35Pin);

  // Correct LM35 Celsius formula
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;  // 10mV per °C

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1); // 1 decimal place
  lcd.print(" C   ");

  lcd.setCursor(0, 1);

  if (temperature > 39.0) {
    lcd.print("Status: HIGH   ");
    digitalWrite(buzzerPin, HIGH);
  }
  else if (temperature >= 33.0 && temperature <= 39.0) {
    lcd.print("Status: NORMAL ");
    digitalWrite(buzzerPin, LOW);
  }
  else {
    lcd.print("Status: LOW    ");
    digitalWrite(buzzerPin, LOW);
  }

  delay(3000);
}
