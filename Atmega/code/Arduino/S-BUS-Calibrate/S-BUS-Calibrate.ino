#include <SBUS.h>
#include <limits.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define NUM_OF_CHANNEL 16

const int refServoPin = 12;
const int refChannel = 0; // internal zero based index, on receiver 1 based

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// connect zwo wires: A4 (myTX) to RXI and GND to GND
const int myTX =  A4;      
const int myRX =  A5;      // unplugged, just for serial init

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Remember to unplug the RX pin of your UNO when uploading this sketch.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
SBUS sbus(Serial);
int maxC[NUM_OF_CHANNEL];
int currentC[NUM_OF_CHANNEL];
int minC[NUM_OF_CHANNEL];

SoftwareSerial mySerial(myRX, myTX); 

Servo servoRef;

// This is timer2, which triggers ever 1ms and processes the incoming SBUS datastream.
ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}

void setup()
{
  sbus.begin();
  mySerial.begin(57600);
  servoRef.attach(refServoPin);
  
  for(int i=0;i<NUM_OF_CHANNEL; i++)
  {
    SetChannel(i, INT_MAX);
  }
}

void loop()
{
  if (digitalRead(buttonPin)== HIGH) {
    digitalWrite(ledPin, HIGH);
    for(int i=0;i<NUM_OF_CHANNEL; i++)
    {
      printChannel(i);
    }
    while (digitalRead(buttonPin) == HIGH)
    {
      delay(10);
    }
     digitalWrite(ledPin, LOW);
     return;
  }
  int valRefServo = getChannelMapped(refChannel);
  servoRef.writeMicroseconds(valRefServo);
    
  for(int i=0;i<NUM_OF_CHANNEL; i++)
  {
    int valLast = currentC[i];
    int valCur = getChannelMapped(i);
    SetChannel(i, valCur);
    if (valLast != valCur)
    {
      printChannel(i);
    }
  }
  delay(1);
}

void SetChannel(int channel, int value)
{
  if((value == INT_MAX)|| (value == INT_MIN) || (value < 10))
  {
    minC[channel] = INT_MAX;
    maxC[channel] = INT_MIN;
    return;
  }
  
  if (channel < 0) return;
  if (channel >= NUM_OF_CHANNEL) return;

  currentC[channel] = value;
  
  if (minC[channel] > value)
  {
    minC[channel]= value;
  }
  if (maxC[channel] < value)
  {
    maxC[channel]= value;
  }
}

void printChannel(int channel)
{
  if (channel < 0) return;
  if (channel >= NUM_OF_CHANNEL) return;
  mySerial.print(channel+1);
  mySerial.print("\t");
  mySerial.print(currentC[channel]);
  mySerial.print("\t");
  mySerial.print(minC[channel]);
  mySerial.print("\t");
  mySerial.println(maxC[channel]);
  //mySerial.print("\t");
  //mySerial.println((int)map(currentC[channel], minC[channel],maxC[channel],1000,2000));
}

int getChannelMapped(int channel)
{
  int value =  sbus.getChannel(channel+1);
  return (int)map(value, 350,1700,1000,2000);
}
