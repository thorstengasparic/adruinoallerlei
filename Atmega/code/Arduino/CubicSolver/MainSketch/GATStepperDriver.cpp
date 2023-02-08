#include <arduino.h>
#include <math.h>

#include "Common.h"
#include "GATStepperDriver.h"

  GATStepperDriver::GATStepperDriver(int  dirPinIn, int stepPinIn )
  {
   
    dirPin = dirPinIn; 
    stepPin = stepPinIn; 

    speedPerStep = defaultSpeed;
    speedHighTime = defaultHighTime;
    stepsToGo = 0;
    SetStepsPerRevolution(defaultStepsPerRevolution);
    
    previousMicrosLow =0;
    previousMicrosHigh =0;
    
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    
  };

  void GATStepperDriver::SetSpeedToHigh()
  {
    SetSpeed(defaultHighSpeed);
  }

  void GATStepperDriver::SetSpeedToLow()
  {
    SetSpeed(defaultLowSpeed);
  }

  void GATStepperDriver::SetSpeed(int speedLowInMicros)
  {
    SetSpeed(speedLowInMicros, round((double)speedLowInMicros * 0.75));
  }
  void GATStepperDriver::SetSpeed(int speedLowInMicros, int speedHighInMicros)
  {
    speedPerStep = speedLowInMicros;
    speedHighTime = speedHighInMicros;
  };

  void GATStepperDriver::SetStepsPerRevolution(int stepsPerRevolutionIn)
  {
    stepsPerRevolution = stepsPerRevolutionIn;
    degreePerStep = 360.0 /(double)stepsPerRevolution;
  };
  
  void GATStepperDriver::TurnSteps(int steps)
  {
    stepsToGo += steps;
    rampCounter = rampWidth;
  };

  void GATStepperDriver::TurnAngle(double angle)
  {
    TurnSteps(round(angle/degreePerStep));
  };

  int GATStepperDriver::PerformTurn()
  {
    if (stepsToGo == 0 )
    {
      previousMicrosLow = 0;
      previousMicrosHigh = 0;
      return 0;
    }
    unsigned long currentMicros = micros();
    if (stepsToGo > 0)
    {
      digitalWrite(dirPin, HIGH);      
    }
    else
    {
      digitalWrite(dirPin, LOW);      
    }

    long rampDelayStart = 0;
    long rampDelayStop = 0;
    if ((previousMicrosLow == 0) && (previousMicrosHigh == 0))
    {
      rampDelayStart = rampCounter*defaultRampDelay;
      long stepsToEnd = abs(stepsToGo);
      if (stepsToEnd <= rampWidth)
      {
        rampDelayStop = abs((rampWidth-stepsToEnd) *defaultRampDelay);
      }
      if (rampDelayStop > 0)
      {
        rampDelayStart = 0;
      }
  #ifdef StepperDriverDebug
      Serial.print(stepsToGo);

      Serial.print("\t");
      Serial.print(rampCounter);
      
      Serial.print("\t");
      Serial.print(rampDelayStart);
      
      Serial.print("\t");
      Serial.print(rampDelayStop);
      Serial.println("");
    #endif
    
      previousMicrosHigh = currentMicros;
      digitalWrite(stepPin, HIGH);      
    }

    if (previousMicrosHigh != 0) 
    {
      if (currentMicros - (previousMicrosHigh) >= speedHighTime + rampDelayStart + rampDelayStop) 
      {
        if (rampCounter > 0)
        {
          rampCounter--;
        }
        previousMicrosHigh =0;
        previousMicrosLow  = currentMicros;
        digitalWrite(stepPin, LOW);      
      }
    }
    if (previousMicrosLow != 0) {
      
      if (currentMicros - previousMicrosLow >= speedPerStep+rampDelayStart + rampDelayStop) 
      {
        previousMicrosHigh =0;
        previousMicrosLow  = 0;
        if (stepsToGo > 0)
        {
          stepsToGo--;
          totalSteps--;
        }
        else
        {
          stepsToGo++;
          totalSteps++;
        }
      }
      
    }
  
    return stepsToGo;
  };



int GATStepperDriver::PerformTurn01()
{
    if (stepsToGo == 0 )
    {
      previousMicrosLow = 0;
      previousMicrosHigh = 0;
      return 0;
    }

    unsigned long currentMicros = micros();
    
    if (stepsToGo > 0)
    {
      digitalWrite(dirPin, HIGH);      
    }
    else
    {
      digitalWrite(dirPin, LOW);      
    }

    if ((previousMicrosLow == 0) && (previousMicrosHigh == 0))
    {
      previousMicrosHigh = currentMicros;
      digitalWrite(stepPin, HIGH);      
      return stepsToGo;
    }

    if (previousMicrosHigh != 0) 
    {
      if (currentMicros - (previousMicrosHigh) >= speedHighTime) 
      {
        previousMicrosHigh =0;
        previousMicrosLow  = currentMicros;
        digitalWrite(stepPin, LOW);      
        return stepsToGo;
      }
    }
    
    if (previousMicrosLow != 0) {
      
      if (currentMicros - previousMicrosLow >= speedPerStep) 
      {
        previousMicrosHigh =0;
        previousMicrosLow  = 0;
        if (stepsToGo > 0)
        {
          stepsToGo--;
        }
        else
        {
          stepsToGo++;
        }
      }
    }
  
    return stepsToGo;
  };

