/*----------------------------------------------------------------------*
 * I2CSensor.h - Arduino library FT-Sensor version 20160408					    *
 *----------------------------------------------------------------------*/ 

#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H


#include <Arduino.h> 

//Default I2C Address of the sensor
#define SENSOR_DEFAULT_ADDR 					0x71

//Sensor Register Addresses
#define SENSOR_GET_CAPACITANCE_PROZ		0x00 // (r) 	2 bytes
#define SENSOR_GET_CAPACITANCE				0x01 // (r) 	2 bytes

#define SENSOR_SET_ADDRESS 						0x02 //	(w) 	1 byte
#define SENSOR_GET_ADDRESS 						0x03 // (r) 	1 byte

#define SENSOR_SET_CALIBRATE_HIGH			0x04 //	(w) 	n/a
#define SENSOR_GET_CALIBRATE_HIGH			0x05 //	(w) 	n/a

#define SENSOR_SET_CALIBRATE_LOW			0x06 //	(r) 	2 bytes
#define SENSOR_GET_CALIBRATE_LOW			0x07 //	(r) 	2 bytes

#define SENSOR_GET_TEMPERATURE				0x08 //	(r) 	2 bytes

#define SENSOR_SET_ALARM_ON						0x09 //	(w) 	1 byte
#define SENSOR_GET_ALARM_ON						0x0A //	(r) 	1 byte
#define SENSOR_SET_ALARM_OFF					0x0B //	(w) 	1 byte
#define SENSOR_GET_ALARM_OFF					0x0C //	(r) 	1 byte

#define SENSOR_RESET 									0x0D //	(w) 	n/a
#define SENSOR_GET_VERSION 						0x0E //	(r) 	1 bytes

#define SENSOR_GET_VCC								0x0F // (r) 	2 bytes

#define SENSOR_GET_SW									0x10 // (r) 	2 bytes

class I2CSensor {
    public:
        I2CSensor(uint8_t addr = SENSOR_DEFAULT_ADDR);

		void begin(bool wait = false);
        unsigned int getCapacitance();
        unsigned int getCapacitanceProz();
        
        unsigned int getVCC();
        
        bool setCalibrateHigh(unsigned int = 0);
        unsigned int getCalibrateHigh();
        
        bool setCalibrateLow(unsigned int = 0);
        unsigned int getCalibrateLow();

        int getTemperature();

        bool setAddress(int addr, bool reset);
        uint8_t getAddress();
        void changeAddress(int addr, bool wait = false);
        
        bool setAlarmOn(int alarm);
        uint8_t getAlarmOn();
        bool setAlarmOff(int alarm);
        uint8_t getAlarmOff();

        void restart();
        uint8_t getVersion();
        
        uint8_t getSwitch();

    private:
		int sensorAddress;

        void writeI2CRegister_8(int addr, int value);
        void writeI2CRegister_8(int addr, int reg, int value);
        uint8_t readI2CRegister_8(int addr, int reg);
        
        unsigned int readI2CRegister_U16(int addr, int reg);
        int readI2CRegister_16(int addr, int reg);
};

#endif
