/*
 * AL_Common.cpp
 *
 * Created: 20.04.2017 21:20:54
 *  Author: gat
 */ 
#include <Arduino.h>
#include <Wire.h>                                    //Include the Wire.h library so we can communicate with the gyro.
#include <EEPROM.h>                                  //Include the EEPROM.h library so we can store information onto the EEPROM
#include <AL-Common.h>

#include "AL-Gyro.h"                                  //Include the EEPROM.h library so we can store information onto the EEPROM

 void InitCommon(void)
 {
	Wire.begin();                                                                         //Start the wire library as master
	TWBR = 12;                                                                            //Set the I2C clock speed to 400kHz.

	pinMode(LED_STATUS_PIN, OUTPUT);
	digitalWrite(LED_STATUS_PIN,LOW);                                     //Turn on the warning led
	//
	gyro_address = 0x68; //eeprom_data[32];                                                       //Store the gyro address in the variable.

 }
 
 void BlinkSignal(int statusNo, bool doreturn)
{

	int maxSeq = 5;
	int seg = statusNo / maxSeq;
	int offs = statusNo % maxSeq;
	while (true)
	{
		for(int i = 0; i<seg;i++)
		{
			digitalWrite(LED_STATUS_PIN,HIGH);                                     //Turn on the warning led
			delay(1500);
			digitalWrite(LED_STATUS_PIN,LOW);                                     //Turn on the warning led
			delay(500);
		}
		for(int i = 0; i<offs;i++)
		{
			digitalWrite(LED_STATUS_PIN,HIGH);                                     //Turn on the warning led
			delay(100);
			digitalWrite(LED_STATUS_PIN,LOW);                                     //Turn on the warning led
			delay(500);
		}
		if (doreturn) return;
		delay(1000);
	}

 }
 