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

#define MPU6050_I2C_ADDRESS1 0x68
#define MPU6050_I2C_ADDRESS2 0x69
//#define MPU6050_REFRESHRATE  250
//#define MPU6050_GYRORATE     65.5
class MPU6050 
{
	private:
		int MPU_addess;
		byte errorled;
		byte statusled;
		
		long acc_total_vector;
		
		double gyro_axis_cal[4];
		
		bool	isCalibated = false;
		bool	firsttime = true;
		
		void set_gyro_registers(void);
		void gyro_read(void);                                                        //Read the gyro output.
		bool raw_read();
		int gyro_address;
		int acc_axis[4], gyro_axis[4];

	public:
		int temperature;
		double gyro_pitch, gyro_roll, gyro_yaw;
		long acc_x, acc_y, acc_z ;
		float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll;

		bool begin(int mpu_addess, byte errorled, byte statusled);
		void calibrate(void);
		void calculateAngles(void);
		
		
};





#endif /* MPU6050LIB_H_ */