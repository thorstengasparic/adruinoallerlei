//#include "Arduino.h"
//#include "I2Cdev.h"
//#include "Wire.h"
//void setup_mpu_6050_registers();
//void read_mpu_6050_data();
//void write_LCD();
/////////////////////////////////////////////////////////////////////////////////////////
///*Terms of use
/////////////////////////////////////////////////////////////////////////////////////////
////THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
////IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
////FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
////AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
////LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
////OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
////THE SOFTWARE.
//
//
/////////////////////////////////////////////////////////////////////////////////////////
////Support
/////////////////////////////////////////////////////////////////////////////////////////
//Website: http://www.brokking.net/imu.html
//Youtube: https://youtu.be/4BoIE8YQwM8
//Version: 1.0 (May 5, 2016)
//
/////////////////////////////////////////////////////////////////////////////////////////
////Connections
/////////////////////////////////////////////////////////////////////////////////////////
//Power (5V) is provided to the Arduino pro mini by the FTDI programmer
//
//Gyro - Arduino pro mini
//VCC  -  5V
//GND  -  GND
//SDA  -  A4
//SCL  -  A5
//
//LCD  - Arduino pro mini
//VCC  -  5V
//GND  -  GND
//SDA  -  A4
//SCL  -  A5
//*//////////////////////////////////////////////////////////////////////////////////////
//
////Include LCD and I2C library
//
//#include <Wire.h>
//
//#define adr 0
//#define aX 1
//#define aY 2
//#define aZ 3
//#define t 4
//#define gX 5
//#define gY 6
//#define gZ 7
//
////Declaring some global variables
//long[2][8] mpu;
//
//long acc_total_vector;
//
//long gyro_x_cal, gyro_y_cal, gyro_z_cal;
//long loop_timer;
//int lcd_loop_counter;
//float angle_pitch, angle_roll;
//int angle_pitch_buffer, angle_roll_buffer;
//boolean set_gyro_angles;
//float angle_roll_acc, angle_pitch_acc;
//float angle_pitch_output, angle_roll_output;
//
////Initialize the LCD library
//
//
//void setup() {
	//mpu[0][0] = 0x68;
	//mpu[1][0] = 0x68;
//
	//Wire.begin();                                                        //Start I2C as master
	//Serial.begin(115200);                                               //Use only for debugging
	//pinMode(13, OUTPUT);                                                 //Set output 13 (LED) as output
	//
	//setup_mpu_6050_registers();                                          //Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro
//
	//digitalWrite(13, HIGH);                                              //Set digital output 13 high to indicate startup
//
	//
	//Serial.print("  MPU-6050 IMU");                                         //Print text to screen
	//Serial.print("Calibrating gyro");                                       //Print text to screen
	//for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                  //Run this code 2000 times
		//if(cal_int % 125 == 0)Serial.print(".");                              //Print a dot on the LCD every 125 readings
		//read_mpu_6050_data();                                              //Read the raw acc and gyro data from the MPU-6050
		//gyro_x_cal += gyro_x;                                              //Add the gyro x-axis offset to the gyro_x_cal variable
		//gyro_y_cal += gyro_y;                                              //Add the gyro y-axis offset to the gyro_y_cal variable
		//gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
		//delay(3);                                                          //Delay 3us to simulate the 250Hz program loop
	//}
	//gyro_x_cal /= 2000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
	//gyro_y_cal /= 2000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
	//gyro_z_cal /= 2000;                                                  //Divide the gyro_z_cal variable by 2000 to get the avarage offset
//
	//
	//digitalWrite(13, LOW);                                               //All done, turn the LED off
	//
	//loop_timer = micros();                                               //Reset the loop timer
//}
//
//void loop1(){
//
	//read_mpu_6050_data();                                                //Read the raw acc and gyro data from the MPU-6050
//
	//gyro_x -= gyro_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
	//gyro_y -= gyro_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
	//gyro_z -= gyro_z_cal;                                                //Subtract the offset calibration value from the raw gyro_z value
	//
	//gyro_z  = 0;
	////Gyro angle calculations
	////0.0000611 = 1 / (250Hz / 65.5)
	//angle_pitch += gyro_x * 0.0000611;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
	//angle_roll += gyro_y * 0.0000611;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
	//
	////0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
	//angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
	//angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
	//
	////Accelerometer angle calculations
	//acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
	////57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
	//angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
	//angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
	//
	////Place the MPU-6050 spirit level and note the values in the following two lines for calibration
	//angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
	//angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll
//
	//if(set_gyro_angles){                                                 //If the IMU is already started
		//angle_pitch = angle_pitch * 0.0 + angle_pitch_acc * 1;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
		//angle_roll = angle_roll * 0.0 + angle_roll_acc * 1;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
	//}
	//else{                                                                //At first start
		//angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle
		//angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle
		//set_gyro_angles = true;                                            //Set the IMU started flag
	//}
	//
	////To dampen the pitch and roll angles a complementary filter is used
	//angle_pitch_output = angle_pitch_output * 0.99 + angle_pitch * 0.01;   //Take 90% of the output pitch value and add 10% of the raw pitch value
	//angle_roll_output = angle_roll_output * 0.99 + angle_roll * 0.01;      //Take 90% of the output roll value and add 10% of the raw roll value
//
	//write_LCD();                                                         //Write the roll and pitch values to the LCD display
//
	//while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
	//loop_timer = micros();                                               //Reset the loop timer
//}
//void loop(){
//
	//read_mpu_6050_data();                                                //Read the raw acc and gyro data from the MPU-6050
//
	////Accelerometer angle calculations
	//acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
	////57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
	//angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
	//angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
	//
	////Place the MPU-6050 spirit level and note the values in the following two lines for calibration
	//angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
	//angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll
//
	//if(set_gyro_angles){                                                 //If the IMU is already started
		//angle_pitch = angle_pitch * 0.0 + angle_pitch_acc * 1;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
		//angle_roll = angle_roll * 0.0 + angle_roll_acc * 1;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
	//}
	//else{                                                                //At first start
		//angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle
		//angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle
		//set_gyro_angles = true;                                            //Set the IMU started flag
	//}
	//
	////To dampen the pitch and roll angles a complementary filter is used
	//angle_pitch_output = angle_pitch_output * 0.99 + angle_pitch * 0.01;   //Take 90% of the output pitch value and add 10% of the raw pitch value
	//angle_roll_output = angle_roll_output * 0.99 + angle_roll * 0.01;      //Take 90% of the output roll value and add 10% of the raw roll value
//
	//write_LCD();                                                         //Write the roll and pitch values to the LCD display
//
	//while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
	//loop_timer = micros();                                               //Reset the loop timer
//}
//
//void read_mpu_6050_data(){                                             //Subroutine for reading the raw gyro and accelerometer data
	//Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
	//Wire.write(0x3B);                                                    //Send the requested starting register
	//Wire.endTransmission();                                              //End the transmission
	//Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
	//while(Wire.available() < 14);                                        //Wait until all the bytes are received
	//acc_x = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
	//acc_y = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
	//acc_z = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
	//temperature = Wire.read()<<8|Wire.read();                            //Add the low and high byte to the temperature variable
	//gyro_x = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_x variable
	//gyro_y = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
	//gyro_z = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_z variable
//
//}
//
//void w_rite_LCD(){                                                      //Subroutine for writing the LCD
	//////To get a 250Hz program loop (4us) it's only possible to write one character per loop
	//////Writing multiple characters is taking to much time
	////if(lcd_loop_counter == 14)lcd_loop_counter = 0;                      //Reset the counter after 14 characters
	////lcd_loop_counter ++;                                                 //Increase the counter
	////if(lcd_loop_counter == 1){
	////angle_pitch_buffer = angle_pitch_output * 10;                      //Buffer the pitch angle because it will change
	////lcd.setCursor(6,0);                                                //Set the LCD cursor to position to position 0,0
	////}
	////if(lcd_loop_counter == 2){
	////if(angle_pitch_buffer < 0)lcd.print("-");                          //Print - if value is negative
	////else lcd.print("+");                                               //Print + if value is negative
	////}
	////if(lcd_loop_counter == 3)lcd.print(abs(angle_pitch_buffer)/1000);    //Print first number
	////if(lcd_loop_counter == 4)lcd.print((abs(angle_pitch_buffer)/100)%10);//Print second number
	////if(lcd_loop_counter == 5)lcd.print((abs(angle_pitch_buffer)/10)%10); //Print third number
	////if(lcd_loop_counter == 6)lcd.print(".");                             //Print decimal point
	////if(lcd_loop_counter == 7)lcd.print(abs(angle_pitch_buffer)%10);      //Print decimal number
	////
	////if(lcd_loop_counter == 8){
	////angle_roll_buffer = angle_roll_output * 10;
	////lcd.setCursor(6,1);
	////}
	////if(lcd_loop_counter == 9){
	////if(angle_roll_buffer < 0)lcd.print("-");                           //Print - if value is negative
	////else lcd.print("+");                                               //Print + if value is negative
	////}
	////if(lcd_loop_counter == 10)lcd.print(abs(angle_roll_buffer)/1000);    //Print first number
	////if(lcd_loop_counter == 11)lcd.print((abs(angle_roll_buffer)/100)%10);//Print second number
	////if(lcd_loop_counter == 12)lcd.print((abs(angle_roll_buffer)/10)%10); //Print third number
	////if(lcd_loop_counter == 13)lcd.print(".");                            //Print decimal point
	////if(lcd_loop_counter == 14)lcd.print(abs(angle_roll_buffer)%10);      //Print decimal number
//}
//
//void write_LCD(){                                                      //Subroutine for writing the LCD
	////To get a 250Hz program loop (4us) it's only possible to write one character per loop
	////Writing multiple characters is taking to much time
	//if(lcd_loop_counter == 14)lcd_loop_counter = 0;                      //Reset the counter after 14 characters
	//lcd_loop_counter ++;                                                 //Increase the counter
	//if(lcd_loop_counter == 1){
		//Serial.println();
		//angle_pitch_buffer = angle_pitch_output * 10;                      //Buffer the pitch angle because it will change
	//}
	//if(lcd_loop_counter == 2){
		//if(angle_pitch_buffer < 0)Serial.print("-");                          //Print - if value is negative
		//else Serial.print("+");                                               //Print + if value is negative
	//}
	//if(lcd_loop_counter == 3)Serial.print(abs(angle_pitch_buffer)/1000);    //Print first number
	//if(lcd_loop_counter == 4)Serial.print((abs(angle_pitch_buffer)/100)%10);//Print second number
	//if(lcd_loop_counter == 5)Serial.print((abs(angle_pitch_buffer)/10)%10); //Print third number
	//if(lcd_loop_counter == 6)Serial.print(".");                             //Print decimal point
	//if(lcd_loop_counter == 7)Serial.print(abs(angle_pitch_buffer)%10);      //Print decimal number
	//
	//if(lcd_loop_counter == 8){
		//angle_roll_buffer = angle_roll_output * 10;
		//Serial.print("\t");
	//}
	//if(lcd_loop_counter == 9){
		//if(angle_roll_buffer < 0)Serial.print("-");                           //Print - if value is negative
		//else Serial.print("+");                                               //Print + if value is negative
	//}
	//if(lcd_loop_counter == 10)Serial.print(abs(angle_roll_buffer)/1000);    //Print first number
	//if(lcd_loop_counter == 11)Serial.print((abs(angle_roll_buffer)/100)%10);//Print second number
	//if(lcd_loop_counter == 12)Serial.print((abs(angle_roll_buffer)/10)%10); //Print third number
	//if(lcd_loop_counter == 13)Serial.print(".");                            //Print decimal point
	//if(lcd_loop_counter == 14)Serial.print(abs(angle_roll_buffer)%10);      //Print decimal number
//}
//
//
//void setup_mpu_6050_registers(){
	////Activate the MPU-6050
	//Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
	//Wire.write(0x6B);                                                    //Send the requested starting register
	//Wire.write(0x00);                                                    //Set the requested starting register
	//Wire.endTransmission();                                              //End the transmission
	////Configure the accelerometer (+/-8g)
	//Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
	//Wire.write(0x1C);                                                    //Send the requested starting register
	//Wire.write(0x10);                                                    //Set the requested starting register
	//Wire.endTransmission();                                              //End the transmission
	////Configure the gyro (500dps full scale)
	//Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
	//Wire.write(0x1B);                                                    //Send the requested starting register
	//Wire.write(0x08);                                                    //Set the requested starting register
	//Wire.endTransmission();                                              //End the transmission
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////#include "Arduino.h"
////#include "I2Cdev.h"
////#include "Wire.h"
////#include <EEPROM.h>
////#include "MPU9250Registers.h"
//////#include "UtilMpu9250.h"
////
////void GyroRead();
////void set_gyro_registers();
////int convert_receiver_channel(byte function);
////
////byte eeprom_data[36];
////int cal_int;
////double gyro_axis_cal[4];
////
////int temperature;
////int acc_axis[4], gyro_axis[4];
////double gyro_pitch, gyro_roll, gyro_yaw;
////long acc_x, acc_y, acc_z, acc_total_vector;
////
////volatile int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4, receiver_input_channel_5, receiver_input_channel_6, receiver_input_channel_7;
////unsigned long loop_timer;
////
////float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
////float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;
////float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;
////
////float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll, angle_yaw;
////
////boolean gyro_angles_set = false;
////
////bool eeproOK = false;
////bool firsttime = true;
////int calibratecount = 2000;
////
////void setup(){
////
////Serial.begin(115200);
////Wire.begin();
////
////pinMode(LED_BUILTIN, OUTPUT);
////digitalWrite(LED_STATUS_PIN , LOW);
////
////TWBR = 12;                                                                //Set the I2C clock speed to 400kHz.
////
////eeprom_data[31] = 1;
////eeproOK = false;
////
////set_gyro_registers();                                                     //Set the specific gyro registers.
////
//////Let's take multiple gyro data samples so we can determine the average gyro offset (calibration).
////for (cal_int = 0; cal_int < calibratecount ; cal_int ++){                           //Take 2000 readings for calibration.
////if(cal_int % 15 == 0)digitalWrite(LED_STATUS_PIN , !digitalRead(LED_STATUS_PIN));                //Change the led status to indicate calibration.
////GyroRead();                                                        //Read the gyro output.
////gyro_axis_cal[1] += gyro_axis[1];                                       //Ad roll value to gyro_roll_cal.
////gyro_axis_cal[2] += gyro_axis[2];                                       //Ad pitch value to gyro_pitch_cal.
////gyro_axis_cal[3] += gyro_axis[3];                                       //Ad yaw value to gyro_yaw_cal.
//////We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
////delayMicroseconds(1000);                                                //Wait 1000us.
////delay(3);                                                               //Wait 3 milliseconds before the next loop.
////}
//////Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
////gyro_axis_cal[1] /= calibratecount;                                                 //Divide the roll total by 2000.
////gyro_axis_cal[2] /= calibratecount;                                                 //Divide the pitch total by 2000.
////gyro_axis_cal[3] /= calibratecount;                                                 //Divide the yaw total by 2000.
////
////PCICR |= (1 << PCIE0);			//Set PCIE0 to enable PCMSK0 scan.
////PCICR |= (1 << PCIE2);                                                    //Set PCIE2 to enable PCMSK2 scan.
////PCMSK0 |= (1 << PCINT0);                                                  //Set PCINT0 (digital input 8) to trigger an interrupt on state change.
////PCMSK0 |= (1 << PCINT1);                                                  //Set PCINT1 (digital input 9)to trigger an interrupt on state change.
////PCMSK0 |= (1 << PCINT2);                                                  //Set PCINT2 (digital input 10)to trigger an interrupt on state change.
////PCMSK0 |= (1 << PCINT3);                                                  //Set PCINT3 (digital input 11)to trigger an interrupt on state change.
////PCMSK0 |= (1 << PCINT4);                                                  //Set PCINT3 (digital input 12)to trigger an interrupt on state change.
////PCMSK2 |= (1 << PCINT18);
////PCMSK2 |= (1 << PCINT19);
////loop_timer = micros();                                                    //Set the timer for the next loop.
////
//////When everything is done, turn off the led.
////digitalWrite(LED_STATUS_PIN,LOW);                                                     //Turn off the warning led.
////angle_pitch = angle_pitch_acc;                                          //Set the gyro pitch angle equal to the accelerometer pitch angle when the quadcopter is started.
////angle_roll = angle_roll_acc;                                            //Set the gyro roll angle equal to the accelerometer roll angle when the quadcopter is started.
////gyro_yaw_input =0;
////}
////
////#define writeByteMacro(i2cadress, regadr, newregval) Wire.beginTransmission(i2cadress); Wire.write(regadr); Wire.write(newregval); Wire.endTransmission();
////#define readByteMacro(i2cadress, regadr, resultbyte) Wire.beginTransmission(i2cadress); Wire.write(regadr); Wire.endTransmission(); Wire.requestFrom(i2cadress, 1); while(Wire.available() < 1); resultbyte = Wire.read();
////
////void set_gyro_registers(){
////
//////Setup the MPU-6050
////if(eeprom_data[31] == 1){
////
////writeByteMacro(MPU9250_ADDRESS, PWR_MGMT_1, 0x00)   //Set the register bits as 00000000 to activate the gyro
////writeByteMacro(MPU9250_ADDRESS, PWR_MGMT_1, 0x01)   // Auto select clock source to be PLL gyroscope reference if ready else
////
////writeByteMacro(MPU9250_ADDRESS,GYRO_CONFIG, 0x08)	//Set the register bits as 00001000 (500dps full scale)
////writeByteMacro(MPU9250_ADDRESS,CONFIG, 0x03)		//Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz)
////
//////Let's perform a random register check to see if the values are written correct
////byte resultByte =  -1;
////readByteMacro(MPU9250_ADDRESS, GYRO_CONFIG, resultByte)
////if(resultByte != 0x08){
////while(1)
////{
////delay(1000);
////digitalWrite(LED_STATUS_PIN,HIGH);
////delay(100);
////digitalWrite(LED_STATUS_PIN,LOW);
////}
////}
////writeByteMacro(MPU9250_ADDRESS,ACCEL_CONFIG, 0x10)		//Set the register bits as 00010000 (+/- 8g full scale range)
////writeByteMacro(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x01)	// Write new ACCEL_CONFIG2 41Hz  11.80ms delay
////writeByteMacro(MPU9250_ADDRESS, INT_PIN_CFG, 0x02)  	//INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=1 ; CLKOUT_EN=0
////}
////}
////
////void GyroRead(){
//////Read the MPU-6050
////if(eeprom_data[31] == 1){
////Wire.beginTransmission(MPU9250_ADDRESS);                                   //Start communication with the gyro.
////Wire.write(ACCEL_XOUT_H);                                                       //Start reading @ register 43h and auto increment with every read.
////Wire.endTransmission();                                                 //End the transmission.
////Wire.requestFrom(MPU9250_ADDRESS,14);                                      //Request 14 bytes from the gyro.
////
////receiver_input_channel_1 = convert_receiver_channel(1);                 //Convert the actual receiver signals for pitch to the standard 1000 - 2000us.
////receiver_input_channel_2 = convert_receiver_channel(2);                 //Convert the actual receiver signals for roll to the standard 1000 - 2000us.
////receiver_input_channel_3 = convert_receiver_channel(3);                 //Convert the actual receiver signals for throttle to the standard 1000 - 2000us.
////receiver_input_channel_4 = convert_receiver_channel(4);                 //Convert the actual receiver signals for yaw to the standard 1000 - 2000us.
////receiver_input_channel_5 = convert_receiver_channel(5);                 //Convert the actual receiver signals for yaw to the standard 1000 - 2000us.
//////receiver_input_channel_6 = convert_receiver_channel(6);                 //Convert the actual receiver signals for yaw to the standard 1000 - 2000us.
//////receiver_input_channel_7 = convert_receiver_channel(7);                 //Convert the actual receiver signals for yaw to the standard 1000 - 2000us.
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
////if(cal_int == calibratecount){
////gyro_axis[1] -= gyro_axis_cal[1];                                       //Only compensate after the calibration.
////gyro_axis[2] -= gyro_axis_cal[2];                                       //Only compensate after the calibration.
////gyro_axis[3] -= gyro_axis_cal[3];                                       //Only compensate after the calibration.
////}
////
////if (eeproOK)
////{
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
////}
////else
////{
////gyro_roll = gyro_axis[1];
////gyro_pitch = gyro_axis[2];
////gyro_yaw = gyro_axis[3];
////
////acc_x = -acc_axis[2];
////acc_y = -acc_axis[1];
////acc_z = acc_axis[3];
////}
////}
////
////int outcounter =0;
////
////void loop()
////{
////
//////65.5 = 1 deg/sec (check the datasheet of the MPU-6050 for more information).
////gyro_roll_input = (gyro_roll_input * 0.7) + ((gyro_roll / 65.5) * 0.3);   //Gyro pid input is deg/sec.
////gyro_pitch_input = (gyro_pitch_input * 0.7) + ((gyro_pitch / 65.5) * 0.3);//Gyro pid input is deg/sec.
////gyro_yaw_input = (gyro_yaw_input * 0.7) + ((gyro_yaw / 65.5) * 0.3);      //Gyro pid input is deg/sec.
////
////////////////////////////////////////////////////////////////////////////////////////////////////////
//////This is the added IMU code from the videos:
//////https://youtu.be/4BoIE8YQwM8
//////https://youtu.be/j-kE0AMEWy4
////////////////////////////////////////////////////////////////////////////////////////////////////////
////
//////Gyro angle calculations
//////0.0000611 = 1 / (250Hz / 65.5)
////angle_pitch += gyro_pitch * 0.0000611;                                    //Calculate the traveled pitch angle and add this to the angle_pitch variable.
////angle_roll += gyro_roll * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.
////angle_yaw += gyro_yaw * 0.0000611;
////
//////0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
////angle_pitch -= angle_roll * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the roll angle to the pitch angel.
////angle_roll += angle_pitch * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the pitch angle to the roll angel.
////
//////Accelerometer angle calculations
////acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));       //Calculate the total accelerometer vector.
////
////// 57.296 = 1 / (3.142 / 180)
////if(abs(acc_y) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
////angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;          //Calculate the pitch angle.
////}
////if(abs(acc_x) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
////angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;          //Calculate the roll angle.
////}
////
//////Place the MPU-6050 spirit level and note the values in the following two lines for calibration.
////angle_pitch_acc -= 0;
////angle_roll_acc += 0;                                          //Accelerometer calibration value for roll.
////
////angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;            //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
////angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;               //Correct the drift of the gyro roll angle with the accelerometer roll angle.
////
////if (!gyro_angles_set)
////{
////angle_pitch = angle_pitch_acc;                                          //Set the gyro pitch angle equal to the accelerometer pitch angle when the quadcopter is started.
////angle_roll = angle_roll_acc;                                            //Set the gyro roll angle equal to the accelerometer roll angle when the quadcopter is started.
////gyro_yaw_input =0;
////gyro_angles_set = true;                                                 //Set the IMU started flag.
////}
////if (outcounter == 0) Serial.print("P:\t");
////if (outcounter == 1) Serial.print(angle_pitch_acc);
////if (outcounter == 2) Serial.print("\tR:\t");
////if (outcounter == 3) Serial.print(angle_roll_acc);
////if (outcounter == 4) Serial.print("\tY:\t");
////if (outcounter == 6) Serial.print(angle_pitch);
////if (outcounter == 7) Serial.print("\tY:\t");
////if (outcounter == 8) Serial.print(angle_roll);
////
////if (outcounter++ > 8) {
////Serial.println();
////outcounter =0;
////}
////
////if(micros() - loop_timer > 4050)digitalWrite(LED_STATUS_PIN, HIGH);                   //Turn on the LED if the loop time exceeds 4050us.
////
//////All the information for controlling the motor's is available.
//////The refresh rate is 250Hz. That means the esc's need there pulse every 4ms.
////while(micros() - loop_timer < 4000);                                      //We wait until 4000us are passed.
////loop_timer = micros();
////GyroRead();
////}
////
////int convert_receiver_channel(byte function){
////return function;
////}
//////
//////int mag_who, mag_info, mag_st1, mag_st2;
//////
//////byte errorled;
//////byte statusled;
//////
//////double RollAngle_Acc, NickAngle_Acc;
//////double RollAngle, NickAngle;
//////
//////void InitGyro(void);
//////void InitMaster(void);
//////void GyroRead(void);
//////
//////float magbias[3] = {0, 0, 0}; // Factory mag calibration and mag bias
//////#define LED_PIN 13
//////bool blinkState = false;
//////unsigned long loop_timer;
//////float gyroBias[3] = {0, 0, 0}, accelBias[3] = {0, 0, 0};      // Bias corrections for gyro and accelerometer
//////float   selfTest[6];    // holds results of gyro and accelerometer self test
//////
//////float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll, angle_yaw;
//////bool firsttime = true;
//////
//////void setup() {
//////// Setup for Master mode, pins 16/18, external pullups, 400kHz
//////Wire.begin();//I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
//////Serial.begin(115200);
////////pinMode(SDA, INPUT);
////////pinMode(SCL, INPUT);
//////TWBR = 12;
////////for(int data = 0; data <= 35; data++)eeprom_data[data] = EEPROM.read(data);               //Read EEPROM for faster data access
//////////Check the EEPROM signature to make sure that the setup program is executed.
////////while(eeprom_data[33] != 'J' || eeprom_data[34] != 'M' || eeprom_data[35] != 'B'){
////////delay(1500);                                                                         //Wait for 500ms.
////////digitalWrite(LED_STATUS_PIN, !digitalRead(LED_STATUS_PIN));                                                 //Change the led status to indicate error.
////////}
//////
//////// Read the WHO_AM_I register, this is a good test of communication
//////Serial.println("MPU9250 + MPL3115A2 devices...");
//////byte c1 = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
//////Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c1, HEX);
//////
//////MPU9250SelfTest(selfTest); // Start by performing self test and reporting values
//////Serial.print("x-axis self test: acceleration trim within : "); Serial.print(selfTest[0],1); Serial.println("% of factory value");
//////Serial.print("y-axis self test: acceleration trim within : "); Serial.print(selfTest[1],1); Serial.println("% of factory value");
//////Serial.print("z-axis self test: acceleration trim within : "); Serial.print(selfTest[2],1); Serial.println("% of factory value");
//////Serial.print("x-axis self test: gyration trim within : "); Serial.print(selfTest[3],1); Serial.println("% of factory value");
//////Serial.print("y-axis self test: gyration trim within : "); Serial.print(selfTest[4],1); Serial.println("% of factory value");
//////Serial.print("z-axis self test: gyration trim within : "); Serial.print(selfTest[5],1); Serial.println("% of factory value");
//////if (!initMPU9250(0, GFS_500DPS, AFS_8G) )
//////{
//////Serial.println("ERROR: MPU9250 init");
//////digitalWrite(13,HIGH);                                           //Turn on the warning led
//////while(1)
//////{
//////delay(1000);                                                     //Stay in this loop for ever{
//////digitalWrite(13,HIGH);                                           //Turn on the warning led
//////delay(100);                                                     //Stay in this loop for ever
//////digitalWrite(13,LOW);                                           //Turn on the warning led
//////}
//////}
//////
//////InitGyro();
//////CalibrateGyro(gyro_axis_cal, acc_axis_cal);
//////
//////// Read the WHO_AM_I register of the magnetometer, this is a good test of communication
//////byte d = readByte(AK8963_ADDRESS, AK8963_WHO_AM_I);  // Read WHO_AM_I register for AK8963
//////Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX);
//////
//////initAK8963(magCalibration, MFS_16BITS);
////////enableI2CMaster();
//////Serial.println("MPU9250 initialized "); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
//////
////////setupSlave(
////////MPU9250_ADDRESS,
////////0                   /* Setup Slave0 */
////////, AK8963_ADDRESS      /* Read from the Mag device */
////////, AK8963_XOUT_L /* Start at the AK8963_INFO register -- this #define should be updated */
////////, true                /* is_read */
////////, 7                  /* read 10 bytes, most importantly this includes a read of STATUS2 */
////////, true                /* send_reg_addr */
////////, false                /* swap word bytes on read - make it the same endianness as MPU data*/
////////, false               /* use even swap alignment */
////////, true                /* enable it with this call */
////////);
//////
//////// configure Arduino LED for
//////pinMode(LED_PIN, OUTPUT);
////////pinMode(5, OUTPUT);
//////angle_roll_acc =0;
//////angle_pitch_acc =0;
//////angle_pitch =0;
//////angle_roll =0;
//////angle_yaw =0;
//////digitalWrite(LED_STATUS_PIN, LOW);
//////
//////loop_timer = micros();                                                    //Set the timer for the next loop.
//////
//////}
//////
//////int oucnt =0;
//////void loop() {
//////
//////if(micros() - loop_timer > 4050)digitalWrite(LED_STATUS_PIN, HIGH);                   //Turn on the LED if the loop time exceeds 4050us.
//////while(micros() - loop_timer < 4000);                                      //We wait until 4000us are passed.
//////loop_timer = micros();                                                    //Set the timer for the next loop.
//////
//////GyroRead();
//////readMagData(NULL);
//////
//////angle_pitch += gyro_pitch * 0.0000611;                                    //Calculate the traveled pitch angle and add this to the angle_pitch variable.
//////angle_roll += gyro_roll * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.
//////angle_yaw +=  gyro_yaw * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.
//////
////////0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
//////angle_pitch -= angle_roll * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the roll angle to the pitch angel.
//////angle_roll += angle_pitch * sin(gyro_yaw * 0.000001066);                  //If the IMU has yawed transfer the pitch angle to the roll angel.
//////
//////
////////Accelerometer angle calculations
//////acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));       //Calculate the total accelerometer vector.
//////
//////// 57.296 = 1 / (3.142 / 180)
//////if(abs(acc_y) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
//////angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;          //Calculate the pitch angle.
//////}
//////if(abs(acc_x) < acc_total_vector){                                        //Prevent the asin function to produce a NaN
//////angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;          //Calculate the roll angle.
//////}
//////
//////if (firsttime)
//////{
//////angle_pitch = angle_pitch_acc;
//////angle_roll = angle_roll_acc;
//////firsttime = false;
//////}
//////
////////Place the MPU-6050 spirit level and note the values in the following two lines for calibration.
//////angle_pitch_acc -= 3;
//////angle_roll_acc += 1;                                          //Accelerometer calibration value for roll.
//////
//////angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;            //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
//////angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;               //Correct the drift of the gyro roll angle with the accelerometer roll angle.
//////
//////float dreg1= 0;
//////float mag_total_vector = sqrt((MagX*MagX)+(MagY*MagY)+(MagZ*MagZ));       //Calculate the total accelerometer vector.
//////if(abs(MagZ) < mag_total_vector){                                        //Prevent the asin function to produce a NaN
//////dreg1 = asin((float)MagZ/mag_total_vector)* -57.296;          //Calculate the roll angle.
//////}
//////
//////double dreg= 0;
//////if (MagY > 0)			dreg = 90 - atan2(MagX,MagY)*180/3.141;
//////if (MagY < 0)			dreg = 270 - atan2(MagX,MagY)*180/3.141;
//////if (0 == MagX  && MagY<0)dreg= 180;
//////if (0 == MagX && MagY>0)dreg= 0;
//////
//////double angle_rollrad = (double)angle_roll /180*3.141;
//////double angle_pitchrad = (double)angle_pitch /180*3.141;
//////
//////double magx = MagZ * sin(angle_rollrad) -  MagY * cos(angle_pitchrad);
//////
//////double magy = MagX  * cos(angle_pitchrad) + MagY * sin(angle_pitchrad) * sin(angle_rollrad) + MagZ * sin(angle_pitchrad) * cos(angle_rollrad);
//////double yaw = atan2(magx,magy)/3.141*180;
//////double totalmag = sqrt(MagX * MagX + MagY*MagY +MagZ*MagZ);
////////
////////oucnt++;
//////oucnt= 131;
////////blinkState = !blinkState;
////////digitalWrite(13, blinkState);
////////if (oucnt == 126 ) {Serial.print("p:");		Serial.print(angle_pitch); }
////////if (oucnt == 127 ) {Serial.print(" ap:");	Serial.print(angle_pitch_acc); }
////////if (oucnt == 128 ) {Serial.print("   r:"); Serial.print(angle_roll); }
////////if (oucnt == 129 ) {Serial.print(" ar:");	Serial.print(angle_roll_acc); }
////////if (oucnt == 130 ) {Serial.print("   y:");	Serial.print(angle_yaw); }
////////if (oucnt == 131 ) {Serial.print("   mx:"); Serial.print(MagX); }
////////if (oucnt == 131)  {Serial.print(" my:");	Serial.print(MagY); }
////////if (oucnt == 131 ) {Serial.print(" mz:");	Serial.print(MagZ); }
////////if (oucnt == 131 ) {Serial.print(" magx");	Serial.print(magx); }
////////if (oucnt == 131 ) {Serial.print(" magy:");	Serial.print(magy); }
////////if (oucnt == 131 ) {Serial.print(" y:");	Serial.print(yaw); }
////////if (oucnt == 131 ) {Serial.print(" deg:");	Serial.print(dreg); }
////////if (oucnt == 131 ) {Serial.print(" deg1:");	Serial.print(dreg1); }
////////if (oucnt == 131 ) {Serial.print(" totalmag:");	Serial.print(totalmag); }
//////
//////if (oucnt == 131 ) {Serial.print("|1:"); Serial.print(MagX); }
//////if (oucnt == 131)  {Serial.print("|2:");	Serial.print(MagY); }
//////if (oucnt == 131 ) {Serial.print("|3:");	Serial.print(MagZ); }
//////if (oucnt == 131 ) {Serial.print("0:");	Serial.print(totalmag); }
//////
////////
//////if (oucnt == 131 ) {Serial.println("");}
//////if (oucnt == 136 ) oucnt = 0;
//////
//////}
//////
////
//////
//////
//////
//////
//////
//////
