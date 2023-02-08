/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <EEPROM.h>                                  //Include the EEPROM.h library so we can store information onto the EEPROM
#include "Sensirion.h"

//#include <DallasTemperature.h>

#include "Ds18S20Min.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void adresseAusgeben(void );
bool GetSwitches();
byte SwitchToggleState(int sw);
byte CurrentSwitchState(int sw);
bool PressDownSeen(int sw, bool doRest);
bool readEprom();
void writeEprom();
void CheckStoreEEprom();
void ResetTepmerature();
void start_gyro();
float ReadTemperture();
float ReadFromSensorTemperature();
char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false);


#define ONE_WIRE_BUS	2		/* Digitalport definieren */
#define SSD_ON_OFF		A1		/* Digitalport definieren */
#define LED_ACTIVE		6		/* Digitalport definieren */
#define DISPLAY_LIGHT   3  /* Digitalport definieren */

#define Switch_00		8
#define Switch_01		7
#define Switch_02		9
#define Switch_03		5
#define Switch_04		4

 #define MPU6050_ADDRESS 0x68
 #define CONFIG           0x1A
 #define GYRO_CONFIG      0x1B
 #define ACCEL_CONFIG     0x1C
 #define ACCEL_CONFIG2    0x1D
 #define ACCEL_XOUT_H     0x3B
 #define ACCEL_XOUT_L     0x3C
 #define ACCEL_YOUT_H     0x3D
 #define ACCEL_YOUT_L     0x3E
 #define ACCEL_ZOUT_H     0x3F
 #define ACCEL_ZOUT_L     0x40
 #define TEMP_OUT_H       0x41
 #define TEMP_OUT_L       0x42
 #define GYRO_XOUT_H      0x43
 #define GYRO_XOUT_L      0x44
 #define GYRO_YOUT_H      0x45
 #define GYRO_YOUT_L      0x46
 #define GYRO_ZOUT_H      0x47
 #define GYRO_ZOUT_L      0x48
 #define USER_CTRL        0x6A  // Bit 7 enable DMP, bit 3 reset DMP
 #define PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
 #define PWR_MGMT_2       0x6C


// Pin 5 6 I2s
//#define I2C_ADDR 0x27  // Add your address here.
#define I2C_ADDR 0x3F  // Add your address here.
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

const uint8_t dataPin  =  11;
const uint8_t clockPin =  10;
Sensirion tempSensor = Sensirion(dataPin, clockPin);

float temperature;
float humidity;
float dewpoint;


//OneWire ds(ONE_WIRE_BUS); /* Ini oneWire instance */
//Ds18S20Temperature  sensors(&ds);

DeviceAddress sensor1 = { 0x10, 0x38, 0x27, 0x57, 0x2, 0x8, 0x0, 0x79 };

#define SW_Scroll	0
#define SW_UP		1
#define SW_DOWN		2
#define SW_LIGTH	3
#define SW_SPARE	4
#define switchcount 5

byte switchDOWNSeen[switchcount];
byte currentSwitchState[switchcount];
byte switchToggleState[switchcount];
byte switchPin[switchcount];

int timer1_counter ;

#define workingmode_OFF 0
#define workingmode_ON  1
#define workingmode_HEATING  2
#define workingmode_COOLING  3
#define workingmode_MAX  workingmode_COOLING
String  modestr[4] = {"Aus    ", "An     ", "Heizen ", "Kuehlen"};
int sollwert = 0;
signed short workingmode = workingmode_OFF;
byte short on_off_hysterese = 3;

#define state_ShowTemperatue	0
#define state_ShowHum			1
#define state_ShowMode			2
#define state_ShowSollwert		3
#define state_ShowSHysterese	4
#define state_ShowResetMinMax	5
#define state_MaxState			state_ShowResetMinMax

#define INVALID_TEMPERATURE -1000

byte prog_state = state_ShowTemperatue;


byte stat =0;
float curtemperature =-1000.0;
float minTemperature ;
float maxTemperature ;
float temperatureDelta = 1.5 ;
#define maxHistory 36
float averArr[maxHistory];
long  avcounter =0;
float averTemperature ;
int mpu6050Temperture;
unsigned long loopcount =0;;
bool resfreshStateDisplay = true;

#define ON true
#define OFF false
bool temperatureLoadOnSwitch = OFF;
char tempBuffer[32];

void setup()
{
  Serial.begin(9600);
  Serial.println("Temperatur");
  Wire.begin();  
  
  delay(300);
  lcd.begin (16,2); //  our LCD is a 16x2, change for your LCD if needed
  delay(300);
  
  Wire.setClock(50000);
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(SSD_ON_OFF, OUTPUT);
  pinMode(LED_ACTIVE, OUTPUT);
  digitalWrite(SSD_ON_OFF,HIGH);
  digitalWrite(SSD_ON_OFF,HIGH);
  
  pinMode(DISPLAY_LIGHT, OUTPUT);
  analogWrite(DISPLAY_LIGHT, 200);
  analogWrite(LED_ACTIVE,50);

  lcd.begin (16,2); //  our LCD is a 16x2, change for your LCD if needed
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);// LCD Backlight ON
  lcd.setBacklight(HIGH);
  lcd.home (); // go home on LCD
  lcd.setCursor(0,0);
  lcd.print("Init...");
  lcd.setCursor(0,1);


	if (!readEprom())
	{
		writeEprom();
		lcd.print("Cannot read EEPROM");
		Serial.println("Cannot read EEPROM");
	}
	else
	{
		lcd.print("EEPROM OK");
		Serial.println("EEPROM OK");
	}

  //sensors.Begin();
  
  delay(1000);
  ResetTepmerature();

  switchPin[SW_LIGTH]	= Switch_00;
  switchPin[SW_Scroll]	= Switch_01;
  switchPin[SW_DOWN]	= Switch_02;
  switchPin[SW_UP]		= Switch_03;
  switchPin[SW_SPARE]	= Switch_04;

  for(int i =0; i< switchcount;i++)
  {
	pinMode(switchPin[i], INPUT_PULLUP);
	switchDOWNSeen[i] = false;
	currentSwitchState[i] = HIGH;
	switchToggleState[i] = LOW;
  }
  switchToggleState[SW_LIGTH] = HIGH;

  lcd.clear();  
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;				// PWM on Pins 9 and 10: controlled by timer 1 !!!
  TCCR1B = 0;

  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 59286;   // preload timer 65536-16MHz/256/10Hz
  //timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz

  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();      
  delay(1000);       // enable all interrupts
  ResetTepmerature();
}

	
ISR(TIMER1_OVF_vect)        // interrupt service routine
{
	noInterrupts();           // disable all interrupts
	GetSwitches();
	interrupts();             // enable all interrupts
	TCNT1 = timer1_counter;   // preload timer
}

unsigned long hysteresecounter = 0;
bool hystereseOK = true;
void loop()
{
	if (loopcount % 10 == 0) // all second
	{
		float sval = ReadTemperture();
		if (sval != INVALID_TEMPERATURE)
			curtemperature = sval;
		
		if (maxTemperature <curtemperature)  maxTemperature  = curtemperature;
		if (minTemperature > curtemperature)  minTemperature  = curtemperature;
	}

	if (loopcount % 1000 == 0) // all 100 second
	{
		averArr[avcounter] = curtemperature;
		avcounter++;
		if (avcounter >=maxHistory) avcounter =0;
		float avSum = 0.0;
		for(int i =0; i< maxHistory;i++)
		{
			avSum +=averArr[i];
		}
		averTemperature = avSum/(float)maxHistory;
	}

	switch(prog_state)
	{
		case state_ShowTemperatue:{
			if (loopcount % 10 ==0 )
			{
				lcd.setCursor(0,0);
				lcd.print("A:");
				lcd.print(floatToString(tempBuffer, curtemperature, 1,5));
				lcd.setCursor(8,0);
				lcd.print("D:");
				lcd.print(floatToString(tempBuffer, averTemperature, 1,5));
				
				lcd.setCursor(0,1);
				lcd.print("m:" );
				lcd.print(floatToString(tempBuffer, minTemperature, 1,5));
				lcd.setCursor(8,1);
				lcd.print("M:" );
				lcd.print(floatToString(tempBuffer, maxTemperature, 1,5));
				lcd.print("        ");
			}
			if (PressDownSeen(SW_SPARE, true))
			{
				prog_state =state_ShowHum;
				}
			break;
			case state_ShowHum:{
				if (loopcount % 10 ==0 )
				{
					lcd.setCursor(0,0);
					lcd.print("A:");
					lcd.print(floatToString(tempBuffer, curtemperature, 1,5));
					lcd.setCursor(8,0);
					lcd.print("D:");
					lcd.print(floatToString(tempBuffer, averTemperature, 1,5));
					
					lcd.setCursor(0,1);
					lcd.print("%:" );
					lcd.print(floatToString(tempBuffer, humidity, 1,5));
					lcd.setCursor(8,1);
					lcd.print("d:" );
					lcd.print(floatToString(tempBuffer, dewpoint, 1,5));
					lcd.print("        ");
				}
				if (PressDownSeen(SW_SPARE, true))
				prog_state =state_ShowTemperatue;
				break;
				}
		}
		case state_ShowMode:{
			if (resfreshStateDisplay )
			{
				lcd.setCursor(0,0);
				lcd.print("Mode: ");
				lcd.print(modestr[workingmode]);
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_DOWN, true))
			{
				workingmode++;
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_UP, true))
			{
				workingmode--;
				resfreshStateDisplay= true;
			}
			if (workingmode > workingmode_MAX )workingmode  = 0;
			if (workingmode < 0 )workingmode  = workingmode_MAX;
			CheckStoreEEprom();
			break;
		}
		case state_ShowSollwert:{
			if (resfreshStateDisplay )
			{
				lcd.setCursor(0,0);
				lcd.print("SollTemp: ");
				lcd.print(sollwert);
				lcd.print("    ");
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_DOWN, true))
			{
				sollwert++;
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_UP, true))
			{
				sollwert--;
				resfreshStateDisplay= true;
			}
			CheckStoreEEprom();
			break;
		}

		case state_ShowSHysterese:{
			if (resfreshStateDisplay )
			{
				lcd.setCursor(0,0);
				lcd.print("On/Off Verzoegerung: ");
				lcd.setCursor(0,1);
				lcd.print(on_off_hysterese);
				lcd.print(" Minuten");
				lcd.print("    ");
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_DOWN, true))
			{
				on_off_hysterese++;
				resfreshStateDisplay= true;
			}
			if( PressDownSeen(SW_UP, true))
			{
				on_off_hysterese--;
				resfreshStateDisplay= true;
			}
			if (on_off_hysterese == 0) on_off_hysterese = 1;
			if (on_off_hysterese >9) on_off_hysterese = 9;
			CheckStoreEEprom();
			break;
		}
		case state_ShowResetMinMax:{
			if (resfreshStateDisplay )
			{
				lcd.setCursor(0,0);
				lcd.print("Reset Min/Max ");
				resfreshStateDisplay= true;
			}
			if (PressDownSeen(SW_SPARE, true))
			{
				lcd.clear();
				lcd.home();
				lcd.setCursor(0,0);
				lcd.print("Reseted...");
				minTemperature = curtemperature ;
				maxTemperature = curtemperature ;
				averTemperature = curtemperature;
				for(int i =0; i< 36;i++)
				{
					averArr[i] = curtemperature;
				}
				delay(2000);
				lcd.clear();
				lcd.home();
				prog_state = state_ShowTemperatue;
			}
			break;
		}
	}

	if (SwitchToggleState(SW_LIGTH) == HIGH)
		analogWrite(DISPLAY_LIGHT, 200);
	else
		analogWrite(DISPLAY_LIGHT, 4);	

	if (PressDownSeen(SW_Scroll, true))
	{
		prog_state++;
		if (prog_state > state_MaxState)
			prog_state =0;
		lcd.clear();
		lcd.home();
		resfreshStateDisplay = true;
	}

	if (!hystereseOK)
	{
		if (hysteresecounter > 600* on_off_hysterese)
			hystereseOK = true;
	}

	byte  switchLoadOn = LOW;
	
	if (workingmode == workingmode_COOLING)
	{
		float lowTrigger = sollwert - temperatureDelta;
		float highTrigger = sollwert + temperatureDelta;
		if (temperatureLoadOnSwitch == ON)
		{
			if (curtemperature  <  lowTrigger ) 
			{
				temperatureLoadOnSwitch = OFF;
				hystereseOK = false;
				hysteresecounter=0;
			}
		}
		else
		{
			if (curtemperature  >  highTrigger )
				temperatureLoadOnSwitch = ON;
		}
	}

	if (workingmode == workingmode_HEATING)
	{
		float lowTrigger = sollwert - temperatureDelta;
		float highTrigger = sollwert + temperatureDelta;
		if (temperatureLoadOnSwitch == ON)
		{
			if (curtemperature  >  highTrigger )
			{
				temperatureLoadOnSwitch = OFF;
				hystereseOK = false;
				hysteresecounter=0;
			}
		}
		else
		{
			if (curtemperature  <  lowTrigger )
				temperatureLoadOnSwitch = ON;
		}
	}

	if (temperatureLoadOnSwitch && hystereseOK)
		switchLoadOn = HIGH;
	
	if (workingmode == workingmode_OFF)switchLoadOn = LOW;
	if (workingmode == workingmode_ON )switchLoadOn = HIGH;

	digitalWrite(SSD_ON_OFF, switchLoadOn);
	analogWrite(LED_ACTIVE, switchLoadOn*5);

	delay(100);
	loopcount++;
	hysteresecounter++;
}

void CheckStoreEEprom()
{
	if (PressDownSeen(SW_SPARE, true))
	{
		lcd.clear();
		lcd.home();
		lcd.setCursor(0,0);
		lcd.print("Gespeichert...");
		writeEprom();
		delay(1500);
		lcd.clear();
		lcd.home();
		resfreshStateDisplay = true;
	}
}

bool PressDownSeen(int sw, bool doRest)
{
	noInterrupts();
	byte erg  = switchDOWNSeen[sw];
	if (doRest) switchDOWNSeen[sw] = false;
	interrupts();             // enable all interrupts
	return erg ;
}

byte CurrentSwitchState(int sw)
{
	return currentSwitchState[sw];
}

byte SwitchToggleState(int sw)
{
	return switchToggleState[sw];
}

bool GetSwitches()
{
	for(int i =0; i< switchcount;i++)
	{
		byte value = digitalRead(switchPin[i]);
		if (currentSwitchState[i] != value)
		{
			delay (20);
			value = digitalRead(switchPin[i]);
			if (currentSwitchState[i] != value)
			{
				if (currentSwitchState[i] == LOW)
				{
					if (value == HIGH)
					{
						if (switchToggleState[i])
						switchToggleState[i] = LOW;
						else
						switchToggleState[i] = HIGH;

					}
				}
				if (value == LOW)
				{
					switchDOWNSeen[i] = true;
				}
				currentSwitchState[i]= value;
			}
		}
	}
}

void ResetTepmerature()
{
  curtemperature = ReadTemperture();
    minTemperature = curtemperature ;
  maxTemperature = curtemperature ;
  averTemperature = curtemperature;
  for(int i =0; i< 36;i++)
  {
	  averArr[i] = curtemperature;
  }

}
void writeEprom()
{
	EEPROM.write(0, 'T');
	EEPROM.write(1, 'E');
	EEPROM.write(2, 'M');
	EEPROM.write(3, 'P');
	EEPROM.write(4, '0');
		
	byte value0 = sollwert & 0xff;
	byte value1 = (sollwert >> 8) & 0xff;
	EEPROM.write(5, value0);
	EEPROM.write(6, value1);

	value0 = workingmode & 0xff;
	//byte value1 = (sollwert >> 8) & 0xff;
	EEPROM.write(7, value0);
	//EEPROM.write(6, value1);

	value0 = on_off_hysterese & 0xff;
	//byte value1 = (sollwert >> 8) & 0xff;
	EEPROM.write(8, value0);
	//EEPROM.write(6, value1);

}

bool readEprom()
{
	if (EEPROM.read(0) != 'T') return false;
	if (EEPROM.read(1) != 'E') return false;
	if (EEPROM.read(2) != 'M') return false;
	if (EEPROM.read(3) != 'P') return false;
	if (EEPROM.read(4) != '0') return false;

	byte value0 = EEPROM.read(5);
	byte value1 = EEPROM.read(6);
	sollwert  = (value1<<8) +value0;

	value0 = EEPROM.read(7);
	value1 = 0;
	workingmode = value0;

	value0 = EEPROM.read(8);
	value1 = 0;
	on_off_hysterese = value0;

	return true;
}
//void start_gyro(){
//
		//Wire.beginTransmission(MPU6050_ADDRESS);                             //Start communication with the gyro
		//Wire.write(PWR_MGMT_1);                                            //PWR_MGMT_1 register
		//Wire.write(0x00);                                            //Set to zero to turn on the gyro
		//Wire.endTransmission();                                      //End the transmission
		//
		//Wire.beginTransmission(MPU6050_ADDRESS);                             //Start communication with the gyro
		//Wire.write(PWR_MGMT_1);                                            //Start reading @ register 28h and auto increment with every read
		//Wire.endTransmission();                                      //End the transmission
		//Wire.requestFrom(MPU6050_ADDRESS, 1);                                //Request 1 bytes from the gyro
		//while(Wire.available() < 1);                                 //Wait until the 1 byte is received
		//Serial.print(F("Register 0x6B is set to:"));
		//Serial.println(Wire.read(),BIN);
		//
		//Wire.beginTransmission(MPU6050_ADDRESS);                             //Start communication with the gyro
		//Wire.write(GYRO_CONFIG);                                            //GYRO_CONFIG register
		//Wire.write(0x08);                                            //Set the register bits as 00001000 (500dps full scale)
		//Wire.endTransmission();                                      //End the transmission
		//
		//Wire.beginTransmission(MPU6050_ADDRESS);                             //Start communication with the gyro (adress 1101001)
		//Wire.write(GYRO_CONFIG);                                            //Start reading @ register 28h and auto increment with every read
		//Wire.endTransmission();                                      //End the transmission
		//Wire.requestFrom(MPU6050_ADDRESS, 1);                                //Request 1 bytes from the gyro
		//while(Wire.available() < 1);                                 //Wait until the 1 byte is received
		//Serial.print(F("Register 0x1B is set to:"));
		//Serial.println(Wire.read(),BIN);
//
//}
#define temparrlen 5
float temparr[temparrlen];
float ReadTemperture()
{
	
    int cnt=0;
	int emergancyexit = 20;
    while (cnt < temparrlen)
	{	
		emergancyexit--;
		if (emergancyexit == 0) return INVALID_TEMPERATURE;
		
		temparr[cnt] = ReadFromSensorTemperature();
		delay(1);
		if (temparr[cnt] == INVALID_TEMPERATURE) continue;
		cnt++;
	} 
	
	for (byte i=0; i<temparrlen;i++)
	{
		byte tCnt =0;
		for (byte j=0;j<temparrlen;j++)
		{
			float dif = temparr[i]-temparr[j];
			float difa = fabs(dif);
			if (difa < 0.5) tCnt++;
		}
		if (tCnt > 3) return temparr[i];
	}
	
	return INVALID_TEMPERATURE;
}


float ReadFromSensorTemperature(){
 tempSensor.measure(&temperature, &humidity, &dewpoint);
 return temperature;
}

char * floatToString(char * outstr, float value, int places, int minwidth, bool rightjustify) {
	// this is used to write a float value to string, outstr.  oustr is also the return value.
	int digit;
	float tens = 0.1;
	int tenscount = 0;
	int i;
	float tempfloat = value;
	int c = 0;
	int charcount = 1;
	int extra = 0;
	// make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
	// if this rounding step isn't here, the value  54.321 prints as 54.3209

	// calculate rounding term d:   0.5/pow(10,places)
	float d = 0.5;
	if (value < 0)
	d *= -1.0;
	// divide by ten for each decimal place
	for (i = 0; i < places; i++)
	d/= 10.0;
	// this small addition, combined with truncation will round our values properly
	tempfloat +=  d;

	// first get value tens to be the large power of ten less than value
	if (value < 0)
	tempfloat *= -1.0;
	while ((tens * 10.0) <= tempfloat) {
		tens *= 10.0;
		tenscount += 1;
	}

	if (tenscount > 0)
	charcount += tenscount;
	else
	charcount += 1;

	if (value < 0)
	charcount += 1;
	charcount += 1 + places;

	minwidth += 1; // both count the null final character
	if (minwidth > charcount){
		extra = minwidth - charcount;
		charcount = minwidth;
	}

	if (extra > 0 and rightjustify) {
		for (int i = 0; i< extra; i++) {
			outstr[c++] = ' ';
		}
	}

	// write out the negative if needed
	if (value < 0)
	outstr[c++] = '-';

	if (tenscount == 0)
	outstr[c++] = '0';

	for (i=0; i< tenscount; i++) {
		digit = (int) (tempfloat/tens);
		itoa(digit, &outstr[c++], 10);
		tempfloat = tempfloat - ((float)digit * tens);
		tens /= 10.0;
	}

	// if no places after decimal, stop now and return

	// otherwise, write the point and continue on
	if (places > 0)
	outstr[c++] = '.';


	// now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
	for (i = 0; i < places; i++) {
		tempfloat *= 10.0;
		digit = (int) tempfloat;
		itoa(digit, &outstr[c++], 10);
		// once written, subtract off that digit
		tempfloat = tempfloat - (float) digit;
	}
	if (extra > 0 && !rightjustify) {
		for (int i = 0; i< extra; i++) {
			outstr[c++] = ' ';
		}
	}


	outstr[c++] = '\0';
	return outstr;
}