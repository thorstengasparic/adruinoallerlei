/*
 * Beeper.cpp
 *
 * Created: 8/13/2012 11:06:47 PM
 *  Author: hefny
 */ 


#include <avr/io.h>
#include <stdbool.h>

#include "../Include/Beeper.h"
#include "../Include/Misc.h"
#include "../Include/IO_config.h"


void Beeper_Beep (uint16_t msDuration, uint8_t Times)
{
	
	//bool CurrentBuzzer_Status = Buzzer;
	
	for (int i=0; i< Times; ++i)
	{
		Buzzer = ON;
		delay_ms(msDuration);
		Buzzer = OFF;
		delay_ms(msDuration);		
	}
	
	//Buzzer = CurrentBuzzer_Status;
	
}

