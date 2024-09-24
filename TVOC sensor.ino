#include <Wire.h> //The library that allows us communicate with I2C devies.
#include <LiquidCrystal_I2C.h> //Library for LCD displays that is connected to I2C chipset. 
#define AGS02MA_ADDRESS 0x1A 
//Defining the TVOC sensor. The TVOC sensor is an AGS02MA. It is a MEMS TVOC gas sensor that uses the I2C communication protocol and has an I2C address of 0x1A in 7-bit mode.
#define LCD_ADDRESS 0x27 
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
void setup() //Code that will run once. 
{
  Serial.begin(9600); //The bitrate set to baud rate (9600 bitrate).
  Wire.begin(); //Start the communication with I2C chipset.
  lcd.begin(16, 2); //Starting the designationted LCD screen.
  lcd.print("TVOC Sensor Init"); //Print command for LCD.
  delay(2000); //Delay of 2000 ms.
  lcd.clear(); //Command to clear the LCD screen.
}
void loop() {
  Wire.beginTransmission(AGS02MA_ADDRESS); //Begin transmission to the TVOC sensor.
  Wire.write(0x01); //Write function of wire.h library that allows us to write data over the i2C bus.
  Wire.endTransmission(); //End transmission to the TVOC sensor.
  Wire.requestFrom(AGS02MA_ADDRESS, 2); //requesting data from the I2C device. The "AGS02MA_ADDRESS" here refers to the TVOC sensor.
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
