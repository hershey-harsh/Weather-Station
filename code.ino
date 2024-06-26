#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

int pinDHT11 = 5;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = dht11.read(&temperature, &humidity, NULL);
  if (err != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(2000);
    return;
  }

  // Convert temperature to Fahrenheit
  float temperatureF = temperature * 1.8 + 32;

  // Display temperature and humidity on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Climates: ");
  lcd.print(temperatureF, 1); // Display with 1 decimal place
  lcd.print((char)223); // Degree symbol
  lcd.print("F");

  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(2000); // Delay for 2 seconds before the next reading
}
