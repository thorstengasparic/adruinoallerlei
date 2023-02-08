/*
 * AL_ESC.h
 *
 * Created: 20.04.2017 21:40:38
 *  Author: gat
 */ 


#ifndef AL_ESC_H_
#define AL_ESC_H_

extern int esc_1, esc_2, esc_3, esc_4;
extern int counter_channel_1, counter_channel_2, counter_channel_3, counter_channel_4;
extern unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_loop_timer;
extern unsigned long zero_timer;

void InitESC(void);
void esc_pulse_output(void);
void print_signals(void);
void gyro_calibrate(void);


#endif /* AL-ESC_H_ */