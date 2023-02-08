/*
 * Ds18S20Min.cpp
 *
 * Created: 02.04.2017 15:58:39
 *  Author: gat
 */ 

 //Beginning of Auto generated function prototypes by Atmel Studio
#include <OneWire.h>
#include "Ds18S20Min.h"

Ds18S20Temperature::Ds18S20Temperature(OneWire* ow)
{
	onewire = ow;
}

void Ds18S20Temperature::Begin(void)
{
	readAdresses() ;
}
 
 void Ds18S20Temperature::writeTimeToScratchpad(byte* address, int delaycnt)
 {
	 //reset the bus
	 onewire->reset();
	 //select our sensor
	 onewire->select(address);
	 //CONVERT T function call (44h) which puts the temperature into the scratchpad
	 onewire->write(0x44,1);
	 //sleep a second for the write to take place
	 delay(delaycnt);
 }
 
 void Ds18S20Temperature::readTimeFromScratchpad(byte* address, byte* data)
 {
	 //reset the bus
	 onewire->reset();
	 //select our sensor
	 onewire->select(address);
	 //read the scratchpad (BEh)
	 onewire->write(0xBE);
	 for (byte i=0;i<9;i++){
		 data[i] = onewire->read();
	 }
 }
 
 float Ds18S20Temperature::getTemperatureById(byte id, bool getcelsius)
 {
	if (id > Devicecount) return -255;
	return getTemperature(sensors[id], getcelsius);
 }
 
float Ds18S20Temperature::getTemperature(byte* address, bool getcelsius)
{
	byte data[12];
	writeTimeToScratchpad(address, 10);
	readTimeFromScratchpad(address,data);
 
	// Convert the data to actual temperature
	// because the result is a 16 bit signed integer, it should
	// be stored to an "int16_t" type, which is always 16 bits
	// even when compiled on a 32 bit processor.
	int16_t raw = (data[1] << 8) | data[0];
	if (getSensortype(address) == 1) 
	{
		raw = raw << 3; // 9 bit resolution default
		if (data[7] == 0x10) 
		{
			// "count remain" gives full 12 bit resolution
			raw = (raw & 0xFFF0) + 12 - data[6];
		}
	} 
	else 
	{
		byte cfg = (data[4] & 0x60);
		// at lower res, the low bits are undefined, so let's zero them
		if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
		else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
		else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
		//// default is 12 bit resolution, 750 ms conversion time
	}
	 
	float celsius = (float)raw / 16.0;
	float fahrenheit = celsius * 1.8 + 32.0;
	if (getcelsius)
	{
		return celsius;
	}
	return fahrenheit;
}
 
 byte Ds18S20Temperature::getSensortype(byte* address)
 {
 		// the first ROM byte indicates which chip
	switch (address[0]) {
		case 0x10:
		//Serial.println("  Chip = DS18S20");  // or old DS1820
		return 1;
		break;
		case 0x28:
		//Serial.println("  Chip = DS18B20");
		return 0;
		break;
		case 0x22:
		//Serial.println("  Chip = DS1822");
		return 0;
		break;
		default:
		//Serial.println("Device is not a DS18x20 family device.");
		return -1;
	}
	return -1;
 }

 void Ds18S20Temperature::readAdresses(void) {
	 byte addr[8];
	 
	 Devicecount = 0;

	 for(int i =0; i< _maxSensors; i++)
	 {
		sensors[i][0] =0;
	 }
	 onewire->reset_search();

	 while(onewire->search(addr)) {
		
		if (getSensortype(addr) == -1) continue;
		 for(int i= 0; i< 8; i++)
		 {
			sensors[Devicecount][i] = addr[i];
		 }
		 
		 Devicecount++;
		 if (Devicecount> _maxSensors ) break;
	 }
	 return;
 }

 char* Ds18S20Temperature::getAdress(int device, char* buffer)
 {
 	 if (device < 0 || device > _maxSensors	 )
	 {
		strcpy(buffer, "(null)");
		return buffer;
	 }
	 
	 if (sensors[device][0] == '\0' )
	 {
		strcpy(buffer, "(null)");
		return buffer;
	 }
	sprintf(buffer, "%X%X%X%X%X%X%X%X", sensors[device][0], sensors[device][1],sensors[device][2],sensors[device][3],
										sensors[device][4], sensors[device][5],sensors[device][6],sensors[device][7]);
	return buffer;
 }
 

