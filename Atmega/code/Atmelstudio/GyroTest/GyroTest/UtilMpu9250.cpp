///*
 //* UtilMpu9250.cpp
 //*
 //* Created: 18.05.2017 13:24:24
 //*  Author: gat
 //*/ 
 //#include "Arduino.h"
 //#include "I2Cdev.h"
 //#include "Wire.h"
//#include <EEPROM.h>                                  //Include the EEPROM.h library so we can store information onto the EEPROM
//
//#include "UtilMpu9250.h"
//
 ////uint8_t Gscale = GFS_250DPS;
 ////uint8_t Ascale = AFS_2G;
 ////uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
 //uint8_t Mmode = 0x06;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read
 //float   SelfTest[6];    // holds results of gyro and accelerometer self test
//
//
////double	gyro_axis_cal[4] {0,0,0,0};
////double	acc_axis_cal[4]{0,0,0,0};
////int temperature;
////int		gyro_axis[4];
////int		acc_axis[4];
////int		mag_axis[4];
//float magCalibration[3] = {0, 0, 0};
//double Temperature;
//double gyro_pitch, gyro_roll, gyro_yaw;
//long acc_x, acc_y, acc_z, acc_total_vector;
//double MagX, MagY, MagZ;
//byte eeprom_data[36];
//
//
//bool initMPU9250(byte smplRateDivider, Gscale gscale, Ascale ascale)
 //{
//
	 //byte c1 = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250 
	 //if (c1 != 0x73)
	 //{
		//Serial.print("ERROR: MPU9250 "); Serial.print("I AM 0x"); Serial.println(c1, HEX);	 
		//return false;
	 //}
//
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
	 //delay(100);
	 //
	 //// get stable time source; Auto select clock source to be PLL gyroscope reference if ready
	 //// else use the internal oscillator, bits 2:0 = 001
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
	 //delay(200);
//
	 //// Configure device for bias calculation
	 //writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
	 //writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
	 //writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
	 //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
	 //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
	 //delay(15);
	 //
	 //// wake up device
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
	 //delay(100); // Wait for all registers to reset
//
	 //// get stable time source
	 //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
	 //delay(200);
	 //
	 //
	 //// Set gyroscope full scale range
	 //// Range selects FS_SEL and GFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
	 //uint8_t c = readByte(MPU9250_ADDRESS, GYRO_CONFIG); // get current GYRO_CONFIG register value
	 //c = c & ~0xE0; // Clear self-test bits [7:5]
	 //c = c & ~0x03; // Clear Fchoice bits [1:0]
	 //c = c & ~0x18; // Clear GFS bits [4:3]
	 //c = c | gscale << 3; // Set full scale range for the gyro
	 //// c =| 0x00; // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of GYRO_CONFIG
	 //writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c ); // Write new GYRO_CONFIG value to register
	 	 //
	 //// Set accelerometer full-scale range configuration
	 //c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG); // get current ACCEL_CONFIG register value
	 //c = c & ~0xE0; // Clear self-test bits [7:5]
	 //c = c & ~0x18;  // Clear AFS bits [4:3]
	 //c = c | ascale << 3; // Set full scale range for the accelerometer
	 //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value
	 //
	 //// Set accelerometer sample rate configuration
	 //// It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
	 //// accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
	 //c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2); // get current ACCEL_CONFIG2 register value
	 //c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
	 //c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
	 //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value
	 //
	 //// Configure Gyro and Thermometer
	 //// Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively;
	 //// minimum delay time for this setting is 5.9 ms, which means sensor fusion update rates cannot
	 //// be higher than 1 / 0.0059 = 170 Hz
	 //// DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
	 //// With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
	 //writeByte(MPU9250_ADDRESS, CONFIG, 0x03);
	 //
	 //// Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
	 //if (smplRateDivider > 1)
		//writeByte(MPU9250_ADDRESS, SMPLRT_DIV, smplRateDivider);  // Use a 200 Hz rate; a rate consistent with the filter update rate
	 //// The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
	 //// but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting
	 //// determined inset in CONFIG above
//
	 //// Configure Interrupts and Bypass Enable
	 //// Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
	 //// clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips
	 //// can join the I2C bus and all can be controlled by the Arduino as master
	 //writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);
	 ////writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
	 ////writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
	 //delay(100);
	 //return true;
 //}
//
 //void MPU9250SelfTest(float * destination) // Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
//{
	//uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
	//uint8_t selfTest[6];
	//int32_t gAvg[3] = {0}, aAvg[3] = {0}, aSTAvg[3] = {0}, gSTAvg[3] = {0};
	//float factoryTrim[6];
	//uint8_t FS = 0;
	//
	//writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
	//writeByte(MPU9250_ADDRESS, CONFIG, 0x02);        // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
	//writeByte(MPU9250_ADDRESS, GYRO_CONFIG, FS<<3);  // Set full scale range for the gyro to 250 dps
	//writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
	//writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, FS<<3); // Set full scale range for the accelerometer to 2 g
//
	//for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
		//
		//readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
		//aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
		//aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
		//aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
		//
		//readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);       // Read the six raw data registers sequentially into data array
		//gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
		//gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
		//gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
	//}
	//
	//for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
		//aAvg[ii] /= 200;
		//gAvg[ii] /= 200;
	//}
	//
	//// Configure the accelerometer for self-test
	//writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
	//writeByte(MPU9250_ADDRESS, GYRO_CONFIG,  0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
	//delay(25);  // Delay a while to let the device stabilize
//
	//for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
		//
		//readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
		//aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
		//aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
		//aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
		//
		//readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
		//gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
		//gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
		//gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
	//}
	//
	//for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average self-test readings
		//aSTAvg[ii] /= 200;
		//gSTAvg[ii] /= 200;
	//}
	//
	//// Configure the gyro and accelerometer for normal operation
	//writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
	//writeByte(MPU9250_ADDRESS, GYRO_CONFIG,  0x00);
	//delay(25);  // Delay a while to let the device stabilize
	//
	//// Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
	//selfTest[0] = readByte(MPU9250_ADDRESS, SELF_TEST_X_ACCEL); // X-axis accel self-test results
	//selfTest[1] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_ACCEL); // Y-axis accel self-test results
	//selfTest[2] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_ACCEL); // Z-axis accel self-test results
	//selfTest[3] = readByte(MPU9250_ADDRESS, SELF_TEST_X_GYRO);  // X-axis gyro self-test results
	//selfTest[4] = readByte(MPU9250_ADDRESS, SELF_TEST_Y_GYRO);  // Y-axis gyro self-test results
	//selfTest[5] = readByte(MPU9250_ADDRESS, SELF_TEST_Z_GYRO);  // Z-axis gyro self-test results
//
	//// Retrieve factory self-test value from self-test code reads
	//factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
	//factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
	//factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
	//factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
	//factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
	//factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation
	//
	//// Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
	//// To get percent, must multiply by 100
	//for (int i = 0; i < 3; i++) {
		//destination[i]   = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i] - 100.;   // Report percent differences
		//destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3] - 100.; // Report percent differences
	//}
	//
//}
//
//
//void CalibrateGyro(double * gyroCalc, double * accCalc)
//{
	//int32_t gyro_bias[4]  = {0, 0, 0, 0}, accel_bias[4] = {0, 0, 0, 0};
//
	//gyroCalc[1] = 0;
	//gyroCalc[2] = 0;
	//gyroCalc[3]  = 0;
//
	//accCalc[1]  = 0;
	//accCalc[2]  = 0;
	//accCalc[3]  = 0;
	////Let's take multiple gyro data samples so we can determine the average gyro offset (calibration).
	//for (int cal = 0; cal < 2000 ; cal ++){                           //Take 2000 readings for calibration.
		//if(cal % 15 == 0)digitalWrite(LED_STATUS_PIN , !digitalRead(LED_STATUS_PIN));                //Change the led status to indicate calibration.
		//GyroRead();
		//gyro_bias[1] += gyro_axis[1];                                       //Ad roll value to gyro_roll_cal.
		//gyro_bias[2] += gyro_axis[2];                                       //Ad pitch value to gyro_pitch_cal.
		//gyro_bias[3] += gyro_axis[3];                                       //Ad yaw value to gyro_yaw_cal.
//
		//accel_bias[1] += acc_axis[1];                                       //Ad roll value to gyro_roll_cal.
		//accel_bias[2] += acc_axis[2];                                       //Ad pitch value to gyro_pitch_cal.
		//accel_bias[3] += acc_axis[3];                                       //Ad yaw value to gyro_yaw_cal.
		////We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
		//PORTD |= B11110000;                                                     //Set digital poort 4, 5, 6 and 7 high.
		//delayMicroseconds(1000);                                                //Wait 1000us.
		//PORTD &= B00001111;                                                     //Set digital poort 4, 5, 6 and 7 low.
		//delay(3);                                                               //Wait 3 milliseconds before the next loop.
	//}
	//
	//gyroCalc[1] = gyro_bias[1] / 2000;                                                 
	//gyroCalc[2] = gyro_bias[2] / 2000;                                                 
	//gyroCalc[3] = gyro_bias[3] / 2000;                                                 
	//
	////byte data[6];
	////data[0] = (-gyro_bias[0]  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
	////data[1] = (-gyro_bias[0])       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
	////data[2] = (-gyro_bias[1]  >> 8) & 0xFF;
	////data[3] = (-gyro_bias[1])       & 0xFF;
	////data[4] = (-gyro_bias[2]  >> 8) & 0xFF;
	////data[5] = (-gyro_bias[2])       & 0xFF;
	////
	////// Push gyro biases to hardware registers
	////writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
	////writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
	////writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
	////writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
	////writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
	////writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);
	////gyroCalc[1] = 0;
	////gyroCalc[2] = 0;
	////gyroCalc[3]  = 0;
//
	//accCalc[1] = accel_bias[1] / 2000;
	//accCalc[2] = accel_bias[2] / 2000;
	//accCalc[3] = accel_bias[3] / 2000;
//}
//
//// Function which accumulates gyro and accelerometer data after device initialization. It calculates the average
//// of the at-rest readings and then loads the resulting offsets into accelerometer and gyro bias registers.
//void calibrateMPU9250(float * dest1, float * dest2)
//{  
  //uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
  //uint16_t ii, packet_count, fifo_count;
  //int32_t gyro_bias[3]  = {0, 0, 0}, accel_bias[3] = {0, 0, 0};
  //
 //// reset device
  //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
  //delay(100);
   //
 //// get stable time source; Auto select clock source to be PLL gyroscope reference if ready 
 //// else use the internal oscillator, bits 2:0 = 001
  //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  
  //writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
  //delay(200);                                    
//
//// Configure device for bias calculation
  //writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
  //writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
  //writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
  //writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
  //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
  //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
  //delay(15);
  //
//// Configure MPU6050 gyro and accelerometer for bias calculation
  //writeByte(MPU9250_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
  //writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
  //writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
  //writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity
 //
  //uint16_t  gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
  //uint16_t  accelsensitivity = 16384;  // = 16384 LSB/g
//
    //// Configure FIFO to capture accelerometer and gyro data for bias calculation
  //writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO  
  //writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in MPU-9150)
  //delay(40); // accumulate 40 samples in 40 milliseconds = 480 bytes
//
//// At end of sample accumulation, turn off FIFO sensor read
  //writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
  //readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
  //fifo_count = ((uint16_t)data[0] << 8) | data[1];
  //packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging
  //
  //for (ii = 0; ii < packet_count; ii++) {
    //int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
    //readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
    //accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
    //accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
    //accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;    
    //gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
    //gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
    //gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;
    //
    //accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
    //accel_bias[1] += (int32_t) accel_temp[1];
    //accel_bias[2] += (int32_t) accel_temp[2];
    //gyro_bias[0]  += (int32_t) gyro_temp[0];
    //gyro_bias[1]  += (int32_t) gyro_temp[1];
    //gyro_bias[2]  += (int32_t) gyro_temp[2];
            //
//}
    //accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    //accel_bias[1] /= (int32_t) packet_count;
    //accel_bias[2] /= (int32_t) packet_count;
    //gyro_bias[0]  /= (int32_t) packet_count;
    //gyro_bias[1]  /= (int32_t) packet_count;
    //gyro_bias[2]  /= (int32_t) packet_count;
    //
  //if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
  //else {accel_bias[2] += (int32_t) accelsensitivity;}
   //
//// Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
  //data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
  //data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
  //data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
  //data[3] = (-gyro_bias[1]/4)       & 0xFF;
  //data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
  //data[5] = (-gyro_bias[2]/4)       & 0xFF;
  //
//// Push gyro biases to hardware registers
  //writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
  //writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
  //writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
  //writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
  //writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
  //writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);
  //
//// Output scaled gyro biases for display in the main program
  //dest1[0] = (float) gyro_bias[0]/(float) gyrosensitivity;  
  //dest1[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
  //dest1[2] = (float) gyro_bias[2]/(float) gyrosensitivity;
//
//// Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
//// factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
//// non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
//// compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
//// the accelerometer biases calculated above must be divided by 8.
//
  //int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
  //readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
  //accel_bias_reg[0] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
  //readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
  //accel_bias_reg[1] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
  //readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
  //accel_bias_reg[2] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
  //
  //uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
  //uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis
  //
  //for(ii = 0; ii < 3; ii++) {
    //if((accel_bias_reg[ii] & mask)) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
  //}
  //
  //// Construct total accelerometer bias, including calculated average accelerometer bias from above
  //accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
  //accel_bias_reg[1] -= (accel_bias[1]/8);
  //accel_bias_reg[2] -= (accel_bias[2]/8);
  //
  //data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
  //data[1] = (accel_bias_reg[0])      & 0xFF;
  //data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  //data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
  //data[3] = (accel_bias_reg[1])      & 0xFF;
  //data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
  //data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
  //data[5] = (accel_bias_reg[2])      & 0xFF;
  //data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers
 //
//// Apparently this is not working for the acceleration biases in the MPU-9250
//// Are we handling the temperature correction bit properly?
//// Push accelerometer biases to hardware registers
//
//writeByte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
  //writeByte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
  //writeByte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
  //writeByte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
  //writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
  //writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);
//
//// Output scaled accelerometer biases for display in the main program
   //dest2[0] = (float)accel_bias[0]/(float)accelsensitivity; 
   //dest2[1] = (float)accel_bias[1]/(float)accelsensitivity;
   //dest2[2] = (float)accel_bias[2]/(float)accelsensitivity;
//}
////#define TestProgram 1
////int cal_int =0;
////void GyroRead(){
	//////Read the MPU-6050
	////#ifdef TestProgram
		////eeprom_data[31] = 1;
	////#endif
	////if(eeprom_data[31] == 1)
	////{
		////Wire.beginTransmission(MPU9250_ADDRESS);                                   //Start communication with the gyro.
		////Wire.write(0x3B);                                                       //Start reading @ register 43h and auto increment with every read.
		////Wire.endTransmission();                                                 //End the transmission.
		////Wire.requestFrom(MPU9250_ADDRESS,14);                                      //Request 14 bytes from the gyro.
		////
		////#ifndef TestProgram
		////receiver_input_channel_1 = convert_receiver_channel(1);                 //Convert the actual receiver signals for pitch to the standard 1000 - 2000us.
		////receiver_input_channel_2 = convert_receiver_channel(2);                 //Convert the actual receiver signals for roll to the standard 1000 - 2000us.
		////receiver_input_channel_3 = convert_receiver_channel(3);                 //Convert the actual receiver signals for throttle to the standard 1000 - 2000us.
		////receiver_input_channel_4 = convert_receiver_channel(4);                 //Convert the actual receiver signals for yaw to the standard 1000 - 2000us.
		////#endif
		////
		////while(Wire.available() < 14);                                           //Wait until the 14 bytes are received.
		////acc_axis[1] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_x variable.
		////acc_axis[2] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_y variable.
		////acc_axis[3] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_z variable.
		////temperature = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the temperature variable.
		////gyro_axis[1] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
		////gyro_axis[2] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
		////gyro_axis[3] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
	////}
////
	////if(cal_int == 2000){
		////gyro_axis[1] -= gyro_axis_cal[1];                                       //Only compensate after the calibration.
		////gyro_axis[2] -= gyro_axis_cal[2];                                       //Only compensate after the calibration.
		////gyro_axis[3] -= gyro_axis_cal[3];                                       //Only compensate after the calibration.
	////}
	////
	////#ifndef TestProgram
		////gyro_roll = gyro_axis[1];
		////gyro_pitch =  = gyro_axis[2];
		////gyro_yaw =  = gyro_axis[3];
////
		////acc_x = acc_axis[1];
		////acc_y  = acc_axis[2];
		////acc_z =  = acc_axis[3];
	////#else
		////gyro_roll = gyro_axis[eeprom_data[28] & 0b00000011];                      //Set gyro_roll to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[28] & 0b10000000)gyro_roll *= -1;                          //Invert gyro_roll if the MSB of EEPROM bit 28 is set.
		////gyro_pitch = gyro_axis[eeprom_data[29] & 0b00000011];                     //Set gyro_pitch to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[29] & 0b10000000)gyro_pitch *= -1;                         //Invert gyro_pitch if the MSB of EEPROM bit 29 is set.
		////gyro_yaw = gyro_axis[eeprom_data[30] & 0b00000011];                       //Set gyro_yaw to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[30] & 0b10000000)gyro_yaw *= -1;                           //Invert gyro_yaw if the MSB of EEPROM bit 30 is set.
////
		////acc_x = acc_axis[eeprom_data[29] & 0b00000011];                           //Set acc_x to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[29] & 0b10000000)acc_x *= -1;                              //Invert acc_x if the MSB of EEPROM bit 29 is set.
		////acc_y = acc_axis[eeprom_data[28] & 0b00000011];                           //Set acc_y to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[28] & 0b10000000)acc_y *= -1;                              //Invert acc_y if the MSB of EEPROM bit 28 is set.
		////acc_z = acc_axis[eeprom_data[30] & 0b00000011];                           //Set acc_z to the correct axis that was stored in the EEPROM.
		////if(eeprom_data[30] & 0b10000000)acc_z *= -1;                              //Invert acc_z if the MSB of EEPROM bit 30 is set.
	////#endif
////}
//
//void InitMaster(void)
//{
	//writeByte(MPU9250_ADDRESS, INT_PIN_CFG	, 0x00);             //INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=0 ; CLKOUT_EN=0
	//writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x5D);
	//
	//writeByte(MPU9250_ADDRESS, USER_CTRL	, 0b00100000);       //USER_CTRL     -- DMP_EN=0 ; FIFO_EN=0 ; I2C_MST_EN=1 (I2C master mode) ; I2C_IF_DIS=0 ; FIFO_RESET=0 ; I2C_MST_RESET=0 ; SIG_COND_RESET=0
	//writeByte(MPU9250_ADDRESS, I2C_MST_CTRL	, 0x0D);             //I2C_MST_CTRL  -- MULT_MST_EN=0 ; WAIT_FOR_ES=0 ; SLV_3_FIFO_EN=0 ; I2C_MST_P_NSR=0 ; I2C_MST_CLK=13 (I2C slave speed bus = 400kHz)
	//writeByte(MPU9250_ADDRESS, I2C_SLV0_ADDR, 0x80|AK8963_ADDRESS );//I2C_SLV0_ADDR -- I2C_SLV4_RW=1 (read operation) ; I2C_SLV4_ADDR=MAG_ADDRESS
	//writeByte(MPU9250_ADDRESS, I2C_SLV0_REG	, AK8963_XOUT_L);//I2C_SLV0_REG  -- 6 data bytes of MAG are stored in 6 registers. First register address is MAG_DATA_REGISTER
	//writeByte(MPU9250_ADDRESS, I2C_SLV0_CTRL, 0x86);             //I2C_SLV0_CTRL -- I2C_SLV0_EN=1 ; I2C_SLV0_BYTE_SW=0 ; I2C_SLV0_REG_DIS=0 ; I2C_SLV0_GRP=0 ; I2C_SLV0_LEN=3 (3x2 bytes)
//}
//
//void setupSlave(uint8_t primary_address, uint8_t slave_id, uint8_t dev_addr, uint8_t reg_addr, bool is_read, uint8_t read_length, bool send_reg_addr, bool swap_bytes, bool odd_aligned, bool enable)
//{
	//#define I2C_SLV_ENABLE_BIT      7
	//#define I2C_SLV_BYTESWP_BIT     6
	//#define I2C_SLV_REG_DIS_BIT     5
	//#define I2C_SLV_SWP_GRP_BIT     4
	//#define I2C_SLV_READ_LEN_BIT    3
	//#define I2C_SLV_READ_LEN_LENGTH 4
//
	//if (slave_id > 3) return;
//
	//uint8_t I2C_SLV_START = I2C_SLV0_ADDR + slave_id*3;
//
	//writeByte(primary_address, I2C_SLV_START + 2, 0x00);		// Disable slave while we reconfigure it
	//dev_addr = (((is_read) ? 0x80 : 0x00) | dev_addr);			// Write(0x00) or Read(0x80) from device
	//writeByte(primary_address, I2C_SLV_START + 0, dev_addr);	// set the slave device address
	//writeByte(primary_address, I2C_SLV_START + 1, reg_addr);	// set the slave register address
	//uint8_t slave_ctrl_byte =	(enable << I2C_SLV_ENABLE_BIT)	| (swap_bytes << I2C_SLV_BYTESWP_BIT)	| (!send_reg_addr << I2C_SLV_REG_DIS_BIT)	| (odd_aligned << I2C_SLV_SWP_GRP_BIT)	| (read_length % 16)	;
	//writeByte(primary_address, I2C_SLV_START + 2, slave_ctrl_byte); // set the slave control byte
	//// And we're done
//}
//
//void enableI2CMaster() {
//
	//// First disable INT_BYPASS
	//writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x00); // I prefer 0x30 or 0x20 here; but those values have nothing to do with I2C
//
	//// Next configure the I2C Master
	//// No other masters on the bus, unless there are (in which case switch this high bit)
	//// Wait for external sensors to finish before data ready interrupt
	//// No FIFO for Slave3 (which is actually about Slave3 and not the I2C Master)
	//// Always issue a full stop, then a start when transitioning between slaves (instead of a restart)
	//// Access the bus at 400kHz (see table in register map for other values)
	//writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x5D);
//
	//// Lastly, enable the I2C Master on the MPU
	//writeByte(MPU9250_ADDRESS, USER_CTRL, 0x20);
//
//}
//
//
//void initAK8963(float * destination, Mscale mscale)
//{
	//// First extract the factory calibration for each magnetometer axis
	//uint8_t rawData[3];  // x/y/z gyro calibration data stored here
	//writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	//delay(10);
	//writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
	//delay(10);
	//readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
	//destination[0] =  (float)(rawData[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
	//destination[1] =  (float)(rawData[1] - 128)/256. + 1.;
	//destination[2] =  (float)(rawData[2] - 128)/256. + 1.;
	//writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	//delay(10);
	//// Configure the magnetometer for continuous read and highest resolution
	//// set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
	//// and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
	//writeByte(AK8963_ADDRESS, AK8963_CNTL, mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
	//delay(10);
//}
//
//void readMagData(int16_t * destination)
//{
	//uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
	//if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
		//readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
		//uint8_t c = rawData[6]; // End data read by reading ST2 register
		//if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
			//mag_axis[1]  = ((int16_t)rawData[1] << 8) | rawData[0] ;  // Turn the MSB and LSB into a signed 16-bit value
			//mag_axis[2]  = ((int16_t)rawData[3] << 8) | rawData[2] ;  // Data stored as little Endian
			//mag_axis[3]  = ((int16_t)rawData[5] << 8) | rawData[4] ;
			////double mRes = 10.*4912./32760.0;
			//double mRes = 4912.0/32760.0;
			//MagX = (double)mag_axis[1] * magCalibration[0]*mRes;
			//MagY= (double)mag_axis[2] * magCalibration[1]*mRes;
			//MagZ = (double)mag_axis[3] * magCalibration[2]*mRes;;
		//}
	//}
	//
//}
//
//
//void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
//{
	//Wire.beginTransmission(address);  // Initialize the Tx buffer
	//Wire.write(subAddress);           // Put slave register address in Tx buffer
	//Wire.write(data);                 // Put data in Tx buffer
	//Wire.endTransmission();           // Send the Tx buffer
//}
//
//uint8_t readByte(uint8_t address, uint8_t subAddress)
//{
	//uint8_t data; // `data` will store the register data
	//Wire.beginTransmission(address);         // Initialize the Tx buffer
	//Wire.write(subAddress);	                 // Put slave register address in Tx buffer
	//Wire.endTransmission();        // Send the Tx buffer, but send a restart to keep connection alive
	////	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
	////	Wire.requestFrom(address, 1);  // Read one byte from slave register address
	//Wire.requestFrom(address, (size_t) 1);  // Read one byte from slave register address
	//data = Wire.read();                      // Fill Rx buffer with result
	//return data;                             // Return data read from slave register
//}
//
//void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
//{
	//Wire.beginTransmission(address);   // Initialize the Tx buffer
	//Wire.write(subAddress);            // Put slave register address in Tx buffer
	//Wire.endTransmission();  // Send the Tx buffer, but send a restart to keep connection alive
	////	Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
	//uint8_t i = 0;
	////        Wire.requestFrom(address, count);  // Read bytes from slave register address
	//Wire.requestFrom(address, (size_t) count);  // Read bytes from slave register address
	//while (Wire.available()) {
	//dest[i++] = Wire.read(); }         // Put read results in the Rx buffer
//}
