#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include <DHT11.h>
DHT11 dht11(2);
#define DHTPIN D4
#define DHTTYPE DHT11
void setup()
{
  lcd.backlight();
  lcd.init();
  Serial.begin(9600);
}
void loop() 
{
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity=");
  lcd.print((float)dht11.readHumidity());
  lcd.print("%");
  lcd.setCursor(0,1);\
  lcd.print("Temp=");
  lcd.print((float)dht11.readTemperature());
  lcd.print("*C");
  delay(2000);
  lcd.clear();
}
