/*
 * MPU6050Lib.cpp
 *
 * Created: 05.04.2017 09:05:45
 *  Author: gat
 */ 
 #include <Arduino.h>
 #include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.
 #include "MPU6050_6Axis_MotionApps20.h"
 #include "MPU6050Raw.h"
  
bool MPU6050Basic::begin(int mpu_addess, byte error_led, byte statusled)
{
	MPU6050Basic::MPU_addess = mpu_addess;
	MPU6050Basic::errorled = error_led;
	MPU6050Basic::statusled = statusled;
	
	TWBR = 12;                                                                //Set the I2C clock speed to 400kHz.
	refresh_timer = 0;
	set_gyro_registers();
	//calibrate();
	return true;
}

void MPU6050Basic::calibrate(void)
{
	gyro_axis_cal[1] =0;
	gyro_axis_cal[2] =0;
	gyro_axis_cal[3] =0;

	

	for (cal_int = 0; cal_int < 2000 ; cal_int ++)
	{                           
		//Take 2000 readings for calibration.
		if(cal_int % 15 == 0)digitalWrite(statusled, !digitalRead(statusled));  //Change the led status to indicate calibration.
		RawRead();                                                        //Read the gyro output.
		gyro_axis_cal[1] += gyro_axis[1];                                       //Ad roll value to gyro_roll_cal.
		gyro_axis_cal[2] += gyro_axis[2];                                       //Ad pitch value to gyro_pitch_cal.
		gyro_axis_cal[3] += gyro_axis[3];                                       //Ad yaw value to gyro_yaw_cal.
		//We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
		//PORTD |= B11110000;                                                     //Set digital poort 4, 5, 6 and 7 high.
		//delayMicroseconds(1000);                                                //Wait 1000us.
		//PORTD &= B00001111;                                                     //Set digital poort 4, 5, 6 and 7 low.
		delay(5);                                                               //Wait 3 milliseconds before the next loop.
	}	
	//Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
	gyro_axis_cal[1] /= 2000;                                                 //Divide the roll total by 2000.
	gyro_axis_cal[2] /= 2000;                                                 //Divide the pitch total by 2000.
	gyro_axis_cal[3] /= 2000;                                                 //Divide the yaw total by 2000.

	calculateAngles(250.0);
	RollAngle =RollAngle_Acc;
	NickAngle =NickAngle_Acc;

}


void MPU6050Basic::set_gyro_registers(void){
	 //Setup the MPU-6050
	Wire.beginTransmission(MPU_addess);                                     
	Wire.write(0x6B);                                                          //We want to write to the PWR_MGMT_1 register (6B hex)
	Wire.write(0x00);                                                          //Set the register bits as 00000000 to activate the gyro
	Wire.endTransmission();                                                    //End the transmission with the gyro.

	Wire.beginTransmission(MPU_addess);                                     
	Wire.write(0x1B);                                                          //We want to write to the GYRO_CONFIG register (1B hex)
	Wire.write(0x08);                                                          //Set the register bits as 00001000 (500dps full scale)
	Wire.endTransmission();                                                    //End the transmission with the gyro

	Wire.beginTransmission(MPU_addess);                                     
	Wire.write(0x1C);                                                          //We want to write to the ACCEL_CONFIG register (1A hex)
	Wire.write(0x10);                                                          //Set the register bits as 00010000 (+/- 8g full scale range)
	Wire.endTransmission();                                                    //End the transmission with the gyro

	//Let's perform a random register check to see if the values are written correct
	Wire.beginTransmission(MPU_addess);                                     
	Wire.write(0x1B);                                                          //Start reading @ register 0x1B
	Wire.endTransmission();                                                    //End the transmission
	Wire.requestFrom(MPU_addess, 1);                                           //Request 1 bytes from the gyro
	while(Wire.available() < 1);                                               //Wait until the 6 bytes are received
	if(Wire.read() != 0x08){                                                   //Check if the value is 0x08
		digitalWrite(errorled,HIGH);                                           //Turn on the warning led
		while(1)
		{		
			delay(100);                                                     //Stay in this loop for ever{
			digitalWrite(errorled,HIGH);                                           //Turn on the warning led
			delay(100);                                                     //Stay in this loop for ever
			digitalWrite(errorled,LOW);                                           //Turn on the warning led
		
		}
	}

	Wire.beginTransmission(MPU_addess);                                      
	Wire.write(0x1A);                                                          //We want to write to the CONFIG register (1A hex)
	Wire.write(0x03);                                                          //Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz)
	Wire.endTransmission();                                                    //End the transmission with the gyro
 }

 bool MPU6050Basic::RawRead(void)
 {
	//Read the MPU-6050
	Wire.beginTransmission(MPU_addess);                                   //Start communication with the gyro.
	Wire.write(0x3B);                                                       //Start reading @ register 43h and auto increment with every read.
	Wire.endTransmission();                                                 //End the transmission.
	Wire.requestFrom(MPU_addess,14);                                      //Request 14 bytes from the gyro.
	digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	while(Wire.available() < 14);                                           //Wait until the 14 bytes are received.
	acc_axis[1] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_x variable.
	acc_axis[2] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_y variable.
	acc_axis[3] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_z variable.
	 
	Temperature = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the temperature variable.

	gyro_axis[1] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
	gyro_axis[2] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
	gyro_axis[3] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
	 digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
	if(cal_int == 2000){
		gyro_axis[1] -= gyro_axis_cal[1];                                       //Only compensate after the calibration.
		gyro_axis[2] -= gyro_axis_cal[2];                                       //Only compensate after the calibration.
		gyro_axis[3] -= gyro_axis_cal[3];                                       //Only compensate after the calibration.
	}
	RollRaw =gyro_axis[1];
	NickRaw=gyro_axis[2];
	YawRaw=gyro_axis[3];

	AccX = acc_axis[1];
	AccY= acc_axis[2];
	AccZ = acc_axis[3];
	//gyro_roll = gyro_axis[eeprom_data[28] & 0b00000011];                      //Set gyro_roll to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[28] & 0b10000000)gyro_roll *= -1;                          //Invert gyro_roll if the MSB of EEPROM bit 28 is set.
	//gyro_pitch = gyro_axis[eeprom_data[29] & 0b00000011];                     //Set gyro_pitch to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[29] & 0b10000000)gyro_pitch *= -1;                         //Invert gyro_pitch if the MSB of EEPROM bit 29 is set.
	//gyro_yaw = gyro_axis[eeprom_data[30] & 0b00000011];                       //Set gyro_yaw to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[30] & 0b10000000)gyro_yaw *= -1;                           //Invert gyro_yaw if the MSB of EEPROM bit 30 is set.
	//
	//acc_x = acc_axis[eeprom_data[29] & 0b00000011];                           //Set acc_x to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[29] & 0b10000000)acc_x *= -1;                              //Invert acc_x if the MSB of EEPROM bit 29 is set.
	//acc_y = acc_axis[eeprom_data[28] & 0b00000011];                           //Set acc_y to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[28] & 0b10000000)acc_y *= -1;                              //Invert acc_y if the MSB of EEPROM bit 28 is set.
	//acc_z = acc_axis[eeprom_data[30] & 0b00000011];                           //Set acc_z to the correct axis that was stored in the EEPROM.
	//if(eeprom_data[30] & 0b10000000)acc_z *= -1;                              //Invert acc_z if the MSB of EEPROM bit 30 is set.
	return true;
}

void MPU6050Basic::calculateAngles(double refreshrateHZ)
{
	RawRead();
	//Accelerometer angle calculations
	acc_total_vector = sqrt((AccX*AccX)+(AccY*AccY)+(AccZ*AccZ));       //Calculate the total accelerometer vector.
	
	if(abs(AccY) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
		NickAngle_Acc = asin((float)AccY/acc_total_vector)* 57.296;          //Calculate the pitch angle.
	}
	if(abs(AccX) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
		RollAngle_Acc = asin((float)AccX/acc_total_vector)* -57.296;          //Calculate the roll angle.
	}
	//Place the MPU-6050 spirit level and note the values in the following two lines for calibration.
	NickAngle_Acc += 6.5;                                                   //Accelerometer calibration value for pitch.
	RollAngle_Acc += 2.7;

	RollAngle += (double)RollRaw  * 0.0000611;                                    //Calculate the traveled pitch angle and add this to the angle_pitch variable.
	NickAngle += (double)NickRaw * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.

	//0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
	
	NickAngle -= RollAngle * sin(YawRaw * 0.000001066);                  //If the IMU has yawed transfer the roll angle to the pitch angel.
	RollAngle += NickAngle * sin(YawRaw * 0.000001066);                  //If the IMU has yawed transfer the pitch angle to the roll angel.

	
	
	//Place the MPU-6050 spirit level and note the values in the following two lines for calibration.
	//angle_pitch_acc -= 0.0;                                                   //Accelerometer calibration value for pitch.
	//angle_roll_acc -= 0.0;                                                    //Accelerometer calibration value for roll.
	
	NickAngle = NickAngle * 0.9996 + NickAngle_Acc * 0.0004;            //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
	RollAngle = RollAngle * 0.9996 + RollAngle_Acc * 0.0004;               //Correct the drift of the gyro roll angle with the accelerometer roll angle.

	//pitch_level_adjust = NickAngle * 15;                                    //Calculate the pitch angle correction
	//roll_level_adjust = RollAngle * 15;                                      //Calculate the roll angle correction


	//Euler:
	//Radian: 0.000001066 = 0.0000166 *(PI/180)
	//angel_roll -0 angel_pitch * sin(gyro_z * 0.000001066)
	//angel_pitch -0 angel_roll * sin(gyro_z * 0.000001066)

	
	//refresh_timer = lastRead_timer;
}


 