#include <I2CSensor_std.h>
#include <Wire.h>

I2CSensor sensor(0x71);

uint16_t CapacitanceHigh;
uint16_t CapacitanceLow;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  sensor.begin(); // reset sensor
  delay(2000); // give some time to boot up
  //sensor.setCalibrateLow(300);
  delay(100); 
  //sensor.setCalibrateHigh(750);
  delay(100); 
}

void loop() {
  
  Serial.print("calibrate low: ");
  Serial.print(sensor.getCalibrateLow(), DEC);
  Serial.print("  calibrate high: ");
  Serial.println(sensor.getCalibrateHigh(), DEC);
  
  Serial.print("Capacitance    : ");
  Serial.print(sensor.getCapacitance()); //read capacitance register
  Serial.println("");
  
  Serial.print("Procent data   : ");
  Serial.print(sensor.getCapacitanceProz()); //read capacitance register
  Serial.println("%");
  Serial.println("");
  delay (1000);
}
