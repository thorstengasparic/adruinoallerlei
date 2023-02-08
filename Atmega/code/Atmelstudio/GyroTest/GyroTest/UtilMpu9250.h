///*
 //* UtilMpu9250.h
 //*
 //* Created: 18.05.2017 13:21:05
 //*  Author: gat
 //*/ 
//
//
//#ifndef UTILMPU9250_H_
//#define UTILMPU9250_H_
//
//#include "Arduino.h"
//#include "I2Cdev.h"
//#include "Wire.h"
//#include "MPU9250Registers.h"
//
//extern double Temperature;
//extern double gyro_pitch, gyro_roll, gyro_yaw;
//extern long acc_x, acc_y, acc_z, acc_total_vector;
//extern double  MagX, MagY, MagZ;
//extern  double	gyro_axis_cal[4];
//extern  double	acc_axis_cal[4];
//extern  int		gyro_axis[4];
//extern  int		acc_axis[4];
//extern  int		mag_axis[4];
//extern  byte eeprom_data[36];
//extern  float magCalibration[3];
//#define LED_STATUS_PIN 13
//
//
//
//
 //void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
 //uint8_t readByte(uint8_t address, uint8_t subAddress);
 //void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
 //void initAK8963(float * destination, Mscale mscale);
 //void readMagData(int16_t * destination);
 //bool initMPU9250(byte smplRateDivider, Gscale gscale, Ascale ascale);
 //void MPU9250SelfTest(float * destination);
  //void calibrateMPU9250(double * dest1, double * dest2);
 //void setupSlave(uint8_t primary_address, uint8_t slave_id, uint8_t dev_addr, uint8_t reg_addr, bool is_read, uint8_t read_length, bool send_reg_addr, bool swap_bytes, bool odd_aligned, bool enable);
 //void enableI2CMaster() ;
 //void CalibrateGyro(double * gyrodest, double* accdest);
 //void GyroRead(void);
//
//
//#endif /* UTILMPU9250_H_ */