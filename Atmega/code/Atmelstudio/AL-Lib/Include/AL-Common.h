/*
 * AL_Common.h
 *
 * Created: 20.04.2017 19:30:05
 *  Author: gat
 */ 


#include <Arduino.h>
#include <Wire.h>

#ifndef AL_COMMON_H_
#define AL_COMMON_H_

#define LED_STATUS_PIN 13
#define GYRO_ADDRESS 0x68

#define INFO_WAITRECEIVER	2

#define ERROR_GYRODETECT 10
#define ERROR_GYROSET	 11
#define ERROR_EPROM		 12

void InitCommon(void);

void BlinkSignal(int statusNo, bool doreturn);


#endif /* AL_COMMON_H_ */