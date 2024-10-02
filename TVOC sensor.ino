#include <Wire.h> //The library that allows us communicate with I2C devies.
#include <LiquidCrystal_I2C.h> //Library for LCD displays that is connected to I2C chipset. 
#define AGS02MA_ADDRESS 0x1A 
//Defining the TVOC sensor. The TVOC sensor is an AGS02MA. It is a MEMS TVOC gas sensor that uses the I2C communication protocol and has an I2C address of 0x1A in 7-bit mode.
#define LCD_ADDRESS 0x27 
// The address here implies that none of the adress pins (A0, A1 and A2) are soldered. There are in total 8 different I2C addresses that can be created - 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20.
//When all theree address pins are unsoltered, then the default address is 0x27. 
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
void setup() //Code that will run once. 
{
  Serial.begin(9600); //The bitrate set to baud rate (9600 bitrate).
  Wire.begin(); //Start the communication with I2C chipset.
  lcd.begin(16, 2); //Starting the LCD screen.
  lcd.print("TVOC Sensor Init"); //Print command for LCD.
  delay(2000); //Delay of 2000 ms.
  lcd.clear(); //Command to clear the LCD screen.
}
void loop() {
  Wire.beginTransmission(AGS02MA_ADDRESS); //Begin transmission to the TVOC sensor. This initiates communication with AGS02MA TVOC sensor via the I2C bus. Wire.beginTransmission(address) prepares to send data to the device with the specified I2C address.
  Wire.write(0x01); //This write function sends commands 0x01, which in command list of AGS02MA is for zero-point calibration.
  Wire.endTransmission(); //End transmission to the TVOC sensor.
  Wire.requestFrom(AGS02MA_ADDRESS, 2); //requesting data from the I2C device. The "AGS02MA_ADDRESS" here refers to the TVOC sensor. It requests two bytes of data from the sensor. Wire.requestFrom(address, quantity) asks the sensor to send a specified number of bytes (quantity) back to the Arduino.
  if (Wire.available() == 2) { //If the vaialble number of bytes are 2 then proceed.
    int highByte = Wire.read(); // The I2C is reading single byte. highByte: Stores the first byte received, representing the high 8 bits of the measurement.
    int lowByte = Wire.read(); // The I2C is reading single byte. lowByte: Stores the second byte, representing the low 8 bits.
    int tvoc = (highByte << 8) | lowByte; // This command merges the two 8-bit bytes into a single 16-bit integer value representing the TVOC measurement. highByte << 8 shifts the bits of highByte 8 positions to the left, effectively moving it from the lower byte to the higher byte in a 16-bit integer. | Combines the shifted highByte with lowByte to form the full 16-bit value.
    Serial.print("TVOC: "); //print command. These commands are for serial monitor and do not display on LCD screen.
    Serial.print(tvoc); //print command. Prints the tvoc value. These commands are for serial monitor and do not display on LCD screen.
    Serial.println(" ppb"); //print command. These commands are for serial monitor and do not display on LCD screen. 
    lcd.setCursor(0, 0); //Sets LCD cursor to the begining.
    lcd.print("TVOC: "); //Print command for LCD.
    lcd.print(tvoc); //Print command for LCD. Prints the TVOC value.
    lcd.print(" ppb"); //Print command for LCD.
    } else { //This is for when the sensor does not provide the 2 bytes of data. 
    Serial.println("Error reading sensor"); //print command. Prints the tvoc value. These commands are for serial monitor and do not display on LCD screen.
    lcd.setCursor(0, 0); //Sets LCD cursor to the begining.
    lcd.print("Sensor Error"); //Print command for LCD.
    }
  delay(1000);
}
