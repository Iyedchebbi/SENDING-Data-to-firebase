#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h> // LCD I2C library

#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 1024.0

#define PIN_LM35 A0 // pin connected to LM35 temperature sensor
const int RS = 9, EN = 8, D4 = 5, D5 = 4, D6 = 3, D7 = 2;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight(); // open the backlight
}

void loop() {
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in Celsius
  float tempC = milliVolt / 100;
  lcd.clear();
  lcd.setCursor(0, 0); // start to print at the first row
  lcd.print(tempC);    // print the temperature in Celsius
  lcd.print("°C");
  // print the temperature to Serial Monitor
  Serial.print("Temperature: ");    // envoyer l'étiquette de température via Serial
  Serial.print(tempC);
  Serial.println("°C  ");
  delay(500);
}
