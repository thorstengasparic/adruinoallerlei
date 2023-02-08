/*
 * MPU6050Lib.h
 *
 * Created: 05.04.2017 09:06:37
 *  Author: gat
 */ 


#ifndef MPU6050LIB_H_
#define MPU6050LIB_H_
#include <Arduino.h>
#include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.

#include "MPU6050.h"

#define MPU6050_I2C_ADDRESS1 0x68
#define MPU6050_I2C_ADDRESS2 0x69

class MPU6050Basic 
{
	private:
		int MPU_addess;
		byte errorled;
		byte statusled;
		
		int		cal_int;
		double	gyro_axis_cal[4];
		int		gyro_axis[4];
		int		acc_axis[4];
		
		
		

		void calibrate(void);
		void set_gyro_registers(void);
		void gyro_read(void);                                                        //Read the gyro output.
		
		unsigned long refresh_timer ;                                                    //needs 3 microSeconds

	public:
		
		bool begin(int mpu_addess, byte errorled, byte statusled);
		void calculateAngles(double refreshrateHZ);
		bool RawRead();
		
		double Temperature;
		double RollRaw, NickRaw, YawRaw;
		double AccX, AccY, AccZ;
		float acc_total_vector;
		double RollAngle_Acc, NickAngle_Acc;
		double RollAngle, NickAngle;
};





#endif /* MPU6050LIB_H_ */