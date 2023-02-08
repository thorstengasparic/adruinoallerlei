
#include <Arduino.h>

#include <Wire.h>
#include <OneWire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Ds18S20Min.h>

void adresseAusgeben(void );
#define ONE_WIRE_BUS 2 /* Digitalport Pin 2 definieren */
OneWire ds(ONE_WIRE_BUS); /* Ini oneWire instance */
Ds18S20Temperature  sensors(&ds);

char buffer[32];

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	//0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE1
	0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01
};
IPAddress ip(192, 168, 42, 95);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);


unsigned int counter = 0;
float tempvalue[_maxSensors];
void setup()
{
  Serial.begin(57600);
  Serial.println("Temperatur Messprogramm");
  delay(300);
  
  sensors.Begin();
  adresseAusgeben();

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  counter = 100000;
  
}
int curdev =0;
void loop()
{
  //sensors.Begin();
  //adresseAusgeben();
  //delay(1000);
  
   // listen for incoming clients
   counter ++;
   if (counter > 10000)
   {
		sensors.Begin();
		adresseAusgeben();
		counter =0;
		for(int dev =0; dev< _maxSensors; dev++)
		{
			tempvalue[dev] =sensors.getTemperatureById(dev, true);
		}
   }
   if ((counter % 500) == 0)
   {
	  tempvalue[curdev] =sensors.getTemperatureById(curdev, true);
	  curdev++;
	  if (curdev>=_maxSensors)
		 curdev =0;
   }
   EthernetClient client = server.available();
   if (client) {
	   Serial.println("new client");
	   // an http request ends with a blank line
	   boolean currentLineIsBlank = true;
	   while (client.connected()) {
		   if (client.available()) {
			   char c = client.read();
			   Serial.write(c);
			   // if you've gotten to the end of the line (received a newline
			   // character) and the line is blank, the http request has ended,
			   // so you can send a reply
			   if (c == '\n' && currentLineIsBlank) {
				   // send a standard http response header
				   client.println("HTTP/1.1 200 OK");
				   client.println("Content-Type: text/html");
				   client.println("Connection: close");  // the connection will be closed after completion of the response
				   client.println("Refresh: 1");  // refresh the page automatically every 5 sec
				   client.println();
				   client.println("<!DOCTYPE HTML>");
				   client.println("<html>");
				   // output the value of each analog input pin
				   //for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
					   //int sensorReading = analogRead(analogChannel);
					   //client.print("analog input ");
					   //client.print(analogChannel);
					   //client.print(" is ");
					   //client.print(sensorReading);
					   //client.println("<br />");
				   //}
				   
				   for(int dev =0; dev< _maxSensors; dev++)
				   {
				   	   byte *addr = sensors.sensors[dev];
					   client.print("S");
					   client.print(sensors.getAdress(dev, buffer));
					   client.print(":");
					   client.print(tempvalue[dev] );
					   client.println("<BR />");
					   if ( strstr(sensors.getAdress(dev, buffer), "(null)") == NULL) 
					   {
						   for(int i =0; i< _maxSensors; i++)
						   {
								if (i == dev) continue;
								if (strstr(sensors.getAdress(i, buffer), "(null)") == NULL) 
								{
									client.print("D");
									client.print(sensors.getAdress(dev, buffer) );
									client.print("-" );
									client.print(sensors.getAdress(i, buffer) );
									client.print(":");
									client.print(tempvalue[dev]-tempvalue[i] );
									client.println("<BR />");
								}
						   }
					   }
				   }
				   client.println("</html>");
				   break;
			   }
			   if (c == '\n') {
				   // you're starting a new line
				   currentLineIsBlank = true;
				   } else if (c != '\r') {
				   // you've gotten a character on the current line
				   currentLineIsBlank = false;
			   }
		   }
	   }
	   // give the web browser time to receive the data
	   delay(1);
	   // close the connection:
	   client.stop();
	   Serial.println("client disconnected");
   }
   delay(1);
}

void adresseAusgeben(void) {
	byte i;
	byte present = 0;
	
	byte *addr;

	Serial.print(sensors.Devicecount);
	Serial.println(" Devices found");// "\n\r" is NewLine

	for(int dev =0; dev< sensors.Devicecount; dev++)
	{
		addr = sensors.sensors[dev];
		Serial.print(dev);
		Serial.print(":");
		Serial.print(sensors.getAdress(dev, buffer));
		if ( OneWire::crc8( addr, 7) != addr[7]) {
			Serial.print("CRC is not valid!\n\r");
			return;
		}
		else
		{
			Serial.print("  -> ");
			Serial.print(sensors.getTemperatureById(dev, true) );
		}
		Serial.println("");
	}
	Serial.println();
	return;
}


