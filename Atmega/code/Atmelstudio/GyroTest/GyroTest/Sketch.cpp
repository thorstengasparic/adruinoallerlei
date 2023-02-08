#include "Arduino.h"
#include "I2Cdev.h"
#include "Wire.h"

#include "MathVector.h"

class Mpu
{
	public:
	byte adress;
	MpuVector raw_accelerometer;
	MpuVector accelerometer;
	MpuVector gyorscope ;
	int temperature;
	void calComplementary(double delta)
	{
		if (delta != 0.0)
		{
			accelerometer.x = accelerometer.x * (1-delta) + raw_accelerometer.x * delta;
			accelerometer.y = accelerometer.y * (1-delta) + raw_accelerometer.y * delta;
			accelerometer.z = accelerometer.z * (1-delta) + raw_accelerometer.z * delta;
		}
		else
		{
			accelerometer.x = raw_accelerometer.x;
			accelerometer.y = raw_accelerometer.y;
			accelerometer.z = raw_accelerometer.z;
		}
	}
};

void read_mpu_6050_data(Mpu *mpu);
void setup_mpu_6050_registers(Mpu mpu);

void printVaulue();
void write_LCD();

#include <Wire.h>


//Declaring some global variables
Mpu mpu01;
Mpu mpu02;

double angle = 0;
double angle_out = 0;
boolean init_angles;
double acc_total_vector;

long loop_timer;
int lcd_loop_counter;


void setup() {
	Wire.begin();                                                        //Start I2C as master
	Serial.begin(115200);                                               //Use only for debugging

	Serial.print("Init()");
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);                                               //All done, turn the LED off

	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);                                               //All done, turn the LED off
	

	mpu01.adress = 0x68;
	setup_mpu_6050_registers(mpu01);                                      
	read_mpu_6050_data(&mpu01);    
	
	mpu01.accelerometer.x = mpu01.raw_accelerometer.x;
	mpu01.accelerometer.y = mpu01.raw_accelerometer.y;
	mpu01.accelerometer.z = mpu01.raw_accelerometer.z;

	mpu02.adress = 0x69;
	setup_mpu_6050_registers(mpu02);                                         
	read_mpu_6050_data(&mpu02);    
	
	mpu02.accelerometer.x = mpu02.raw_accelerometer.x;
	mpu02.accelerometer.y = mpu02.raw_accelerometer.y;
	mpu02.accelerometer.z = mpu02.raw_accelerometer.z;
	Serial.print("Start()");
}


long cnt =0;
void loop(){

	read_mpu_6050_data(&mpu01);    
	mpu01.calComplementary(0.05);


	read_mpu_6050_data(&mpu02);    
	mpu02.calComplementary(0.05);

	angle = mpu01.accelerometer.angle(mpu02.accelerometer);
	angle_out = angle_out * 0.99 + angle *0.01;
	cnt++;
	//Serial.print(mpu01.accelerometer.x);
	//Serial.print("\t");
	//Serial.print(mpu01.accelerometer.y);
	//Serial.print("\t");
	//Serial.print(mpu01.accelerometer.z);
	//Serial.print("\t");
//
	//Serial.print(mpu02.accelerometer.x);
	//Serial.print("\t");
	//Serial.print(mpu02.accelerometer.y);
	//Serial.print("\t");
	//Serial.print(mpu02.accelerometer.z);
	//Serial.print("\t");
//
//
	//Serial.print(mpu01.accelerometer.absolut());
	//Serial.print("\t");
	//Serial.print(mpu02.accelerometer.absolut());
	//Serial.print("\t");
	//Serial.print(mpu01.accelerometer.skalarprodukt(mpu02.accelerometer));
	//Serial.print("\t");
	//Serial.println(angle);

	
	
	printVaulue();
}

int prntCnt = 0;
void printVaulue()
{
	//if (prntCnt == 1) Serial.print("p=");
	//if (prntCnt == 20) Serial.print(mpu01.accelerometer.pitch());
	//if (prntCnt == 30) Serial.print("\tr=");
	//if (prntCnt == 40) Serial.print(mpu01.accelerometer.roll());
	//if (prntCnt == 50) Serial.print("\tp=");
	//if (prntCnt == 60) Serial.print(mpu02.accelerometer.pitch());
	//if (prntCnt == 70) Serial.print("\tr=");
	//if (prntCnt == 80) Serial.print(mpu02.accelerometer.roll());
	if (prntCnt == 90) Serial.print("\tw=");
	if (prntCnt == 100) Serial.print(angle);
	if (prntCnt == 110) Serial.print("\two=");
	if (prntCnt == 120) Serial.print(angle_out);
	if (prntCnt == 130) Serial.print("\tc=");
	if (prntCnt == 140) Serial.println(cnt);

	if (prntCnt > 150) prntCnt = 0;
	prntCnt++;
}
void setup_mpu_6050_registers(Mpu mpu){

	byte mpuAdr = mpu.adress;
	//Activate the MPU-6050
	Wire.beginTransmission(mpuAdr);                               
	Wire.write(0x6B);                                             
	Wire.write(0x00);                                             
	Wire.endTransmission();                                       
	//Configure the accelerometer (+/-8g)
	Wire.beginTransmission(mpuAdr);                               
	Wire.write(0x1C);                                             
	Wire.write(0x10);                                             
	Wire.endTransmission();                                       
	//Configure the gyro (500dps full scale)
	Wire.beginTransmission(mpuAdr);                               
	Wire.write(0x1B);                                             
	Wire.write(0x08);                                             
	Wire.endTransmission();                                       
}

void read_mpu_6050_data(Mpu *mpu){                              
	Wire.beginTransmission(mpu->adress);                
	Wire.write(0x3B);                                             
	Wire.endTransmission();                                       
	Wire.requestFrom(mpu->adress,6);                   
	while(Wire.available() < 6);                                 
	mpu->raw_accelerometer.x  = (double)(Wire.read()<<8|Wire.read());                 ;
	mpu->raw_accelerometer.y  = (double)(Wire.read()<<8|Wire.read());                 
	mpu->raw_accelerometer.z  = (double)(Wire.read()<<8|Wire.read());                 
	mpu->temperature = (int)(Wire.read()<<8|Wire.read());                 
	mpu->gyorscope.x  = (double)(Wire.read()<<8|Wire.read());                 
	mpu->gyorscope.y  = (double)(Wire.read()<<8|Wire.read());                 
	mpu->gyorscope.z  = (double)(Wire.read()<<8|Wire.read());                 
}








