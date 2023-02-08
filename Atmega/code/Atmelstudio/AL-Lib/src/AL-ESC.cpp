/*
 * AL_ESC.cpp
 *
 * Created: 20.04.2017 21:40:22
 *  Author: gat
 */ 

 #include <Arduino.h>
 #include "AL-Receiver.h"
 #include "AL-ESC.h"

 int esc_1, esc_2, esc_3, esc_4;
 int counter_channel_1, counter_channel_2, counter_channel_3, counter_channel_4;
 unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_loop_timer;
 unsigned long zero_timer;

 void InitESC(void)
 {
	DDRD |= B11110000;	//Configure digital port 4, 5, 6 and 7 as output.
}
int esc_zero_timer;
  void esc_pulse_output(){
	
	esc_zero_timer = micros();
	PORTD |= B11110000;                                            //Set port 4, 5, 6 and 7 high at once
	timer_channel_1 = esc_1 + esc_zero_timer;                          //Calculate the time when digital port 4 is set low.
	timer_channel_2 = esc_2 + esc_zero_timer;                          //Calculate the time when digital port 5 is set low.
	timer_channel_3 = esc_3 + esc_zero_timer;                          //Calculate the time when digital port 6 is set low.
	timer_channel_4 = esc_4 + esc_zero_timer;                          //Calculate the time when digital port 7 is set low.
	
	while(PORTD >= 16){                                            //Execute the loop until digital port 4 to 7 is low.
	esc_loop_timer = micros();                                   //Check the current time.
	if(timer_channel_1 <= esc_loop_timer)PORTD &= B11101111;     //When the delay time is expired, digital port 4 is set low.
	if(timer_channel_2 <= esc_loop_timer)PORTD &= B11011111;     //When the delay time is expired, digital port 5 is set low.
	if(timer_channel_3 <= esc_loop_timer)PORTD &= B10111111;     //When the delay time is expired, digital port 6 is set low.
	if(timer_channel_4 <= esc_loop_timer)PORTD &= B01111111;     //When the delay time is expired, digital port 7 is set low.
	}
  }
  
  void print_signals(){
	  
	  //Serial.print("Start:");
	  //Serial.print(start);
	  
	  Serial.print("  Roll:");
	  if(receiver_input_channel_1 - 1480 < 0)Serial.print("<<<");
	  else if(receiver_input_channel_1 - 1520 > 0)Serial.print(">>>");
	  else Serial.print("-+-");
	  Serial.print(receiver_input_channel_1);
	  
	  Serial.print("  Pitch:");
	  if(receiver_input_channel_2 - 1480 < 0)Serial.print("^^^");
	  else if(receiver_input_channel_2 - 1520 > 0)Serial.print("vvv");
	  else Serial.print("-+-");
	  Serial.print(receiver_input_channel_2);
	  
	  Serial.print("  Throttle:");
	  if(receiver_input_channel_3 - 1480 < 0)Serial.print("vvv");
	  else if(receiver_input_channel_3 - 1520 > 0)Serial.print("^^^");
	  else Serial.print("-+-");
	  Serial.print(receiver_input_channel_3);
	  
	  Serial.print("  Yaw:");
	  if(receiver_input_channel_4 - 1480 < 0)Serial.print("<<<");
	  else if(receiver_input_channel_4 - 1520 > 0)Serial.print(">>>");
	  else Serial.print("-+-");
	  Serial.print(receiver_input_channel_4);
	  Serial.print("   ");
	  Serial.print(esc_1);
	  Serial.print("   ");
	  Serial.println(esc_2);
	  
  }

  void PulseESCOFF(void)
  {
	//We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
	  PORTD |= B11110000;                                                             //Set digital poort 4, 5, 6 and 7 high.
	  delayMicroseconds(1000);                                                        //Wait 1000us.
	  PORTD &= B00001111;                                                             //Set digital poort 4, 5, 6 and 7 low.
	  delay(3);                                                                       //Wait 3 milliseconds before the next loop.
  }
