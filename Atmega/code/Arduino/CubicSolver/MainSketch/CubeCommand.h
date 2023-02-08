#include <arduino.h>
#ifndef CUBECOMMAND_H
#define CUBECOMMAND_H

#include "Common.h"

class MovementProtokoll
{
  private:
    String inputString = "";         // a String to hold incoming data
    String outString = "";         // a String to hold return data
    bool stringComplete = false;  // whether the string is complete
    
    unsigned long  heartbeatMillisIntervall = 500;
    unsigned long  heartbeatMillis = 0;
    
  public:
    MovementProtokoll();
    
    bool commandAvailable();
    String getRawCommand();
    void SendHeartbeat();
    void ackCommand(String command);
};



#endif