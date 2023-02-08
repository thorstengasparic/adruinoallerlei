/*
 * GlobalValues.h
 *
 * Created: 8/16/2012 7:20:55 AM
 *  Author: hefny
 */ 


#ifndef GLOBALVALUES_H_
#define GLOBALVALUES_H_



#include "typedefs.h"
#include "IO_config.h"
///////////////////////////// Define Section


//#define DEBUG_ME


#define PID_I_LEAK_RATE	0.01
int8_t SystemActions;
#define SYS_ACT_NON					0b00000000
#define SET_SYS_ACT_NON				(SystemActions & 0b00000000)
#define SYS_ACT_REBOOT				0b00000001
#define IS_SYS_ACT_REBOOT			(SystemActions & 0b00000001)
#define SET_SYS_ACT_REBOOT			(SystemActions | 0b00000001)
#define CLR_SYS_ACT_REBOOT			(SystemActions & 0b11111110)
#define SYS_ACT_DISARM				0b00000010
#define IS_SYS_ACT_DISARM			(SystemActions & 0b00000010)
#define SET_SYS_ACT_DISARM			(SystemActions | 0b00000010)
#define CLR_SYS_ACT_DISARM			(SystemActions & 0b11111101)


int8_t SystemErrorType; 
#define SYS_ERR_NON				0b00000000
#define CLR_SYS_ERR_SIGNAL		(SystemErrorType & 0b11111110)
#define SET_SYS_ERR_SIGNAL		(SystemErrorType | 0b00000001)
#define IS_SYS_ERR_SIGNAL		(SystemErrorType & 0b00000001)	
#define CLR_SYS_ERR_VOLTAGE		(SystemErrorType & 0b11111101)
#define SET_SYS_ERR_VOLTAGE		(SystemErrorType | 0b00000010)
#define IS_SYS_ERR_VOLTAGE		(SystemErrorType & 0b00000010)

//Timer
//#define 

// LED
#define LED_LONG_TOGGLE  80  // 800 
#define LED_SHORT_TOGGLE 30 // 400

// LCD
#define LCD_RefreashRate	10
char sXDeg[20];

 

////////////////// STICK READINGS
// Stick Arming - enable this line to enable Stick arming
#define STICK_LEFT					 400	//  the total range is from [-500, 500]
#define STICK_RIGHT					-400	
#define STICKThrottle_HIGH			 850	//  the total range is from [ 0, 1000]
#define STICKThrottle_ARMING		  50	//  the total range is from [ 0, 1000]
#define STICKPOSITION_LONG_TIME		 305  // minimum time duration for stick to accept a command.
#define STICKPOSITION_SHORT_TIME	  80
#define STICK_DEADBAND				  15
#define DISARM_TIME					1000
///////////////// EOD STICK READINGS


// Max Collective
// limits the maximum stick collective (range 80->100  100=Off)
// this allows gyros to stabilize better when full throttle applied
#define MAX_COLLECTIVE		800
// trimming value for motors when generating PWM signals.
#define MOTORS_HIGH_VALUE	1150 //1100 = 2.0 
#define MOTORS_IDLE_VALUE	100
#define SERVO_IN_MIDDLE		550
// Defines output rate to ESC/Servo
// either define by setting ESC_RATE (Max is approx 495Hz)
// uses Timer 1 ticks to control output rate.
#define ESC_RATE 250	// in Hz
//#define ESC_RATE 400	// in Hz (at SINGLE_COPTER and DUAL_COPTER)
//#define ESC_RATE 450	// in Hz
//#define ESC_RATE 495	// in Hz
#define PWM_LOW_PULSE_INTERVAL 1000000 / ESC_RATE // time in ms for a delay.
#define BASE_PULSE				800 //950 //1000   //  :: I reduced it from 1120 to 1104 as trimming.





////////////////////////////// Variables Section

//#define RX_Div_Factor	16	// div by 16

// Receiver Signal Values
volatile uint8_t ActiveRXIndex;			// 0: primary rx, 1: secondary rx, 3: buddy mode [primary & secondary] 

volatile uint16_t RX_Length   [2][RXChannels];
volatile int16_t  RX_Latest   [2][RXChannels];   // the actual RX values that are used for calculations.
int16_t			  RX_Snapshot    [RXChannels];
int16_t			  RX_Snapshot_1  [RXChannels];
// used for calibration...not initialized... true values are in Config in case IsCalibrated & Stick = True.
uint16_t RX_MAX_raw			  [2][RXChannels];
uint16_t RX_MIN_raw			  [2][RXChannels];
	

BOOL	UIEnableStickCommands;
BOOL	IsArmed;

uint16_t Sensors_dt; // time in 100us between sensors reading

// Motors Signals
int16_t MotorOut[4];


int8_t nFlyingModes;   
#define FLYINGMODE_ACRO			0b00000001
#define FLYINGMODE_LEVEL		0b00000010
#define FLYINGMODE_ALTHOLD		0b00000100	// ALT HOLD & LEVEL
#define IS_FLYINGMODE_LEVEL			(nFlyingModes & FLYINGMODE_LEVEL)
#define IS_FLYINGMODE_ACRO			(nFlyingModes & FLYINGMODE_ACRO)
#define IS_FLYINGMODE_ALTHOLD		(nFlyingModes & FLYINGMODE_ALTHOLD)


// Holds final calculated values of Pitch, Roll, Yaw based on the sensors and stabilization algorithm
int16_t gyroPitch;
int16_t gyroRoll;
int16_t gyroYaw;


double NavY, NavX;
///////////////////////////////////////////////////
// Intermediate results for IMU_CalculateAngles
//gyros
	//double gyroXangle;
	//double gyroYangle;
	//double gyroZangle;

	//accelerometers
	//double accXangle;
	//double accYangle;
	//float accZangle;
///////////////////////////////////////////////////

double CompGyroRoll;
double CompGyroPitch;
double CompGyroZ;	
	

double CompAccZ;	

volatile double AngleRoll;
volatile double AnglePitch;
volatile double AngleZ;


#define GYRO_MIN	-10
#define GYRO_MAX	10
#define ACC_MIN		-10
#define ACC_MAX		10

//int16_t StabilityMatrix_GX[20];
//int16_t StabilityMatrix_GY[20];

// USed for Scaling
//double Pitch_Ratio;
//double Yaw_Ratio;
//double Acc_Ratio;


// Contains Values of PID and their limit.... configured from the LCD.
typedef struct 
{
	//int16_t minSource,maxSource;
	//int16_t minDest,maxDest;
	int16_t 
			_P,_PLimit, 
			_I, _ILimit, 
			_D, _DLimit, 
			ComplementaryFilterAlpha;   // this value ranges from 0 [no filter] to 999[smoothest] ... this is the complementry filter ALPHA
} pid_param_t;


// holds runtime values for PID calculation 
typedef struct 
{
	//int16_t minSource,maxSource;
	//int16_t minDest,maxDest;
	float P,			// float value of pid_param_t._P * Value
	 I,
	 D,			
	 Error;		// Old value (n-1)
	 
} pid_terms_t;


// Structure that hold PID calculated values for Gyro & ACC
pid_terms_t PID_GyroTerms[3], PID_AccTerms[3], PID_SonarTerms[1];

// TIMERS
uint16_t CurrentTCNT1_X;				// equal to TCNT1_X value -- read every loop entry [it provide a safe read for TCNT1_X... it is updated only @ start of the loop
volatile uint16_t TCNT0_X;
volatile uint16_t TCNT1_X;				// TCNT1_X click every 0.0032768 sec [1 sec = 305.17578125 TCNT1_X]
volatile uint16_t TCNT2_X;				// TCNT2  overflows every  3.2us x 0xff = 0.0008192 sec,  TCNT2_X value tick every 819.2 us and overflow every 53.6870912 sec
volatile uint16_t TCNT1H_OLD;	
uint16_t TimeDef ; 	
//volatile uint16_t OCR0A_X;
uint16_t TCNT1_X_snapshot1;				
uint16_t TCNT_X_snapshot2;
uint16_t TCNT_X_snapshotAutoDisarm;
//uint16_t TCNT1_X_GlobalTimer;
volatile BOOL UpdateServo;
BOOL bResetTCNR1_X;



// ADC Values
// Order is aligned with Menu Screens
#define ACC_PITCH_Index			3   // affected by Pitch and is in reverse direction with GyroY .... it is positive when backword.
#define ACC_ROLL_Index			4	// affected by Roll and is in reverse direction with GyroX .... it is positive when right.	
#define ACC_Z_Index				5
#define GYRO_ROLL_Index			0
#define GYRO_PITCH_Index		1
#define GYRO_Z_Index			2
#define V_BAT_Index				6
#define SENSORS_IMU				6
#define SENSORS_ALL				7
static uint8_t SensorsIndex[SENSORS_ALL] = {GYRO_ROLL_PNUM,GYRO_PITCH_PNUM,GYRO_Z_PNUM,ACC_PITCH_PNUM,ACC_ROLL_PNUM,ACC_Z_PNUM,V_BAT_PNUM};


#define ACC_Z_1G				256;
#define	GYRO_RATE				0.00077 //0.00077 //0.027  //0.045
#define RAD_TO_DEG				76.45    //57.324   [for 120]
#define DEG_TO_RAD				0.01308		//(PI/2 = 120)
#define GYRO_RATE_x_IVR_RAD		0.00058875	// = GYRO_RATE * ((3.14/2)/100) //0.01744444444444444444444444444444
volatile double  Sensors_Latest [8];
/////////////////////////////////////////

// MISC SENSORS

#define NO_MISC_SENSORS					0
#define SET_MISC_SENSOR_SONAR_ENABLED	(Config.MiscSensors	| 0b00000001)
#define SET_MISC_SENSOR_SONAR_DISABLED	(Config.MiscSensors	& 0b11111110)
#define IS_MISC_SENSOR_SONAR_ENABLED	(Config.MiscSensors	& 0b00000001)
#define SONAR_TO_cm_Convert				27.6233f		
#define SONAR_TO_cm_Convert_BIG			(27.6233f * 256.0f)		
#define SONAR_ALTITUDE_HOLD_REGION		15.0f
#define THROTTLE_DEAD_RANGE				20;
uint16_t LastAltitudeHold;
double Landing;							
double AltDiff;

/////////////////////////////////////////


// BAUD RATES
// Thanks to Retlaw: http://www.rcgroups.com/forums/showpost.php?p=24904574&postcount=258

#define BAUD_115200		10 	
#define BAUD_57600		20 	
#define BAUD_38400		30 
#define BAUD_19200		60 
#define BAUD_14400		80
#define BAUD_9600		120 

#define SERIAL_BAUD_RATE	BAUD_115200

// TEMP
volatile char Result[8]; 
volatile uint16_t nResult[8];


#define FRAMETYPE_QUADCOPTER		1
#define FRAMETYPE_TRICOPTER			2


#define CALIBRATED_ALL				7
#define CALIBRATED_Stick_ALL		3
#define CALIBRATED_Stick_PRIMARY	1
#define CALIBRATED_Stick_SECONDARY	2
#define CALIBRATED_SENSOR			4

// eeProm data structure
#define IMU_SelfLevelMode		1
#define RX_mode_UARTMode		0xff
#define RX_mode_BuddyMode		0x00
#define ESCCalibration_ON		1
#define ESCCalibration_OFF		0
#define QuadFlyingMode_PLUS		0	 
#define QuadFlyingMode_X		1
#define TRIFlyingMode_Y			0 
#define TRIFlyingMode_A			1

	
//limits for sensor testing
#define AccLowLimit			450
#define AccHighLimit		850
#define GyroLowLimit		450 
#define GyroHighLimit		800 


#define Mixer_Quad_PLUS		0
#define Mixer_Quad_X		1
#define Mixer_TRI			2


#define PITCH_INDEX	0
#define ROLL_INDEX	1
#define YAW_INDEX	2
#define Z_INDEX		2


#define GYRO_NORMAL			 1
#define GYRO_REVERSE		-1

typedef struct  
{
	uint8_t signature;				//	offset: +0
	uint16_t Version;
	uint8_t IsCalibrated;			//	offset: +1		
	uint8_t RX_mode;				//	offset: +2		 01 [Secondary RX only and PD are used of UART"PD2-PD3"]  02[Buddy mode both Primary & Secondary RX are used]
	uint8_t SelfLevelMode;			//	offset: +3	
	uint8_t ArmingMode;				//	offset: +4	
	uint8_t AutoDisarm;				//	offset: +5	
	uint8_t IsESCCalibration;		//	offset: +6	
	uint8_t FrameType;				//	offset: +7	
	uint8_t BoardOrientationMode;	//	offset: +8	
	uint8_t QuadFlyingMode;			//	offset: +9	
	uint8_t LCDContrast;			//	offset: +10	
	uint8_t ThrottleMin;			//	offset: +11	
	uint8_t StickScaling;			//	offset: +12	
	uint8_t MiscSensors;			//	offset: +13	0b00000001		bit0: true/false SONAR
	
	pid_param_t GyroParams[3];		
	pid_param_t AccParams[3];		
	pid_param_t SonarParams[1];		
	
	uint8_t VoltageAlarm;			
	int8_t	Acc_Pitch_Trim;
	int8_t	Acc_Roll_Trim;
	//model_t Mixer;
	uint16_t RX_Mid[2][RXChannels]; 
	uint16_t RX_Min[2][RXChannels];
	uint8_t Reserved[4];
	double Sensor_zero[SENSORS_ALL];
	int8_t  RX_DiV_Value[2][RXChannels];
	int8_t	ReverseYAW;
	int8_t	PitchRollLinked;
	
	
} config_t;

config_t Config;




#endif /* GLOBALVALUES_H_ */