/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
#include <arduino.h>
#include <math.h>

#include "GATStepperDriver.h"
#include "CubeCommand.h"



// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

GATStepperDriver stepper01 = GATStepperDriver(dirPin, stepPin);
MovementProtokoll commands = MovementProtokoll();

int doSteps = 100 ;
int curSpeed = 1200 ;

void setup() {
  //stepper01.SetSpeed(curSpeed);
  Serial.begin(115200); 
  while (!Serial) {}
  //stepper01.TurnSteps(doSteps);
}

void loop() {
  commands.SendHeartbeat();

  int steps = stepper01.PerformTurn01();
  if (steps == 0 )
  {
    //int customDelay = analogRead(A0); // Reads the potentiometer
    //curSpeed = map(customDelay, 0, 1023, 300,4000); 
    
    Serial.println(curSpeed);
    //stepper01.SetSpeed(curSpeed);
    doSteps *= -1;
    stepper01.TurnSteps(doSteps);
    delay (200);
  }

/*  if (commands.commandAvailable())
  {
    String cmd = commands.getRawCommand();
    commands.ackCommand(cmd);
  }
  */
}

