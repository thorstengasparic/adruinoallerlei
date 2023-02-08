#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"

#define I2C_ADDR 0x27  // Add your address here.
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
int i = 0;

void setup()
{
  lcd.begin (16,2); //  our LCD is a 16x2, change for your LCD if needed

  // LCD Backlight ON
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // go home on LCD
 
}

void loop()
{
 lcd.setCursor (0,0); // go to start of 1nd line
 //lcd.print("Current Distance:");
 //lcd.setCursor (0,1); // go to start of 4th line
 //lcd.print("Ping: ");
 i++;
 lcd.print(i);
 //lcd.print(" ");

 //delay(5);
}
