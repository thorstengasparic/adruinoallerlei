/*
 * AL_Eprom.h
 *
 * Created: 20.04.2017 19:39:41
 *  Author: gat
 */ 

#include <Arduino.h>
#include <EEPROM.h>                        //Include the EEPROM.h library so we can store information onto the EEPROM

#ifndef AL_EPROM_H_
#define AL_EPROM_H_

extern bool eeprom_ok;
extern byte eeprom_data[36];

bool ReadEEprom(bool doreturn);
void WriteEEprom(void);


#endif /* AL_EPROM_H_ */