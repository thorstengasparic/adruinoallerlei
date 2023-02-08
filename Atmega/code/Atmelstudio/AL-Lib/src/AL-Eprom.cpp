/*
 * AL_Eprom.cpp
 *
 * Created: 20.04.2017 19:40:02
 *  Author: gat
 */ 
 #include <Arduino.h>
 #include <EEPROM.h>                        //Include the EEPROM.h library so we can store information onto the EEPROM
 #include "AL-Common.h"
 #include "AL-Eprom.h"
 
 bool eeprom_ok = false;
 byte eeprom_data[36];

 bool ReadEEprom(bool doreturn)
 {
	eeprom_ok = false;
	for(int data = 0; data <= 35; data++)eeprom_data[data] = EEPROM.read(data);               //Read EEPROM for faster data access
	//Check the EEPROM signature to make sure that the setup program is executed.
	while(eeprom_data[33] != 'J' || eeprom_data[34] != 'M' || eeprom_data[35] != 'B'){
		if (doreturn) return false;
		BlinkSignal(ERROR_EPROM, false);
	}
	eeprom_ok = true;
	return true;
 }
 void WriteEEprom(void)
 {}