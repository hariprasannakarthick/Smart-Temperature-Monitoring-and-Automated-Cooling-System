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