
#include <LiquidCrystal_I2C.h> // library for used lcd1602 with i2c module
#include <Wire.h> 
#include <OneWire.h>
#include <DallasTemperature.h> //libraries for conections with sensor Dallas
#include <DS3231.h> // library for RTC

#define ONE_WIRE_BUS 2 // pin for connect sensor Dallas

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature TEMP (&oneWire); //create an object to work with the library DallasTemperature
DS3231 Clock; //create an object to work with the library DS3231

bool h12;
bool PM;
bool Century = false; // Required parameters for DS3231 library

int min;
LiquidCrystal_I2C lcd (0x27, 16, 2); // display address and parameters

byte cel[8]   = {B11100,B10100,B11100,B00000,B00000,B00000,B00000,B00000,}; //Celsius degree symbol

void setup() {
  TEMP.begin(); //initialization Dallas sensor
  TEMP.setResolution(9);
  lcd.begin(); //initialization display
  lcd.clear(); //clear display
  lcd.createChar(1, cel); //create symbol celsius degree
  lcd.home(); //return the cursor to the beginning of the display
  lcd.print("Out:"); 
  lcd.print(round(TEMP.getTempCByIndex(0))); //round value to integer
  lcd.print("\1"); //print celsius degree symbol
  lcd.setCursor(10,0); //move the cursor to a given position
  lcd.print("In:");
  lcd.setCursor(15,0);
  lcd.print("\1");
  min = 99;
  }

void loop() {
 if (Clock.getMinute() != min){     // condition for updating the screen
  lcd.setCursor(1,1);
  lcd.print(Clock.getHour(h12,PM)); //get and print hour
  lcd.print(":");
  lcd.print(Clock.getMinute()); //get and print minute
  lcd.setCursor(10,1);
  lcd.print(Clock.getDate()); //get and print Day
  lcd.print("/");
  lcd.print(Clock.getMonth(Century)); // get and print Month
  lcd.setCursor(4,0);
  TEMP.requestTemperaturesByIndex(0); // request for data from the sensor 
  lcd.print(round(TEMP.getTempCByIndex(0))); // get, round and print the temperature
  lcd.setCursor(13,0);
  lcd.print(int(Clock.getTemperature()));
   min = Clock.getMinute();
   }
}
