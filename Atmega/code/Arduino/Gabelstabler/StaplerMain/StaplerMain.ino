#include <SBUS.h>
#include <Servo.h>
#include <limits.h>
#include <math.h>

#include <SoftwareSerial.h>


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Remember to unplug the RX pin of your UNO when uploading this sketch.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define NUM_OF_CHANNEL 16

#define CHANNEL_UpDown        1 // T2, J2
#define CHANNEL_Tilt          2 // T1, J1
#define CHANNEL_Speed         4 // T3, J3
#define CHANNEL_Steering      3 // T3, J4

#define CHANNEL_LightON       5 // SF, ZU1
#define CHANNEL_Blink         7 // SE, ZU3
#define CHANNEL_Horn          8 // SH, ZU4
#define CHANNEL_Beep          9 // SG, ZU5

const int SERVOPIN_Steering   =  12; //P
const int SERVOPIN_Lift       =  11; //O
const int SERVOPIN_Tilt       =  10; //N
const int DIGPIN_Blink =        9;
const int DIGPIN_LIGHT =        7;
const int PWMPIN_Speed =        6;
const int PWMPIN_BUZZER =       5;
const int DIGPIN_Direction   =  4;

const int ANLGINPIN_Voltage   =  A3;

#define TRIM_Steering -125
#define ENDPOINTLOW_Steering 1015
#define ENDPOINTHIGH_Steering 1800

#define ENDPOINTLOW_Lift 950
#define ENDPOINTHIGH_Lift 2055

#define Switch_ON          1
#define Switch_Middle      0
#define Switch_OFF        -1


#define _DEBUG
#ifdef DEBUG
#define DEBUGLIGHT
#define DEBUGSPEED
#define DEBUGBZZER
#define DEBUGSTEERING
#define DEBUGLIFT
#define DEBUGTILT
#define DEBUGBLINK
#define DEBUGVOLTAGE

// connect zwo wires: A4 (myTX) to RXI and GND to GND
const int myTX =  A4;      
const int myRX =  A5;      // unplugged, just for SoftwareSerial init
SoftwareSerial mySerial(myRX, myTX); 
#endif

SBUS sbus(Serial);
Servo servoSteering;
Servo servoLift;
Servo servoTilt;


#define HORNSOUND 2222
#define BEEPSOUND1 2222
#define BEEPSOUND2 2422

#define VOLTAGE_FACT 0.98799
#define MIN_VOLTAGE 6.4
double sensorValue = -1.0;
double getVoltage()
{
  if (sensorValue < 0.0)
  {
    sensorValue = analogRead(ANLGINPIN_Voltage)*VOLTAGE_FACT;
  }
  else
  {
    sensorValue = sensorValue * 0.99 + analogRead(ANLGINPIN_Voltage)*0.01 *VOLTAGE_FACT;
  }
  
  double voltValue  = sensorValue/100.0;
  #ifdef DEBUGVOLTAGE
    mySerial.print("DEBUGVOLTAGE: ");
    mySerial.print(analogRead(ANLGINPIN_Voltage));
    mySerial.print("\t");
    mySerial.println(voltValue );
    
    #endif
  return voltValue;
}

boolean batteryLow()
{
  return getVoltage()< MIN_VOLTAGE;
}

ISR(TIMER2_COMPA_vect)
{
  //sbus.process();
}
int liftNeutral = ENDPOINTLOW_Lift ;
int tiltNeutral = 1500; 

int liftMicroseconds = liftNeutral;
int tiltMicroseconds = tiltNeutral;
void setup()
{
  pinMode(PWMPIN_Speed, OUTPUT);
  analogWrite(PWMPIN_Speed, 0);   
  pinMode(DIGPIN_Blink, OUTPUT);
  pinMode(DIGPIN_LIGHT, OUTPUT);
  pinMode(DIGPIN_Direction, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  
  
  
  sbus.begin();
  servoSteering.attach(SERVOPIN_Steering);
  servoTilt.attach(SERVOPIN_Tilt);
  servoLift.attach(SERVOPIN_Lift);

#ifdef DEBUG
  mySerial.begin(57600);
#endif  
  doBeep(0);
  servoLift.writeMicroseconds(liftMicroseconds);    
  servoTilt.writeMicroseconds(tiltMicroseconds);
  getVoltage();
}

unsigned long previousMillisTimerSBUS = 0;
boolean firsttime = true;
void loop()
{
  unsigned long currentMillis = millis();

  if (batteryLow())
  {
    digitalWrite(DIGPIN_LIGHT, LOW);   
    digitalWrite(LED_BUILTIN, LOW);     
    delay(200);
    digitalWrite(DIGPIN_LIGHT, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);        
    delay(200);
  }
    
  if (currentMillis - previousMillisTimerSBUS >= 10) 
  {
    previousMillisTimerSBUS = currentMillis;
    sbus.process();
  }
  
  int blinkOnOff = decodeSwitch(CHANNEL_Blink);

  if (blinkOnOff == Switch_OFF)
  {
    analogWrite(PWMPIN_Speed, 0);   
    liftMicroseconds = liftNeutral;
    tiltMicroseconds = tiltNeutral;
    servoLift.writeMicroseconds(liftMicroseconds);    
    servoTilt.writeMicroseconds(tiltMicroseconds);
    return;
  }

  if (channelsUP())
  {
    digitalWrite(LED_BUILTIN, LOW);     
    ProcessLightChannel();
    ProcessBlinkChannel();
    ProcessSpeedChannel();
    ProcessBeepChannel();
    ProcessSteeringChannel();
    ProcessLiftChannel();
    ProcessTiltChannel();
  }
}
boolean channelISUP = false;
boolean channelsUP()
{
  if (channelISUP) return true;
  
  for (int i =1; i < 5; i++)
  {
    //buggy, todo, check speed == middleposition
    if (sbus.getChannel(i) < 800) return false;
  }
  channelISUP = true;
  return true;
}

int steeringMilli =0;
void ProcessSteeringChannel()
{
  int newSteeringMilli = getChannelMapped(CHANNEL_Steering) + TRIM_Steering;
  if (newSteeringMilli != steeringMilli)
  {
    steeringMilli = newSteeringMilli;
    if(newSteeringMilli < ENDPOINTLOW_Steering) newSteeringMilli = ENDPOINTLOW_Steering;
    if(newSteeringMilli > ENDPOINTHIGH_Steering ) newSteeringMilli = ENDPOINTHIGH_Steering;
    servoSteering.writeMicroseconds(newSteeringMilli);
    #ifdef DEBUGTILT
    mySerial.print("servoSteering: ");
    mySerial.print(newSteeringMilli);
    mySerial.print("\t");
    mySerial.println(steeringMilli);
    #endif
  }
}

unsigned long previousMillisTimerLift = 0;
void ProcessLiftChannel()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisTimerLift >= 100) 
  {
    previousMillisTimerLift = currentMillis;
    int newLiftMilli = getChannelMapped(CHANNEL_UpDown);
    int newLiftDelta = (newLiftMilli-1500) / 10;
    if (abs(newLiftDelta) > 1)
    {
      liftMicroseconds += newLiftDelta;
      if(liftMicroseconds < ENDPOINTLOW_Lift) liftMicroseconds = ENDPOINTLOW_Lift;
      if(liftMicroseconds > ENDPOINTHIGH_Lift) liftMicroseconds = ENDPOINTHIGH_Lift;
      servoLift.writeMicroseconds(liftMicroseconds);
      #ifdef DEBUGLIFT
      mySerial.print("servoLift: ");
      mySerial.print("\t");
      mySerial.print(newLiftMilli);
      mySerial.print("\t");
      mySerial.print(liftMicroseconds);
      mySerial.print("\t");
      mySerial.println(newLiftDelta);
      #endif
    }
    
  }
}

unsigned long previousMillisTimerTilt = 0;
void ProcessTiltChannel()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisTimerTilt >= 10) 
  {
    previousMillisTimerTilt = currentMillis;
    int newTiltMilli = getChannelMapped(CHANNEL_Tilt);
    int newTiltDelta = (newTiltMilli-1500) / 30;
    if (abs(newTiltDelta) > 1)
    {
      tiltMicroseconds += newTiltDelta;
      if(tiltMicroseconds < 1000) tiltMicroseconds = 1000;
      if(tiltMicroseconds > 2000) tiltMicroseconds = 2000;
      
      servoTilt.writeMicroseconds(tiltMicroseconds);
      
      #ifdef DEBUGTILT
      mySerial.print("servoTilt: ");
      mySerial.print("\t");
      mySerial.print(newTiltMilli);
      mySerial.print("\t");
      mySerial.print(tiltMicroseconds);
      mySerial.print("\t");
      mySerial.println(newTiltDelta);
      #endif
    }
    
  }
}


int lightOnOff = Switch_OFF;
void ProcessLightChannel()
{
  int newlightOnOff = decodeSwitch(CHANNEL_LightON);
  if (newlightOnOff != lightOnOff) {
    lightOnOff = newlightOnOff;
    int state;
    if (lightOnOff == Switch_OFF)
    {
      state = LOW;
    }
    else
    {
      state = HIGH;
    }
    digitalWrite(DIGPIN_LIGHT, state);   
    #ifdef DEBUGLIGHT
    mySerial.print("ProcessLightChannel: ");
    mySerial.print(lightOnOff);
    mySerial.println("");
    #endif    
  }
}

int blinkPinState = LOW;
unsigned long previousMillisTimerBlink = 0;
void ProcessBlinkChannel()
{
  int blinkOnOff = decodeSwitch(CHANNEL_Blink);

  if ((blinkOnOff != Switch_ON) && (blinkPinState == HIGH))
  {
    blinkPinState = LOW;
    digitalWrite(DIGPIN_Blink, blinkPinState);   
  }

  if (blinkOnOff == Switch_ON)
  {
    unsigned long currentMillis = millis();
    int blinkdelay = 50;
    if (blinkPinState == LOW)
      blinkdelay = 400;
    if (currentMillis - previousMillisTimerBlink >= blinkdelay) 
    {
      previousMillisTimerBlink = currentMillis;
      
      if (blinkPinState == LOW)
        blinkPinState = HIGH;
      else
        blinkPinState = LOW;
      
      digitalWrite(DIGPIN_Blink, blinkPinState);   
      
      #ifdef DEBUGBLINK
      mySerial.print("blinkPinState: ");
      mySerial.print(blinkPinState);
      mySerial.println("");
      #endif    
      
    }
  }
}


int speedMilli =0;
boolean beepEnabled = false;
void ProcessSpeedChannel()
{
  if (sbus.getFailsafeStatus() == SBUS_FAILSAFE_ACTIVE)
  {
    analogWrite(PWMPIN_Speed, 0);   
    return;
  }
  
  int newSpeedMilli = getChannelMapped(CHANNEL_Speed);
  if (newSpeedMilli != speedMilli) {
    
    speedMilli = newSpeedMilli;
    boolean turnForward = true;
    int calSpeed = speedMilli -1500;
    if (calSpeed < 0)
    {
      turnForward = false;
      if (calSpeed < -20) 
      {
        beepEnabled  = true;
      }
      else
      {
        beepEnabled  = false;
      }
    }
    else
    {
      beepEnabled  = false;
      turnForward = true;
    }
    
    int speedPWM  = map(abs(calSpeed), 10,495,0,255);
    if (speedPWM  > 255) speedPWM = 255;
    if (speedPWM  <0 ) speedPWM = 0;
    analogWrite(PWMPIN_Speed, speedPWM);   
    digitalWrite(DIGPIN_Direction, turnForward);
    
    #ifdef DEBUGSPEED
    mySerial.print("ProcessSpeed: ");
    mySerial.print(speedMilli);
    mySerial.print("\t");
    mySerial.print(calSpeed);
    mySerial.print("\t");
    mySerial.print(speedPWM);
    mySerial.print("\t");
    mySerial.print(turnForward);
    mySerial.print("\t");
    mySerial.print(beepEnabled );
    mySerial.println("");
    #endif    
  }
}

int hornSwitch = Switch_OFF;
int beepSwitch = Switch_OFF;
byte beepON = false;
byte beepSound1 = false;
unsigned long previousMillis = 0;
boolean hornSwitchPressed = false;
void ProcessBeepChannel()
{
  boolean stateChanged = false;
  int newHornSwitch = decodeSwitch(CHANNEL_Horn);
  if (hornSwitch != newHornSwitch)
  {
    stateChanged = true;
    hornSwitch = newHornSwitch;
    if (hornSwitch == Switch_ON)
    {
      doBeep(HORNSOUND);
      hornSwitchPressed = true;
    }
    else
    {
      if (hornSwitchPressed)
      {
        hornSwitchPressed = false;
        doBeep(0);
      }
    }
  }
  
  int newBeepSwitch = decodeSwitch(CHANNEL_Beep);
  if (beepSwitch != newBeepSwitch)
  {
    beepSwitch = newBeepSwitch;
    stateChanged = true;
  }
  
  if ((hornSwitch == Switch_OFF) && ((beepSwitch == Switch_OFF) || ((beepSwitch == Switch_Middle) && !beepEnabled)))
  {
    if (beepON)
    {
      doBeep(0);
      beepON = !beepON;
      return;
    }
  }
  
  if (((beepSwitch == Switch_ON) || ( (beepSwitch == Switch_Middle) && beepEnabled)) && (hornSwitch != Switch_ON))
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 250) 
    {
      previousMillis = currentMillis;
      beepON = !beepON;
      if (beepON)
      {
        if (beepSound1) 
        {
          doBeep(BEEPSOUND1);
        }
        else
        {
          doBeep(BEEPSOUND2);
        }
        beepSound1 = !beepSound1;
      }
      else
      {
        doBeep(0);
      }
    }
  }
  
  #ifdef DEBUGBZZER
  if (stateChanged)
  {
    mySerial.print("ProcessBeepChannel: ");
    mySerial.print(hornSwitch);
    mySerial.print("\t");
    mySerial.print(beepSwitch);
    mySerial.println("");
  }
  #endif    
}

void doBeep(int value)
{
  if (value > 0)
    analogWrite(PWMPIN_BUZZER, 76); 
   else
    analogWrite(PWMPIN_BUZZER, LOW); 
}
int currentC[NUM_OF_CHANNEL+1];
void printChannel(int channel, int value)
{
  #ifdef DEBUG
  if (channel < 1) return;
  if (channel > NUM_OF_CHANNEL) return;
  
  if (currentC[channel] == value) return;
  
  currentC[channel] =  value;
  mySerial.print("Rawprint: ");
  mySerial.print(channel);
  mySerial.print("\t");
  mySerial.print(currentC[channel]);
  mySerial.print("\n");
  #endif
}

int getChannelMapped(int channel)
{
  return getChannelMapped(channel, 1000,2000);
}

int getChannelMapped(int channel, int low, int high)
{
  int value =  sbus.getChannel(channel);
  return (int)map(value, 350,1700,low,high);
}

int getMilliToPWM(int milli)
{
  int newMilli = map(milli, 1010,1990,0,255);
  if (newMilli > 255) return 255;
  if (newMilli <0 ) return 0;
  return newMilli;
}

int decodeSwitch(int channel)
{
  int switchMilli = getChannelMapped(channel);  
  if ( switchMilli < 1333) return Switch_OFF;
  if ( switchMilli > 1666) return Switch_ON;
  return Switch_Middle;
}
