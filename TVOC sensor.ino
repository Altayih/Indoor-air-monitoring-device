#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define AGS02MA_ADDRESS 0x1A
#define LCD_ADDRESS 0x27
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
void setup() {
  Serial.begin(9600);\
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("TVOC Sensor Init");
  delay(2000);
  lcd.clear();
}
void loop() {
  Wire.beginTransmission(AGS02MA_ADDRESS);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(AGS02MA_ADDRESS, 2);
  if (Wire.available() == 2) {
    int highByte = Wire.read();
    int lowByte = Wire.read();
    int tvoc = (highByte << 8) | lowByte;
    Serial.print("TVOC: ");
    Serial.print(tvoc);
    Serial.println(" ppb");
    lcd.setCursor(0, 0);
    lcd.print("TVOC: ");
    lcd.print(tvoc);
    lcd.print(" ppb");
    } else {\
    Serial.println("Error reading sensor");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    }
  delay(1000);
}
