#include <ESP8266WiFi.h> //This is the library for Nodemcu wifi module.
#include <Wire.h> //This library allows you to communicate with I2C devices, a feature that is present on all Arduino boards. The I2C board is connected to the LCD screen.
#include <LiquidCrystal_I2C.h> //A library for I2C LCD displays. 
LiquidCrystal_I2C lcd(0x27,20,4); //LiquidCrystal_I2C lcd(i2c_addr,cols,rows)
#include <DHT11.h> //Library for DHT 11 sensor.
DHT11 dht11(2); //Defining the DHT pin connection.
#define DHTPIN D4
//Defining the DHT pin.
#define DHTTYPE DHT11 
//Defining the DHT type (DHT11, 22, etc.) 
void setup() //The setup contains code that has to run only once.
{
  lcd.backlight(); //switching on the LCS backlight.
  lcd.init(); //Initialising the LCS display.
  Serial.begin(9600); //Serial. begin(9600); passes the value 9600 to the speed parameter. 
}
void loop() ////The loop contains code that has to run on a loop.
{
  delay(2000); //Delay of 2000ms before starting. It is jsut a simple safekeeping procedure before running the loop code. It is not necessary.
  lcd.clear(); //It clear out the lcd screen.
  lcd.setCursor(0,0); //It sets the cursor position. lcd.setCursor(0,0) means that the cursor is at the start of the screen.
  lcd.print("Humidity="); //print function of the lcd.
  lcd.print((float)dht11.readHumidity()); // This reads the current humidity nearby the DHT 11 sensor. The (float) command means that the values will contain decimals.
  lcd.print("%"); //print function of the lcd.
  lcd.setCursor(0,1); //It sets the cursor position. lcd.setCursor(0,1) means that the cursor is that position.
  lcd.print("Temp="); //print function of the lcd.
  lcd.print((float)dht11.readTemperature()); // This reads the current temperature nearby the DHT 11 sensor. The (float) command means that the values will contain decimals.
  lcd.print("*C"); //print function of the lcd.
  delay(2000); //Delay of 2000ms before starting.
  lcd.clear(); //It clear out the lcd screen.
}
