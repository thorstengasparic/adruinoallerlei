/*
 * Ds18S20Min.h
 *
 * Created: 02.04.2017 15:59:49
 *  Author: gat
 */ 


#ifndef DS18S20MIN_H_
#define DS18S20MIN_H_

#include <OneWire.h>
#include <Arduino.h>

typedef uint8_t DeviceAddress[8];
const int _maxSensors = 6;

class Ds18S20Temperature
{
		OneWire *onewire;
	
	public:
		int Devicecount;
		DeviceAddress sensors[_maxSensors];
		byte sensortype[_maxSensors];
		Ds18S20Temperature(OneWire*);
		void Begin(void);
		float getTemperatureById(byte id, bool getcelsius);
		char* getAdress(int device, char* buffer);

	private:		
		
		byte getSensortype(byte* address);
		float getTemperature(byte* address, bool getcelsius);
		void readAdresses(void) ;
		void readTimeFromScratchpad(byte* address, byte* data);
		void writeTimeToScratchpad(byte* address, int delaycnt);
};



#endif /* DS18S20MIN_H_ */