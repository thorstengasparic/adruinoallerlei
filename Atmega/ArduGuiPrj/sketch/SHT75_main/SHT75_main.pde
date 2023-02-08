#include <LibSHT75.h>


int ledPin =  13;    // LED connected to digital pin 13

// The setup() method runs once, when the sketch starts
Senserion sht75 = Senserion();
void setup()   {                
  // initialize the digital pin as an output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);     
//  sht75.Verbos = true;
//  sht75.debug = false;
}

// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()                     
{
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(1000);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(1000);                  // wait for a second
  char temp[10];
  char hum[10];
  char dew[10];
  sht75.Measure(temp, hum, dew);   
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(hum);
  Serial.print(" ");
  Serial.println(dew);
}
