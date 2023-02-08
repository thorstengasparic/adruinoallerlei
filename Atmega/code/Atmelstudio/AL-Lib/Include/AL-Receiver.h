/*
 * AL_Receiver.h
 *
 * Created: 20.04.2017 19:56:10
 *  Author: gat
 */ 

#include <Arduino.h>
#include "AL-Common.h"

#ifndef AL_RECEIVER_H_
#define AL_RECEIVER_H_

extern int receiver_input[5];
extern unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4;
extern byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
extern unsigned long current_time, timer_1, timer_2, timer_3, timer_4;
extern volatile int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4;

void InitReceiver(void);
void wait_for_receiver();
void ISR_PCINT0_vect (void);


#endif /* AL_RECEIVER_H_ */