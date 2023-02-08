
#include <arduino.h>
#include <math.h>
#include "Common.h"

#include "CubeCommand.h"


MovementProtokoll::MovementProtokoll()
{
  	inputString.reserve(maxinputbuffer);
    outString.reserve(maxinputbuffer);
};

bool MovementProtokoll::commandAvailable()
{
  while (Serial.available()) 
  {
      char inChar = (char)Serial.read();
      if (inChar == '\n') 
      {
        outString = inputString;
        inputString = "";
        inputString.reserve(maxinputbuffer);
        return true;
      }
      else
      {
        inputString += inChar;
      }
    }
    return false;
};

String MovementProtokoll::getRawCommand()
{
  return outString; 
};

void MovementProtokoll::ackCommand(String command)
{
  command = ACK+command ;
  Serial.println(command );
};

void MovementProtokoll::SendHeartbeat()
    {
      unsigned long currentMillis = millis();
      if (currentMillis - heartbeatMillis >  heartbeatMillisIntervall)
      {
        heartbeatMillis = currentMillis;
        Serial.println(heartbeat);
      }
    };
