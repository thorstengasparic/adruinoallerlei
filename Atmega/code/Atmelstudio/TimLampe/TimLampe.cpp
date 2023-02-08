/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <EEPROM.h>                                  //Include the EEPROM.h library so we can store information onto the EEPROM
/*End of auto generated code by Atmel studio */
#include "Bounce2.h"

void dimmerFunction();
void stroboFunction();
void FlashLED();
void IncDecFunction(int doIncrement);
bool readEprom();
void writeEprom();

#define ledPin  11

#define doIncrement 1
#define doDecrement -1

#define MODE_MINMODE    1 //!!! adjust, if modes change
#define MODE_DIMMER     1
#define MODE_FLASHLEN   2 
#define MODE_PULSLEN	3
#define MODE_MAXMODE    3 //!!! adjust, if modes change

#define SWITCHPIN01		7
#define SWITCHPIN02		8
#define KEYPRESSED		LOW
#define KEYUP			HIGH
#define debounceIntervall 5 /* interval in ms */
Bounce switch01 = Bounce();
Bounce switch02 = Bounce();

#define toggleModeHoldTIntervall 1000 /* in millis */
unsigned long sw1MillisDown;
unsigned long sw2MillisDown;

#define inDecUpdateIntervall 50
#define State_Idle 0
#define State_IncDec 1
#define State_WaitReleaseButton 2
byte currenState ;

unsigned long incDevTimer ;
int currentMode;
int dimmerValue;
int _dimmerLastValue = 0;

int pulselength;
int flashLength;
unsigned long _stropeTimer;
unsigned long _stropeMilliCounter;



void setup() 
{
  //Serial.begin(115200);

  currentMode = MODE_DIMMER;
  dimmerValue = 128;
  flashLength = 50;
  pulselength = 100;

  if (!readEprom())
	writeEprom();
	
  pinMode(SWITCHPIN01, INPUT_PULLUP);
  switch01.attach(SWITCHPIN01);
  switch01.interval(debounceIntervall); 
  
  pinMode(SWITCHPIN02, INPUT_PULLUP);
  switch02.attach(SWITCHPIN02);
  switch02.interval(debounceIntervall);
  
  sw1MillisDown =0;
  sw2MillisDown =0;
 
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, LOW);
  
  //pinMode(ledPin, OUTPUT);   
  currenState = State_Idle ;

}

long curhighValue =0;
long curlowValue =0;

// the loop function runs over and over again forever
void loop()  
{
	switch01.update();
	switch02.update();

	if( switch01.fell()) 
	{
		sw1MillisDown = millis();
	}
	if( switch02.fell()) 
	{	
		sw2MillisDown = millis();
	}
	
	bool key01IsDown = !switch01.read();
	bool key02IsDown = !switch02.read();
	bool bothKeysAreDown = key01IsDown && key02IsDown;
	bool onlyOneKeysIsDown = (key01IsDown || key02IsDown) && (!bothKeysAreDown);
	bool noKeysIsDown	 = (!key01IsDown) && (!key02IsDown);

	switch(currenState)
	{
		case State_Idle:
			if (bothKeysAreDown)
			{
				if ((millis()-sw1MillisDown > toggleModeHoldTIntervall) && (millis()-sw2MillisDown > toggleModeHoldTIntervall))
				{
					FlashLED();
					currenState = State_WaitReleaseButton;
					currentMode ++;
					if (currentMode > MODE_MAXMODE)
					currentMode = MODE_MINMODE;
					_stropeTimer = millis();
					_stropeMilliCounter = pulselength;
					_dimmerLastValue = 0;
					return;
				}
			}
			if (switch01.rose()) 
			{
				IncDecFunction(doIncrement);
				return;
			}
			if (switch02.rose()) 
			{
				IncDecFunction(doDecrement);
				return;
			}
			if (onlyOneKeysIsDown)
			{
				if (((millis()-sw1MillisDown > toggleModeHoldTIntervall && key01IsDown) || (millis()-sw2MillisDown > toggleModeHoldTIntervall && key02IsDown)))
				{
					incDevTimer = millis();
					currenState = State_IncDec;
					return;
				}
			}

			break;

		case State_IncDec:
				if (noKeysIsDown)
				{
					currenState = State_Idle;
					return;
				}

				if ((millis() - incDevTimer) > inDecUpdateIntervall )
				{
					if (key01IsDown) IncDecFunction(doIncrement);
					if (key02IsDown) IncDecFunction(doDecrement);
					incDevTimer = millis();
					return;
				}
				break;

		case State_WaitReleaseButton:
				if ((switch01.read() == KEYUP)&& (switch01.read() == KEYUP) )
				{
					//FlashLED();
					currenState = State_Idle;
					return;
				}
				break;
	}

	switch(currentMode)
	{
		case MODE_DIMMER:
			dimmerFunction();
			break;
		case MODE_PULSLEN:
		case MODE_FLASHLEN:
			stroboFunction();
			break;
		default:
		currentMode = MODE_DIMMER;
	}

	//Serial.print(flashLength);
	//Serial.print("\t");
	//Serial.print(pulselength);
	//Serial.print("\t");
	//Serial.println(dimmerValue);
}


void dimmerFunction()
{
	if ( _dimmerLastValue!= dimmerValue)
	{
		analogWrite(ledPin, dimmerValue);
		_dimmerLastValue = dimmerValue;
	}
}

void stroboFunction()
{
	if (_stropeMilliCounter == 0)
		_stropeMilliCounter = pulselength;
	
	if (_stropeMilliCounter <= flashLength)
		analogWrite(ledPin, dimmerValue);
	else
		analogWrite(ledPin, 0);

	if ( millis() -_stropeTimer >= 1)
	{
		_stropeMilliCounter--;
		_stropeTimer = millis();
	}
}

void IncDecFunction(int incDecSign)
{
	int dimmerValueDelta = 1;
	switch(currentMode)
	{
		case MODE_DIMMER:
			
			if (dimmerValue > 50) dimmerValueDelta = 10;

			dimmerValue += dimmerValueDelta*incDecSign;
			if (dimmerValue  < 1) dimmerValue = 1;
			if (dimmerValue > 255) dimmerValue = 255;
			break;

		case MODE_PULSLEN:
			pulselength += 10*incDecSign;
			if (pulselength < 10) pulselength = 10;
			if (pulselength > 5000) pulselength = 5000;
			break;

		case MODE_FLASHLEN:
			flashLength += 1*incDecSign;
			if (flashLength > pulselength) pulselength = flashLength +200;
			if (flashLength  < 2) flashLength = 2;
			
		break;
	}

	writeEprom();

}

#define flashLevel 2
#define flashLevelDelay 200
void FlashLED()
{
	for (int i=0; i<5; i++)
	{
		analogWrite(ledPin, flashLevel);
		delay(flashLevelDelay);
		analogWrite(ledPin, 0);
		delay(flashLevelDelay);
	}
}

void writeEprom()
{
  EEPROM.write(0, 23); //Magic = 23.01.2018
  EEPROM.write(1, 01);
  EEPROM.write(2, 18);

  byte value0 = dimmerValue & 0xff;
  byte value1 = (dimmerValue >> 8) & 0xff;
  EEPROM.write(3, value0);
  EEPROM.write(4, value1);
  
  value0 = pulselength & 0xff;
  value1 = (pulselength >> 8) & 0xff;
  EEPROM.write(5, value0);
  EEPROM.write(6, value1);

  value0 = flashLength & 0xff;
  value1 = (flashLength >> 8) & 0xff;
  EEPROM.write(7, value0);
  EEPROM.write(8, value1);
}

bool readEprom()
{
	if (EEPROM.read(0) != 23) return false;
	if (EEPROM.read(1) != 01) return false;
	if (EEPROM.read(2) != 18) return false;

	byte value0 = EEPROM.read(3);
	byte value1 = EEPROM.read(4);
	dimmerValue = (value1<<8) +value0;

	value0 = EEPROM.read(5);
	value1 = EEPROM.read(6);
	pulselength = (value1<<8) +value0;

	value0 = EEPROM.read(7);
	value1 = EEPROM.read(8);
	flashLength = (value1<<8) +value0;
}

