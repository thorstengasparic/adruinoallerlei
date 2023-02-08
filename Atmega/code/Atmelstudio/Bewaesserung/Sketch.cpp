/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Wire.h>
#include <EEPROM.h>                                  //Include the EEPROM.h library so we can store information onto the EEPROM
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include "I2CSensor_std.h"
// Pin 5 6 I2s
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

int sensorPowerPin1  = A1;
int sensorPin1    = A0;
int relaisPin    = A2;
int buttonPin1    = 4;
int buttonPin2    = 5;

const int ledPin =  13;
int buttonState = 0;


#define LOOP_DELAY (unsigned long)100   // ms
unsigned long MEASURE_INTERVALL = 60; // Minutes
unsigned int MEASURE_MINVALUE = 500;        // 0..1023
unsigned int WATER_ON_TIME = 0;          // Seconds

int readsensorValue(int sensorPowerPin, int sensorPin,bool saveHistory);
int DoMeasurement(bool saveHistory);
void writeEprom();
bool readEprom();
void prinfInfo();
void historyInfo();
void waterON( int seconds);
int _sensorValue0 = 1023;
int _sensorValue1 = 1023;
#define historylen 24*2
byte curhistory ;
int lastValues[historylen][2];
int wateronTime[historylen];
I2CSensor sensor(0x71);

void setup()
{
	
	Serial.begin(9600);
	
	pinMode(sensorPowerPin1 , OUTPUT);

	delay(100);
	Serial.println("Temperatur Messprogramm");
	delay(100);
	lcd.begin (16,2); //  our LCD is a 16x2, change for your LCD if needed
	delay(300);
	lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);// LCD Backlight ON
	lcd.setBacklight(HIGH);
	lcd.home (); // go home on LCD
	lcd.clear();
	lcd.print("Init...");
	for (int i = 0; i< historylen; i++)
	{
		lastValues[i][0] = 0;
		lastValues[i][1] = 0;
		wateronTime[i] =0;
	}
	pinMode(sensorPowerPin1, OUTPUT);
	pinMode(relaisPin, OUTPUT);

	digitalWrite(sensorPowerPin1, LOW);
	digitalWrite(relaisPin, HIGH);

	if (!readEprom())
	{
		writeEprom();
		lcd.print("Cannot read EEPROM");
		Serial.println("Cannot read EEPROM");
		delay(1000);
	}
	else
	{
		lcd.print("EEPROM OK");
		Serial.println("EEPROM OK");
	}
	delay(5000);
	curhistory =0;
	DoMeasurement(true);
	curhistory++;
	lastValues[curhistory][0] = _sensorValue0;
	lastValues[curhistory][1] = _sensorValue1;
	
	prinfInfo();
}


String readString ;
String valString ;
unsigned long loopcount = 0;
#define PRINTDELAY delay(50);
void loop()
{
	while (Serial.available()) {
		delay(5);  //delay to allow buffer to fill
		if (Serial.available() >0) {
			char c = Serial.read();  //gets one byte from serial buffer
			readString += c; //makes the string readString
		}
	}
	
	if (readString.length() >0) {
		Serial.println(readString); //see what was received

		if (readString.substring(0,1) == "?")
		{
			Serial.println("Commands:");
			PRINTDELAY
			Serial.println("info : print current setting");
			PRINTDELAY
			Serial.println("history : print last values");
			PRINTDELAY
			Serial.println("intervall=<minutes> : set measurement intervall in minutes");
			PRINTDELAY
			Serial.println("minvalue=<value> : minimal moits value");
			PRINTDELAY
			Serial.println("wateron=<seconds> : manuel water on time");
			PRINTDELAY
			Serial.println("watertime=<seconds> : automatic water on time");
			PRINTDELAY
			Serial.println("measure : do manuel measurement");
			readString = "";
		}
		
		if (readString.substring(0,10) == "intervall=")
		{
			MEASURE_INTERVALL = readString.substring(10).toInt();
			loopcount =0;
			writeEprom();
			prinfInfo();
			readString = "";
		}
		if (readString.substring(0,9) == "minvalue=")
		{
			MEASURE_MINVALUE = readString.substring(9).toInt();
			writeEprom();
			prinfInfo();
			readString = "";
		}
		if (readString.substring(0,8) == "wateron=")
		{
			int secon = readString.substring(8).toInt();
			waterON( secon);
			readString = "";
		}
		if (readString.substring(0,10) == "watertime=")
		{
			WATER_ON_TIME = readString.substring(10).toInt();
			writeEprom();
			prinfInfo();
			readString = "";
		}
		if (readString.substring(0,4) == "info")
		{
			prinfInfo();
			readString = "";
		}
		if (readString.substring(0,7) == "history")
		{
			historyInfo();
			readString = "";
		}
		
		if (readString.substring(0,7) == "measure")
		{
			DoMeasurement(true);
			Serial.print("Last values: ");
			Serial.print(_sensorValue0);
			Serial.print(", ");
			Serial.println(_sensorValue1);
			readString = "";
		}

		if (readString.length() >0) {
			Serial.println("ERROR: Unkown command. Press ? for help.");
			readString = readString.substring(0,4);
			Serial.print("'");
			Serial.print(readString);
			Serial.println("'");
			readString = "";
		}
		
	}
	buttonState = digitalRead(buttonPin1);
	if (buttonState == HIGH) {
		digitalWrite(relaisPin, LOW);
	}
	else {
		digitalWrite(relaisPin, HIGH);
	}

	bool doMeasure = false;
	buttonState = digitalRead(buttonPin2);
	if (buttonState == HIGH) {
		DoMeasurement(true);
	}
	
	if ((unsigned long)(loopcount * LOOP_DELAY) > (MEASURE_INTERVALL * 60 * 1000))
	{
		DoMeasurement(true);
		wateronTime[curhistory] =0;
		if (_sensorValue0 > MEASURE_MINVALUE)
		{
			waterON( WATER_ON_TIME);
			wateronTime[curhistory] = WATER_ON_TIME;
		}
		
		curhistory++;
		if (curhistory >= historylen)
		curhistory=0;
		loopcount =0;
	}

	if (((loopcount * LOOP_DELAY) % 1000) == 0)
	{
		lcd.clear();
		lcd.home (); // go home on LCD

		lcd.setCursor (0,0); // go to start of 1nd line
		lcd.print(_sensorValue0);
		lcd.print(", ");
		lcd.print(_sensorValue1);

		lcd.setCursor (0,1); // go to start of 1nd line
		unsigned long timeLeft =  (MEASURE_INTERVALL * 60)-((loopcount * LOOP_DELAY) / 1000) ;// - (loopcount * LOOP_DELAY) / 1000;
		lcd.print(timeLeft / 60);
		lcd.print(":");
		lcd.print(timeLeft % 60);
		lcd.print("  ");
		lcd.print(sensor.getTemperature() / (float)10);
		lcd.print("C");
	}
	loopcount ++;
	delay(LOOP_DELAY);
}


int DoMeasurement(bool saveHistory)
{
	lcd.clear();
	lcd.home (); // go home on LCD
	lcd.print("Messung...");
	digitalWrite(ledPin, HIGH);
	byte sensorValue = readsensorValue(sensorPowerPin1, sensorPin1, saveHistory);
	delay(1000);
	digitalWrite(ledPin, LOW);
	return sensorValue;
}

int readsensorValue(int sensorPowerPin, int sensorPin, bool saveHistory)
{
	digitalWrite(sensorPowerPin, HIGH);
	_sensorValue0 = analogRead(sensorPin);
	if (saveHistory) lastValues[curhistory][0] = _sensorValue0;
	digitalWrite(sensorPowerPin, LOW);

	_sensorValue1 = sensor.getCapacitance();
	if (saveHistory) lastValues[curhistory][1] = _sensorValue1;

	
	return _sensorValue0;
}

void waterON( int seconds)
{
	lcd.clear();
	lcd.home (); // go home on LCD
	lcd.print("WATER on...");
	digitalWrite(relaisPin, LOW);
	delay(seconds * 1000);
	digitalWrite(relaisPin, HIGH);
}

void prinfInfo()
{
	Serial.print("intervall: ");
	Serial.println(MEASURE_INTERVALL);
	PRINTDELAY
	Serial.print("minvalue: ");
	Serial.println(MEASURE_MINVALUE);
	PRINTDELAY
	Serial.print("watertime: ");
	Serial.println(WATER_ON_TIME);
	PRINTDELAY
	Serial.print("Calibrate low: ");
	Serial.println(sensor.getCalibrateLow(), DEC);
	PRINTDELAY
	Serial.print("Calibrate High: ");
	Serial.println(sensor.getCalibrateHigh(), DEC);
	PRINTDELAY
	Serial.print("Capacitance: ");
	Serial.println(sensor.getCapacitance()); //read capacitance register
	PRINTDELAY
	Serial.print("Procent data: ");
	Serial.println(sensor.getCapacitanceProz()); //read capacitance register
	PRINTDELAY
	Serial.print("Temperature: ");
	Serial.print(sensor.getTemperature() / (float)10); //temperature register
	Serial.println("C");
	PRINTDELAY
	Serial.print("Time left: ");
	unsigned long timeLeft =  (MEASURE_INTERVALL * 60)-((loopcount * LOOP_DELAY) / 1000) ;// - (loopcount * LOOP_DELAY) / 1000;
	Serial.print(timeLeft / 60);
	Serial.print(":");
	Serial.println(timeLeft % 60);
	PRINTDELAY
	Serial.print("Last value: ");
	Serial.print(_sensorValue0);
	Serial.print(", ");
	Serial.println(_sensorValue1);
}

void historyInfo()
{
	for (int i = 0; i< historylen; i++)
	{
		if (i==curhistory)
		Serial.print("->");
		Serial.print(lastValues[i][0]);
		Serial.print("\t");
		Serial.print(lastValues[i][1]);
		Serial.print("\t");
		Serial.println(wateronTime[i]);
		PRINTDELAY
	}
}

void writeEprom()
{
	EEPROM.write(0, 'G');
	EEPROM.write(1, 'A');
	EEPROM.write(2, 'T');
	EEPROM.write(3, '0');
	EEPROM.write(4, '0');
	
	byte value0 = MEASURE_INTERVALL & 0xff;
	byte value1 = 0xff;
	EEPROM.write(5, value0);
	
	value0 = MEASURE_MINVALUE & 0xff;
	value1 = (MEASURE_MINVALUE >> 8) & 0xff;
	EEPROM.write(6, value0);
	EEPROM.write(7, value1);
	
	value0 = MEASURE_MINVALUE & 0xff;
	value1 = (MEASURE_MINVALUE >> 8) & 0xff;
	EEPROM.write(6, value0);
	EEPROM.write(7, value1);

	value0 = WATER_ON_TIME & 0xff;
	EEPROM.write(8, value0);
}

bool readEprom()
{
	if (EEPROM.read(0) != 'G') return false;
	if (EEPROM.read(1) != 'A') return false;
	if (EEPROM.read(2) != 'T') return false;
	if (EEPROM.read(3) != '0') return false;
	if (EEPROM.read(4) != '0') return false;

	byte value0 = EEPROM.read(5);
	byte value1 = 0;
	MEASURE_INTERVALL = value0 & 0xffffffff;
	
	value0 = EEPROM.read(6);
	value1 = EEPROM.read(7);
	MEASURE_MINVALUE = (value1<<8) +value0;

	value0 = EEPROM.read(8);
	value1 = 0;
	WATER_ON_TIME = value0;
	return true;
}
