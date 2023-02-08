/*
 * MPU6050Lib.cpp
 *
 * Created: 05.04.2017 09:05:45
 *  Author: gat
 */ 
 #include <Arduino.h>
 #include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.
 #include <MPU6050Lib.h>

bool MPU6050::begin(int mpu_addess, byte error_led, byte statusled)
{
	MPU6050::MPU_addess = mpu_addess;
	MPU6050::errorled = error_led;
	MPU6050::statusled = statusled;
	gyro_address	= mpu_addess;

	TWBR = 12;                                                                //Set the I2C clock speed to 400kHz.
	isCalibated = false;
	firsttime = true;
	set_gyro_registers();
	return true;
}

void MPU6050::calibrate(void)
{
	gyro_axis_cal[1] =0;
	gyro_axis_cal[2] =0;
	gyro_axis_cal[3] =0;

	for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                           //Take 2000 readings for calibration.
		if(cal_int % 15 == 0)digitalWrite(statusled, !digitalRead(statusled));//Change the led status to indicate calibration.
		raw_read();                                                        //Read the gyro output.
		gyro_axis_cal[1] += gyro_axis[1];                                       //Ad roll value to gyro_roll_cal.
		gyro_axis_cal[2] += gyro_axis[2];                                       //Ad pitch value to gyro_pitch_cal.
		gyro_axis_cal[3] += gyro_axis[3];                                       //Ad yaw value to gyro_yaw_cal.
		delay(5);                                                               //Wait 5 milliseconds before the next loop.
	}

	//Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
	gyro_axis_cal[1] /= 2000.0;                                                 //Divide the roll total by 2000.
	gyro_axis_cal[2] /= 2000.0;                                                 //Divide the pitch total by 2000.
	gyro_axis_cal[3] /= 2000.0;                                                 //Divide the yaw total by 2000.
	isCalibated = true;

	calculateAngles();
}


void MPU6050::set_gyro_registers(void){
	
	 //Setup the MPU-6050
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
	if(Wire.read() != 0x08)	{                                                   //Check if the value is 0x08
		while(true){
			delay(50);                                                       //Stay in this loop for ever
			digitalWrite(errorled, HIGH);                                                   //Turn on the warning led
			delay(100);                                                       //Stay in this loop for ever
			digitalWrite(errorled, LOW);                                                   //Turn on the warning led
		}
	}

	Wire.beginTransmission(gyro_address);                                      //Start communication with the address found during search
	Wire.write(0x1A);                                                          //We want to write to the CONFIG register (1A hex)
	Wire.write(0x03);                                                          //Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz)
	Wire.endTransmission();                                                    //End the transmission with the gyro
}

 bool MPU6050::raw_read(void)
 {
	//Read the MPU-6050
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
	
	if(isCalibated){
		gyro_axis[1] -= gyro_axis_cal[1];                                       //Only compensate after the calibration.
		gyro_axis[2] -= gyro_axis_cal[2];                                       //Only compensate after the calibration.
		gyro_axis[3] -= gyro_axis_cal[3];                                       //Only compensate after the calibration.
	}
	gyro_roll =gyro_axis[1];
	gyro_pitch=gyro_axis[2];
	gyro_yaw=gyro_axis[3];

	acc_x = acc_axis[1];
	acc_y = acc_axis[2];
	acc_z = acc_axis[3];
	return true;
}

void MPU6050::calculateAngles()
{
	raw_read();
	//Gyro angle calculations
	//0.0000611 = 1 / (250Hz / 65.5)
	angle_pitch += gyro_pitch * 0.0000611;                                    //Calculate the traveled pitch angle and add this to the angle_pitch variable.
	angle_roll += gyro_roll * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.

	//0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
	angle_pitch -= angle_roll * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the roll angle to the pitch angel.
	angle_roll += angle_pitch * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the pitch angle to the roll angel.

	//Accelerometer angle calculations
	acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));       //Calculate the total accelerometer vector.
	
	if(abs(acc_y) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
		angle_roll_acc = asin((float)acc_y/acc_total_vector)* 57.296;          //Calculate the pitch angle.
	}
	if(abs(acc_x) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
		angle_pitch_acc = asin((float)acc_x/acc_total_vector)* -57.296;          //Calculate the roll angle.
	}
	if (firsttime)
	{
		angle_pitch = angle_pitch_acc;
		angle_roll = angle_roll_acc;
		firsttime= false;
	}
	//Place the MPU-6050 spirit level and note the values in the following two lines for calibration.
	angle_pitch_acc -= 0.0;                                                   //Accelerometer calibration value for pitch.
	angle_roll_acc -= 0.0;                                                    //Accelerometer calibration value for roll.
	
	angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;            //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
	angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;
}


 