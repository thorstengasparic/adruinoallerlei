
#include "Arduino.h"
#include "I2Cdev.h"
#include "Wire.h"



#define MPU9250_ADDRESS 0x68  // Device address
#define INT_PIN_CFG      0x37
#define WHO_AM_I_MPU9250 0x75 // Should return 0x71

enum Mscale {
	MFS_14BITS = 0, // 0.6 mG per LSB
	MFS_16BITS = 1     // 0.15 mG per LSB
};
#define AK8963_ADDRESS   0x0C
#define AK8963_WHO_AM_I  0x00 // should return 0x48
#define AK8963_INFO      0x01
#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_XOUT_L	 0x03  // data
#define AK8963_XOUT_H	 0x04
#define AK8963_YOUT_L	 0x05
#define AK8963_YOUT_H	 0x06
#define AK8963_ZOUT_L	 0x07
#define AK8963_ZOUT_H	 0x08
#define AK8963_ST2       0x09  // Data overflow bit 3 and data read error status bit 2
#define AK8963_CNTL      0x0A  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_ASTC      0x0C  // Self test control
#define AK8963_I2CDIS    0x0F  // I2C disable
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY      0x11  // Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ      0x12  // Fuse ROM z-axis sensitivity adjustment value


double magCalibration[3] = {1.0, 1.0, 1.0};
float zeroPointCorrection[3] = {133, 122, -162};
float scaleCorrection[3] = {1.0, 1.0, 1.0};

float mag_axis[3];

double MagX, MagY, MagZ;
unsigned long loop_timer;

struct LUCFILTER
{
	double prevValue;
	double noiseParameter;
	double noiseParameterSen;
	double lowpass;
};
LUCFILTER filter[3];

double noiseFilter(LUCFILTER *filter, double valin ) 
{
	//Serial.print("prev:");
	//Serial.print(filter->prevValue);
	//Serial.print(" p1:");
	//Serial.print(filter->noiseParameter);
	//Serial.print(" p1:");
	//Serial.print(filter->noiseParameterSen);
	//Serial.print(" val:");
	//Serial.print(valin);

	if (valin < filter->prevValue - filter->noiseParameter | valin > filter->prevValue + filter->noiseParameter) 
	{
		filter->prevValue = valin;
	} 
	else 
	{
		if (valin < filter->prevValue - filter->noiseParameterSen | valin > filter->prevValue + filter->noiseParameterSen) 
		{
			filter->prevValue = (filter->prevValue + valin) / 2;
		} 
		else 
		{
			filter->prevValue = ((double)((1.0 - filter->lowpass) * filter->prevValue+ filter->lowpass * valin));
		}
	}
	//Serial.print(" ret:");
	//Serial.println(filter->prevValue);
	return filter->prevValue;
}
	


void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
	Wire.beginTransmission(address);  // Initialize the Tx buffer
	Wire.write(subAddress);           // Put slave register address in Tx buffer
	Wire.write(data);                 // Put data in Tx buffer
	Wire.endTransmission();           // Send the Tx buffer
}

uint8_t readByte(uint8_t address, uint8_t subAddress)
{
	uint8_t data; // `data` will store the register data
	Wire.beginTransmission(address);         // Initialize the Tx buffer
	Wire.write(subAddress);	                 // Put slave register address in Tx buffer
	Wire.endTransmission();        // Send the Tx buffer, but send a restart to keep connection alive
	//	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
	//	Wire.requestFrom(address, 1);  // Read one byte from slave register address
	Wire.requestFrom(address, (size_t) 1);  // Read one byte from slave register address
	data = Wire.read();                      // Fill Rx buffer with result
	return data;                             // Return data read from slave register
}

void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest)
{
	Wire.beginTransmission(address);   // Initialize the Tx buffer
	Wire.write(subAddress);            // Put slave register address in Tx buffer
	Wire.endTransmission();  // Send the Tx buffer, but send a restart to keep connection alive
	//	Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
	uint8_t i = 0;
	//        Wire.requestFrom(address, count);  // Read bytes from slave register address
	Wire.requestFrom(address, (size_t) count);  // Read bytes from slave register address
	while (Wire.available()) {
	dest[i++] = Wire.read(); }         // Put read results in the Rx buffer
}

void initAK8963(double * calibration, Mscale mscale)
{
	// First extract the factory calibration for each magnetometer axis
	uint8_t rawData[3];  // x/y/z gyro calibration data stored here
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	delay(10);
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
	delay(10);
	readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
	calibration[0] =  (float)(rawData[0] - 128)/256.0 + 1.0;   // Return x-axis sensitivity adjustment values, etc.
	calibration[1] =  (float)(rawData[1] - 128)/256.0 + 1.0;
	calibration[2] =  (float)(rawData[2] - 128)/256.0 + 1.0;
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	delay(10);
	// Configure the magnetometer for continuous read and highest resolution
	// set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
	// and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
	uint8_t Mmode = 0x06;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read
	writeByte(AK8963_ADDRESS, AK8963_CNTL, mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
	delay(10);
}

bool readMagData()
{
	uint8_t rawData[7];  // x/y/z gyro register data, ST2 register stored here, must read ST2 at end of data acquisition
	if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01) { // wait for magnetometer data ready bit to be set
		readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);  // Read the six raw data and ST2 registers sequentially into data array
		uint8_t c = rawData[6]; // End data read by reading ST2 register
		if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
			mag_axis[0]  = ((int16_t)rawData[1] << 8) | rawData[0] ;  // Turn the MSB and LSB into a signed 16-bit value
			mag_axis[1]  = ((int16_t)rawData[3] << 8) | rawData[2] ;  // Data stored as little Endian
			mag_axis[2]  = ((int16_t)rawData[5] << 8) | rawData[4] ;
			
			double mRes = 4912.0/32760.0;
			MagX = (double)(mag_axis[0]-zeroPointCorrection[0])*scaleCorrection[0] * magCalibration[0]*mRes;
			MagY = (double)(mag_axis[1]-zeroPointCorrection[1])*scaleCorrection[1] * magCalibration[1]*mRes;
			MagZ = (double)(mag_axis[2]-zeroPointCorrection[2])*scaleCorrection[2] * magCalibration[2]*mRes;
			return true;
		}
	}
	return false;
}

void magcalMPU9250(float * zeroPointCorrection, float * scaleCorrection)
{
	int32_t mag_bias[3] = {0, 0, 0};
	int32_t mag_scale[3] = {0, 0, 0};
	int16_t mag_max[3] = {0x8000, 0x8000, 0x8000};
	int16_t mag_min[3] = {0x7FFF, 0x7FFF, 0x7FFF};
	//int16_t mag_temp[3] = {0, 0, 0};

	Serial.println("Mag Calibration: Wave device in a figure eight until done!");
	delay(1000);

	uint16_t ii = 0;
	uint16_t sample_count = 400;
	while (true)
	{
		if (readMagData())
		{
			for (int jj = 0; jj < 3; jj++) {
				if(mag_axis[jj] > mag_max[jj]) mag_max[jj] = mag_axis[jj];
				if(mag_axis[jj] < mag_min[jj]) mag_min[jj] = mag_axis[jj];
			}
			ii++;
		}
		delay(20);  // at 8 Hz ODR, new mag data is available every 125 ms
		Serial.print(".");
		if (ii>sample_count) break;
	}
	Serial.println(".");
	// Get hard iron correction
	mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
	mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
	mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts
	//Serial.println("aaaaaaaa");
	//double mRes = 4912.0/32760.0;
	zeroPointCorrection[0] = (double) mag_bias[0];//* magCalibration[0]*mRes;
	zeroPointCorrection[1] = (double) mag_bias[1];//* magCalibration[0]*mRes;
	zeroPointCorrection[2] = (double) mag_bias[2];//* magCalibration[0]*mRes;
	
	// Get soft iron correction estimate
	mag_scale[0]  = (mag_max[0] - mag_min[0])/2;  // get average x axis max chord length in counts
	mag_scale[1]  = (mag_max[1] - mag_min[1])/2;  // get average y axis max chord length in counts
	mag_scale[2]  = (mag_max[2] - mag_min[2])/2;  // get average z axis max chord length in counts

	float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
	avg_rad /= 3.0;
	//Serial.println("BBBBBB");
	scaleCorrection[0] = avg_rad/((float)mag_scale[0]);
	scaleCorrection[1] = avg_rad/((float)mag_scale[1]);
	scaleCorrection[2] = avg_rad/((float)mag_scale[2]);

	Serial.println("Mag Calibration done!");
}


void xyCalibrate(double * calibrate)
{
	double mag_bias[3] = {0.0, 0.0, 0.0};

	Serial.println("Mag Calibration: press key to start....");
	while (true)
	{
		if (Serial.available() > 0) {
			Serial.read();
			break;
		}
		delay(10);
	}
	Serial.println("Wait....");
	uint16_t sample_count = 200;

	uint16_t ii = 0;
	while (true)
	{
		if (readMagData())
		{
			for (int jj = 0; jj < 3; jj++) {
				mag_bias[jj] += mag_axis[jj];
			}
			ii++;
		}
		delay(50);  // at 8 Hz ODR, new mag data is available every 125 ms
		//Serial.println(ii);
		if (ii>sample_count) break;
	}
	Serial.println("Turn 180 dgree: press key to start....");
	while (true)
	{
		if (Serial.available() > 0) {
			Serial.read();
			break;
		}
		delay(10);
	}
	Serial.println("Wait....");
	ii = 0;
	while (true)
	{
		if (readMagData())
		{
			for (int jj = 0; jj < 3; jj++) {
				mag_bias[jj] += mag_axis[jj];
			}
			ii++;
		}
		delay(50);  // at 8 Hz ODR, new mag data is available every 125 ms
		//Serial.println(ii);
		if (ii>sample_count) break;
	}

	calibrate[0] = mag_bias[0] /((double)sample_count * 2.0);
	calibrate[1] = mag_bias[1] /((double)sample_count * 2.0);
	calibrate[2] = mag_bias[2] /((double)sample_count * 2.0);
}


void _setup() {
	Serial.begin(115200);

	Wire.begin();//I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
	TWBR = 12;
	//pinMode(SDA, INPUT);
	//pinMode(SCL, INPUT);

    Serial.println("MPU9250 + MPL3115A2 devices...");
    byte c = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
    Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX); Serial.print(" I should be "); Serial.println(0x73, HEX);

	//INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=1 ; CLKOUT_EN=0
	writeByte(MPU9250_ADDRESS, INT_PIN_CFG	, 0x02);



	byte d = readByte(AK8963_ADDRESS, AK8963_WHO_AM_I);  // Read WHO_AM_I register for AK8963
	Serial.print("AK8963 "); Serial.print("I AM "); Serial.println(d, HEX);

	initAK8963(magCalibration, MFS_16BITS);
	Serial.print("cx:"); Serial.print(magCalibration[0]);
	Serial.print("\tcx:"); Serial.print(magCalibration[1]);
	Serial.print("\tcz:"); Serial.println(magCalibration[2]);

	magcalMPU9250(zeroPointCorrection, scaleCorrection);
	Serial.print("  zPX"); Serial.print(zeroPointCorrection[0]);
	Serial.print("\tzPY:"); Serial.print(zeroPointCorrection[1]);
	Serial.print("\tzPZ:"); Serial.println(zeroPointCorrection[2]);
	Serial.print("  sPX"); Serial.print(scaleCorrection[0]);
	Serial.print("\tsPY:"); Serial.print(scaleCorrection[1]);
	Serial.print("\tsPZ:"); Serial.println(scaleCorrection[2]);

  pinMode(LED_BUILTIN, OUTPUT);
  loop_timer = micros();                                                    //Set the timer for the next loop.
  
  while (!readMagData()){}
  filter[0].prevValue = MagX;
  filter[0].lowpass = 0.055;
  filter[0].noiseParameter = 12.0;
  filter[0].noiseParameterSen = 6.0;

  filter[1].prevValue = MagY;
  filter[1].lowpass = filter[0].lowpass;
  filter[1].noiseParameter = filter[0].noiseParameter;
  filter[1].noiseParameterSen = filter[0].noiseParameterSen;
}

double xycalibrate[3];

void _loop() 
{

	if(micros() - loop_timer > 4050)digitalWrite(LED_BUILTIN, HIGH);                   //Turn on the LED if the loop time exceeds 4050us.

	while(micros() - loop_timer < 4000);                                      //We wait until 4000us are passed.
	loop_timer = micros();                                                    //Set the timer for the next loop.

	//magcalMPU9250(zeroPointCorrection, scaleCorrection);
	//Serial.print("  zPX"); Serial.print(zeroPointCorrection[0]);
	//Serial.print("\tzPY:"); Serial.print(zeroPointCorrection[1]);
	//Serial.print("\tzPZ:"); Serial.println(zeroPointCorrection[2]);
	//Serial.print("  sPX"); Serial.print(scaleCorrection[0]);
	//Serial.print("\tsPY:"); Serial.print(scaleCorrection[1]);
	//Serial.print("\tsPZ:"); Serial.println(scaleCorrection[2]);
	
	//xyCalibrate(xycalibrate);
	//Serial.print("  clX"); Serial.print(xycalibrate[0]);
	//Serial.print("\tclY:"); Serial.print(xycalibrate[1]);
	//Serial.print("\tclZ:"); Serial.println(xycalibrate[2]);
	//return;

	if (readMagData())
	{

		MagX = noiseFilter(&(filter[0]), MagX ); 
		MagY = noiseFilter(&(filter[1]), MagY ); 
		Serial.print("x:"); Serial.print(MagX);
		Serial.print("\ty:"); Serial.print(MagY);
		Serial.print("\tz:"); Serial.print(MagZ);

		double dreg= 0;
		if (MagY != 0)			dreg = atan2(MagX,MagY)*180/3.141;
		if (0 == MagY  && MagX<0)dreg= 180;
		if (0 == MagY && MagX>0)dreg= 0;
		if (dreg <0) dreg += 360;

		Serial.print("\tdreg:"); Serial.print(dreg);

		double totalMag = sqrt(MagX*MagX+ MagY*MagY + MagZ*MagZ);
		Serial.print("\tt:"); Serial.print(totalMag);

		Serial.println();
	}
	//Serial.print("st1:"); Serial.println(readByte(AK8963_ADDRESS, AK8963_ST1));

}


