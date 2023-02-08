/*
 * AL_Gyro.cpp
 *
 * Created: 20.04.2017 19:26:43
 *  Author: gat
 */ 
#include "AL-Common.h"
#include "AL-Gyro.h"
#include "AL-Eprom.h"

int gyro_address = GYRO_ADDRESS;

boolean first_angle;

int temperature;
long acc_x, acc_y, acc_z;
long acc_total_vector[20];
long acc_av_vector;

int acc_axis[4];
int gyro_axis[4];
double gyro_pitch, gyro_roll, gyro_yaw;
float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll;

int cal_int;
double gyro_axis_cal[4];

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //Subroutine for reading the gyro
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void gyro_signalen(){
	 //Read the MPU-6050
	 if(eeprom_data[31] == 1){
		 Wire.beginTransmission(gyro_address);                                   //Start communication with the gyro.
		 Wire.write(0x3B);                                                       //Start reading @ register 43h and auto increment with every read.
		 Wire.endTransmission();                                                 //End the transmission.
		 Wire.requestFrom(gyro_address,14);                                      //Request 14 bytes from the gyro.
		 
		 while(Wire.available() < 14);                                           //Wait until the 14 bytes are received.
		 acc_axis[1] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_x variable.
		 acc_axis[2] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_y variable.
		 acc_axis[3] = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the acc_z variable.
		 temperature = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the temperature variable.
		 gyro_axis[1] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
		 gyro_axis[2] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
		 gyro_axis[3] = Wire.read()<<8|Wire.read();                              //Read high and low part of the angular data.
	 }

	 if(cal_int == 2000){
		 gyro_axis[1] -= gyro_axis_cal[1];                                       //Only compensate after the calibration.
		 gyro_axis[2] -= gyro_axis_cal[2];                                       //Only compensate after the calibration.
		 gyro_axis[3] -= gyro_axis_cal[3];                                       //Only compensate after the calibration.
	 }
	 if(eeprom_ok)
	 {
		 gyro_roll = gyro_axis[eeprom_data[28] & 0b00000011];                      //Set gyro_roll to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[28] & 0b10000000)gyro_roll *= -1;                          //Invert gyro_roll if the MSB of EEPROM bit 28 is set.
		 gyro_pitch = gyro_axis[eeprom_data[29] & 0b00000011];                     //Set gyro_pitch to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[29] & 0b10000000)gyro_pitch *= -1;                         //Invert gyro_pitch if the MSB of EEPROM bit 29 is set.
		 gyro_yaw = gyro_axis[eeprom_data[30] & 0b00000011];                       //Set gyro_yaw to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[30] & 0b10000000)gyro_yaw *= -1;                           //Invert gyro_yaw if the MSB of EEPROM bit 30 is set.
	 
		 acc_x = acc_axis[eeprom_data[29] & 0b00000011];                           //Set acc_x to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[29] & 0b10000000)acc_x *= -1;                              //Invert acc_x if the MSB of EEPROM bit 29 is set.
		 acc_y = acc_axis[eeprom_data[28] & 0b00000011];                           //Set acc_y to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[28] & 0b10000000)acc_y *= -1;                              //Invert acc_y if the MSB of EEPROM bit 28 is set.
		 acc_z = acc_axis[eeprom_data[30] & 0b00000011];                           //Set acc_z to the correct axis that was stored in the EEPROM.
		 if(eeprom_data[30] & 0b10000000)acc_z *= -1;                              //Invert acc_z if the MSB of EEPROM bit 30 is set.
	 }
	 else{
		 gyro_roll = gyro_axis[1];           //Set gyro_roll to the correct axis that was stored in the EEPROM.
		 gyro_pitch = gyro_axis[2];          //Set gyro_pitch to the correct axis that was stored in the EEPROM.
		 gyro_yaw = gyro_axis[3];            //Set gyro_yaw to the correct axis that was stored in the EEPROM.

		 acc_x = acc_axis[1];                //Set acc_x to the correct axis that was stored in the EEPROM.
		 acc_y = acc_axis[2];                //Set acc_y to the correct axis that was stored in the EEPROM.
		 acc_z = acc_axis[3];                //Set acc_z to the correct axis that was stored in the EEPROM.
	}
 }

 void InitGyro(){
	 //Setup the MPU-6050
	 gyro_address = GYRO_ADDRESS;

	 if(eeprom_data[31] == 1){
		 Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search.
		 Wire.write(0x6B);                                                          //We want to write to the PWR_MGMT_1 register (6B hex)
		 Wire.write(0x00);                                                          //Set the register bits as 00000000 to activate the gyro
		 Wire.endTransmission();                                                    //End the transmission with the gyro.

		 Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search.
		 Wire.write(0x1B);                                                          //We want to write to the GYRO_CONFIG register (1B hex)
		 Wire.write(0x08);                                                          //Set the register bits as 00001000 (500dps full scale)
		 Wire.endTransmission();                                                    //End the transmission with the gyro

		 Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search.
		 Wire.write(0x1C);                                                          //We want to write to the ACCEL_CONFIG register (1A hex)
		 Wire.write(0x10);                                                          //Set the register bits as 00010000 (+/- 8g full scale range)
		 Wire.endTransmission();                                                    //End the transmission with the gyro

		 //Let's perform a random register check to see if the values are written correct
		 Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search
		 Wire.write(0x1B);                                                          //Start reading @ register 0x1B
		 Wire.endTransmission();                                                    //End the transmission
		 Wire.requestFrom(gyro_address, 1);                                         //Request 1 bytes from the gyro
		 while(Wire.available() < 1);                                               //Wait until the 6 bytes are received
		 if(Wire.read() != 0x08){                                                   //Check if the value is 0x08
			BlinkSignal(ERROR_GYROSET, false);			 
		 }

		 Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search
		 Wire.write(0x1A);                                                          //We want to write to the CONFIG register (1A hex)
		 Wire.write(0x03);                                                          //Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz)
		 Wire.endTransmission();                                                    //End the transmission with the gyro

	 }
 }

void gyro_calibrate(void)
{ 	
	cal_int =0;
 	Serial.print("Calibrating the gyro");
 	//Let's take multiple gyro data samples so we can determine the average gyro offset (calibration).
 	for (cal_int = 0; cal_int < 2000 ; cal_int ++)
	{                                   //Take 2000 readings for calibration.
 		if(cal_int % 125 == 0){
 			digitalWrite(LED_STATUS_PIN, !digitalRead(LED_STATUS_PIN));   //Change the led status to indicate calibration.
 			Serial.print(".");
 		}
 		gyro_signalen();                                                                //Read the gyro output.
 		gyro_axis_cal[1] += gyro_axis[1];                                               //Ad roll value to gyro_roll_cal.
 		gyro_axis_cal[2] += gyro_axis[2];                                               //Ad pitch value to gyro_pitch_cal.
 		gyro_axis_cal[3] += gyro_axis[3];                                               //Ad yaw value to gyro_yaw_cal.
	} 	
 	Serial.println(".");
 	//Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
 	gyro_axis_cal[1] /= 2000;                                                         //Divide the roll total by 2000.
 	gyro_axis_cal[2] /= 2000;                                                         //Divide the pitch total by 2000.
 	gyro_axis_cal[3] /= 2000;                                                         //Divide the yaw total by 2000.
	first_angle = true;
}


void gyro_calculate(void)
{
	//Gyro angle calculations
	//0.0000611 = 1 / (250Hz / 65.5)
	angle_pitch += gyro_pitch * 0.0000611;                                           //Calculate the traveled pitch angle and add this to the angle_pitch variable.
	angle_roll += gyro_roll * 0.0000611;                                             //Calculate the traveled roll angle and add this to the angle_roll variable.
	
	//0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
	angle_pitch -= angle_roll * sin(gyro_yaw * 0.000001066);                         //If the IMU has yawed transfer the roll angle to the pitch angel.
	angle_roll += angle_pitch * sin(gyro_yaw * 0.000001066);                         //If the IMU has yawed transfer the pitch angle to the roll angel.
	
	//Accelerometer angle calculations
	acc_total_vector[0] = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));           //Calculate the total accelerometer vector.
	
	//57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
	angle_pitch_acc = asin((float)acc_y/acc_total_vector[0])* 57.296;                //Calculate the pitch angle.
	angle_roll_acc = asin((float)acc_x/acc_total_vector[0])* -57.296;                //Calculate the roll angle.
	if(abs(acc_y) < acc_total_vector[0]){                                        //Prevent the asin function to produce a NaN
		angle_roll_acc = asin((float)acc_y/acc_total_vector[0])* 57.296;          //Calculate the pitch angle.
	}
	if(abs(acc_x) < acc_total_vector[0]){                                        //Prevent the asin function to produce a NaN
		angle_pitch_acc = asin((float)acc_x/acc_total_vector[0])* -57.296;          //Calculate the roll angle.
	}
	
	if(!first_angle){
		angle_pitch = angle_pitch_acc;                                                 //Set the pitch angle to the accelerometer angle.
		angle_roll = angle_roll_acc;                                                   //Set the roll angle to the accelerometer angle.
		first_angle = true;
	}
	else{
		angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;                 //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
		angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;                    //Correct the drift of the gyro roll angle with the accelerometer roll angle.
	}
}


