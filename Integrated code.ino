#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>
LiquidCrystal_I2C lcd(0x27,20,4);
#include <DHT11.h>
DHT11 dht11(2);
#define DHTPIN D4
#define DHTTYPE DHT11
#define AGS02MA_ADDRESS 0x1A
54
#define MQ7_PIN A0
#define MQ7_BOARD "ESP-8266"
#define MQ7_TYPE "MQ-7"
#define VOLTAGE_RESOLUTION 3.3
#define ADC_BIT_RESOLUTION 10
void setup() {
Serial.begin(9600);
Wire.begin();
lcd.init();
lcd.backlight();
dht.begin();
}
void loop() {
float temperature = dht.readTemperature();
float humidity = dht.readHumidity();
float mq135_reading = readMQ135(); // Function to read MQ-135 data
float mq7_reading = readMQ7(); // Function to read MQ-7 data
float dust_reading = readGP2Y1010AU0F(); // Function to read 
GP2Y1010AU0F data
float tvoc_reading = readAGS02MA(); // Function to read AGS02MA data
displayData(temperature, humidity, mq135_reading, mq7_reading, 
dust_reading, tvoc_reading);
delay(2000); // Update every 2 seconds
}
float readMQ135() {
// Read MQ-135 data and return value
}
float readMQ7() {
// Read MQ-7 data and return value
}
float readGP2Y1010AU0F() {
// Read GP2Y1010AU0F data and return value
}
float readAGS02MA() {
// Read AGS02MA data and return value
}
55
void displayData(float temperature, float humidity, float mq135, 
float mq7, float dust, float tvoc) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp: ");
lcd.print(temperature);
lcd.print(" C Humidity: ");
lcd.print(humidity);
lcd.print("%");
lcd.setCursor(0, 1);
lcd.print("MQ135: ");
lcd.print(mq135);
lcd.print(" MQ7: ");
lcd.print(mq7);
lcd.setCursor(0, 2);
lcd.print("Dust: ");
lcd.print(dust);
lcd.setCursor(0, 3);
lcd.print("TVOC: ");
lcd.print(tvoc);
}
