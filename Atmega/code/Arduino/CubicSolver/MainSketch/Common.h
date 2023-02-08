#include <arduino.h>
#ifndef COMMON_H
#define COMMON_H
  
  //  Communication Section
  #define maxinputbuffer 16
  #define heartbeat "H"
  #define ACK       "A"

  //  Stepper ramp Section
  #define defaultLowSpeed 1500
  #define defaultHighSpeed 1500

  #define defaultSpeed  800
  #define defaultHighTime  300
  #define defaultStepsPerRevolution  200
  #define defaultRampDelay  100
  #define defaultrampWidth  10


#endif