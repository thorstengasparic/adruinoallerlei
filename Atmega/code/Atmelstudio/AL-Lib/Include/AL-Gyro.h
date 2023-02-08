/*
 * AL_Gyro.h
 *
 * Created: 20.04.2017 19:26:26
 *  Author: gat
 */ 

#include <Arduino.h>
#include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.

#ifndef AL_GYRO_H_
#define AL_GYRO_H_

#include "AL-Common.h"

extern int gyro_address;

extern boolean first_angle;

extern int temperature;
extern long acc_x, acc_y, acc_z;
extern long acc_total_vector[20];
extern long acc_av_vector;

extern int acc_axis[4];
extern int gyro_axis[4];
extern double gyro_pitch, gyro_roll, gyro_yaw;
extern float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll;

extern int cal_int;
extern double gyro_axis_cal[4];

void InitGyro();

int convert_receiver_channel(byte function);
void calculate_pid();
void gyro_signalen();
void gyro_calculate(void);




#endif /* AL_GYRO_H_ */