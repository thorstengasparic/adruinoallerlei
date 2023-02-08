/*----------------------------------------------------------------------*
 * I2CSensor.cpp - Arduino library FT-Sensor version 20160408					  *
 *----------------------------------------------------------------------*/ 

#include "I2CSensor_std.h"

#if defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
	#include <TinyWireM.h>
	#define i2cBegin TinyWireM.begin
	#define i2cBeginTransmission TinyWireM.beginTransmission
	#define i2cEndTransmission TinyWireM.endTransmission
	#define i2cRequestFrom TinyWireM.requestFrom
	#define i2cRead TinyWireM.receive
	#define i2cWrite TinyWireM.send
#elif ARDUINO >= 100
	#include <Wire.h>
	#define i2cBegin Wire.begin
	#define i2cBeginTransmission Wire.beginTransmission
	#define i2cEndTransmission Wire.endTransmission
	#define i2cRequestFrom Wire.requestFrom
	#define i2cRead Wire.read
	#define i2cWrite Wire.write
#else
	#include <Wire.h>
	#define i2cBegin Wire.begin
	#define i2cBeginTransmission Wire.beginTransmission
	#define i2cEndTransmission Wire.endTransmission
	#define i2cRequestFrom Wire.requestFrom
	#define i2cRead Wire.receive
	#define i2cWrite Wire.send
#endif

/*----------------------------------------------------------------------*/
I2CSensor::I2CSensor(uint8_t addr) : sensorAddress(addr) {
}
  
/*----------------------------------------------------------------------*/
void I2CSensor::begin(bool wait) {
  restart();
  if (wait) {
    delay(1000);
  }
}

/*----------------------------------------------------------------------*/
unsigned int I2CSensor::getCapacitanceProz() {
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CAPACITANCE_PROZ);
}
/*----------------------------------------------------------------------*/
unsigned int I2CSensor::getCapacitance() {
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CAPACITANCE);
}
/*----------------------------------------------------------------------*/
bool I2CSensor::setCalibrateHigh(unsigned int value) {
  writeI2CRegister_8(sensorAddress, SENSOR_SET_CALIBRATE_HIGH);
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CALIBRATE_HIGH);
}
/*----------------------------------------------------------------------*/
unsigned int I2CSensor::getCalibrateHigh() {
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CALIBRATE_HIGH);	
}
/*----------------------------------------------------------------------*/
bool I2CSensor::setCalibrateLow(unsigned int value) {
  writeI2CRegister_8(sensorAddress, SENSOR_SET_CALIBRATE_LOW);
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CALIBRATE_LOW);
}
/*----------------------------------------------------------------------*/
unsigned int I2CSensor::getCalibrateLow() {
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_CALIBRATE_LOW);	
}
/*----------------------------------------------------------------------*/
unsigned int I2CSensor::getVCC() {
  return readI2CRegister_U16(sensorAddress, SENSOR_GET_VCC);
}
/*----------------------------------------------------------------------*/
int I2CSensor::getTemperature() {
  return readI2CRegister_16(sensorAddress, SENSOR_GET_TEMPERATURE);
}
/*----------------------------------------------------------------------*/
bool I2CSensor::setAlarmOn(int alarm) {
  writeI2CRegister_8(sensorAddress, SENSOR_SET_ALARM_ON, alarm);
  return (readI2CRegister_8(sensorAddress, SENSOR_GET_ALARM_ON) == alarm);
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::getAlarmOn() {
  return readI2CRegister_8(sensorAddress, SENSOR_GET_ALARM_ON);
}
/*----------------------------------------------------------------------*/
bool I2CSensor::setAlarmOff(int alarm) {
  writeI2CRegister_8(sensorAddress, SENSOR_SET_ALARM_OFF, alarm);
  return (readI2CRegister_8(sensorAddress, SENSOR_GET_ALARM_OFF) == alarm);
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::getAlarmOff() {
  return readI2CRegister_8(sensorAddress, SENSOR_GET_ALARM_OFF);
}
/*----------------------------------------------------------------------*/
bool I2CSensor::setAddress(int addr, bool reset) {
  writeI2CRegister_8(sensorAddress, SENSOR_SET_ADDRESS, addr);
  if (reset) {
	restart();
    delay(1000);
  }
  sensorAddress=addr;
  return (readI2CRegister_8(sensorAddress, SENSOR_GET_ADDRESS) == addr);
}
/*----------------------------------------------------------------------*/
void I2CSensor::changeAddress(int addr, bool wait) {
  sensorAddress=addr;
  begin(wait);
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::getAddress() {
  return sensorAddress;
}
/*----------------------------------------------------------------------*/
void I2CSensor::restart() {
  writeI2CRegister_8(sensorAddress, SENSOR_RESET);
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::getVersion() {
  return readI2CRegister_8(sensorAddress, SENSOR_GET_VERSION);
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::getSwitch() {
  return readI2CRegister_8(sensorAddress, SENSOR_GET_SW);
}
/*----------------------------------------------------------------------*/
void I2CSensor::writeI2CRegister_8(int addr, int value) {
  i2cBeginTransmission(addr);
  i2cWrite(value);
  i2cEndTransmission();
}
/*----------------------------------------------------------------------*/
void I2CSensor::writeI2CRegister_8(int addr, int reg, int value) {
  i2cBeginTransmission(addr);
  i2cWrite(reg);
  i2cWrite(value);
  i2cEndTransmission();
}
/*----------------------------------------------------------------------*/
unsigned int I2CSensor::readI2CRegister_U16(int addr, int reg) {
  i2cBeginTransmission(addr);
  i2cWrite(reg);
  i2cEndTransmission();
  delay(20);
  i2cRequestFrom(addr, 2);
  unsigned int t = i2cRead() << 8;
  t = t | i2cRead();
  return t;
}
/*----------------------------------------------------------------------*/
int I2CSensor::readI2CRegister_16(int addr, int reg) {
  i2cBeginTransmission(addr);
  i2cWrite(reg);
  i2cEndTransmission();
  delay(20);
  i2cRequestFrom(addr, 2);
  int t = i2cRead() << 8;
  t = t | i2cRead();
  return t;
}
/*----------------------------------------------------------------------*/
uint8_t I2CSensor::readI2CRegister_8(int addr, int reg) {
  i2cBeginTransmission(addr);
  i2cWrite(reg);
  i2cEndTransmission();
  delay(20);
  i2cRequestFrom(addr, 1);
  return i2cRead();
}
