#include <arduino.h>
#include <math.h>

#define _StepperDriverDebug 

#ifndef GATSTEPPERDRIVER_H
#define GATSTEPPERDRIVER_H

#include "Common.h"

class GATStepperDriver
{
/*
  #define defaultSpeed  800
  #define defaultHighTime  50
  
  #define defaultStepsPerRevolution  200
  #define defaultRampDelay  100
  #define defaultrampWidth  10
*/
  /*
  #define defaultSpeed  400
  #define defaultHighTime  100
  #define defaultStepsPerRevolution  200*2
  #define defaultRampDelay  10
  #define defaultrampWidth  5
*/
  
  
	private:
    byte dirPin; 
    byte stepPin; 
    
    int stepsPerRevolution;
    double degreePerStep;

    int speedPerStep;
    int speedHighTime;

    long stepsToGo = 0;
    
    unsigned long previousMicrosLow = 0;
    unsigned long previousMicrosHigh = 0;

    long rampWidth = defaultrampWidth ;
    long rampCounter = 0;
    
  public:
    long totalSteps = 0;
    boolean debug = false;
    
    GATStepperDriver(int  dirPinIn, int stepPinIn );
    
	void SetSpeedToHigh();
    void SetSpeedToLow();
    void SetSpeed(int speedLowInMicros);
    void SetSpeed(int speedLowInMicros, int speedHighInMicros);
    void SetStepsPerRevolution(int stepsPerRevolutionIn);
    void TurnSteps(int steps);
    void TurnAngle(double angle);
    int PerformTurn();
    int PerformTurn01();
};

#endif