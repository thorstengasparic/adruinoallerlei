#include <..\OneWire\OneWire.h>
#include <DS1820.h>

#include <stdlib.h>
#include <inttypes.h>
#include "WConstants.h"
#include "HardwareSerial.h"


DS1820::DS1820(uint8_t IoPin)
{
	debug = false;
	ds = OneWire(IoPin);
	Reset();

}
void DS1820::Reset()
{
	SensorCount = 0;
}

void DS1820::Search()
{
	SensorCount = 0;
	while(ds.search(addr[SensorCount])) 
	{
		if ( OneWire::crc8( addr[SensorCount], 7) != addr[SensorCount][7]) 
		{
			if (debug) Serial.print("CRC is not valid!\n");
			continue;
		}
  
		if ( addr[SensorCount][0] != 0x10) 
		{
			if (debug) Serial.print("Device is not a DS18S20 family device.\n");
			continue;
		}
      
		if (debug)
		{
			Serial.print("SensorID: =");
			for( int i = 0; i < 8; i++) 
			{
				Serial.print(addr[SensorCount][i], HEX);
				Serial.print(" ");
			}
			Serial.println("");
		}
  		SensorCount++;
		if (SensorCount >= MAX_SENSORCOUNT) break;
	}
    ds.reset_search();
    return;
}

float DS1820::Measure(uint8_t sensor)
{
	if (SensorCount == 0) return 0.0;
	if (sensor >= SensorCount) return 0.0;
	uint8_t i;
	uint8_t present = 0;

	ds.reset();
	ds.select(addr[sensor]);
	ds.write(0x44,1);         // start conversion, with parasite power on at the end
	i = 0;
	while (true)
	{
	  present = ds.read();
	  if (present != 0) break;
	  if (i++ > 100) break;
	  delay(10);
	}

	present = ds.reset();
	ds.select(addr[sensor]);    
	ds.write(0xBE);         // Read Scratchpad
	for ( i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = ds.read();
	}
	if (debug)
	{
	  Serial.print("P=");
	  Serial.print(present,HEX);
	  Serial.print(" ");
	  for ( i = 0; i < 9; i++) {           
		Serial.print(data[i], HEX);
		Serial.print(" ");
	  }
	  Serial.println("");
	}
	float temp = ((int)(data[1]<<8) + (int)data[0]) / 2.0;
	return temp;
 }
