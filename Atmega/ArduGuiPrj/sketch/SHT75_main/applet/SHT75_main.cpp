#define NOACK   0               /* Flags to tell read_byte routine whether */
#define ACK     1               /* or not to send an ACK after the read    */ 

/* Define the SHT7x commands to be their command codes */
#define         MEASURE_TEMP    0x03
#define         MEASURE_HUMI    0x05
#define         STATUS_REG_W    0x06
#define         STATUS_REG_R    0x07
#define         RESET           0x1e

/* Following constants are in microseconds */
#define         LONG_DELAY      delayMicroseconds(80)
#define         MEDIUM_DELAY    delayMicroseconds(40)
#define         SHORT_DELAY     delayMicroseconds(20)


#include "WProgram.h"
void setup();
void loop();
class Senserion
{
public:
	Senserion();
	Senserion(int SCK_Pin, int SHT_Pin);
	bool Measure(float*, float*, float*);   
        bool Measure(char *, char *, char *);
	unsigned char GetStatusRegister();
	bool SHT_Version4;	// SHT Version 3 or 4
	bool VDD_5V;	// Inpu Voltage 3.3V or 5.0V
	bool Verbos;
	unsigned char debug;          /* When set, intermediate data is printed */

private:
	void Reset();
	char sWriteByte(unsigned char value);
	char sReadByte (unsigned char sendAck);
	void sTransmitStart ();
	void sConnectionReset ();
	char sSoftReset();
	char sMeasure (unsigned char *pValue, unsigned char command, unsigned char singleFlag);
	void doCRC (unsigned char ch, unsigned char *crc);
	void calcTempHumid (float *pHumidity, float *pTemperature);
	float calcDewPoint (float humidity, float temperature);
	void splitFloat (float *fNum, int *pInt, char *pFrac, int decPlaces);
	void printReading (char *label, float *pVal, char *suffix);
	int m_Clock_Pin;
	int m_Data_Pin;
};

Senserion::Senserion()
{
	debug = false;
	m_Clock_Pin = 2; // default CLOCK
	m_Data_Pin = 3;  // default DATA
	SHT_Version4 = true;
	VDD_5V = true;
	Reset();
}

Senserion::Senserion(int Clock_Pin, int Data_Pin)
{
	Senserion();
	m_Clock_Pin = Clock_Pin;
	m_Data_Pin = Data_Pin;
	Reset();
}

void Senserion::Reset()
{
    pinMode (m_Clock_Pin, OUTPUT);
    sConnectionReset();
}


/**
 * sWriteByte
 *
 *      Routine to write a byte to the SHT/x and check for the acknowledge
 *
 * Parameters:
 *      @value          byte value to be written
 *      @dataport       data port to access
 *
 * Returns:
 *      0 for success, 1 if no Acknowledge received from SHT7x
 */
char Senserion::sWriteByte(unsigned char value)
{
    unsigned char ix;                   /* loop index */
    unsigned char error;                /* result of the write */

    pinMode (m_Data_Pin, OUTPUT);
    for (ix = 0x80; ix; ix >>= 1) {
        digitalWrite (m_Data_Pin, ix & value);/* Next bit to I/O port */
        SHORT_DELAY;			/* Shouldn't be needed */
        digitalWrite (m_Clock_Pin, HIGH);	/* Set clock signal high */
        MEDIUM_DELAY;			/* some delay needed */
        digitalWrite (m_Clock_Pin, LOW);	/* Set clock back to low */
    }
    pinMode (m_Data_Pin, INPUT);              /* Prepare to read the ACK bit */
    digitalWrite (m_Data_Pin, HIGH);          /* Engage pull-up resistor */
    digitalWrite (m_Clock_Pin, HIGH);         /* Send 9th clock for ack) */
    //SHORT_DELAY;
    MEDIUM_DELAY;
    error = digitalRead (m_Data_Pin);         /* Expect pulled down by SHT1x */
    SHORT_DELAY;
    digitalWrite (m_Clock_Pin, LOW);          /* complete the clock pulse */
    return error;
}

/**
 * sReadByte
 *
 *      Routine to read one byte from the SHT1x.  An acknowledge may or
 *      may not be generated, according to the routine's argument.
 *
 * Parameters:
 *      @sendAck        If non-zero, an ACK is sent to the SHT1x if
 *                      the read was successful.
 *      @dataport       data port to access
 *
 * Returns:
 *      The value read from the SHT1x
 */
char Senserion::sReadByte (unsigned char sendAck)
{
    unsigned char ix;                   /* loop index */
    unsigned char val = 0;              /* for building the received data */

    /*
     *  Note to Bill:   we should assure DATA is input by default
     *                  and get rid of these next two lines
     */
    pinMode (m_Data_Pin, INPUT);              /* Set data pin for input mode */
    digitalWrite (m_Data_Pin, HIGH);          /* Engage pull-up resistor */

    for (ix = 0x80; ix; ix >>= 1) {
        digitalWrite (m_Clock_Pin, HIGH);     /* High tells SHT1x we're reading */
        SHORT_DELAY;
        if (digitalRead (m_Data_Pin))
            val |= ix;                  /* If DATA high, set corr. bit */
        digitalWrite (m_Clock_Pin, LOW);      /* Tell SHT1x ready for next bit */
        SHORT_DELAY;
    }
    pinMode (m_Data_Pin, OUTPUT);             /* Change mode to prepare for ack */
    digitalWrite (m_Data_Pin, !sendAck);      /* Set DATA LOW if sendAck requested */
    digitalWrite (m_Clock_Pin, HIGH);         /* Let SHT1x get the data */
    MEDIUM_DELAY;                       /* delay for safety */
    digitalWrite (m_Clock_Pin, LOW);          /* Signal we're done with this */
    SHORT_DELAY;
    pinMode (m_Data_Pin, INPUT);              /* Return Arduino pin to input */
    digitalWrite (m_Data_Pin, HIGH);          /* And engage the pull-up */
    return val;
}

/**
 * sTransmitStart
 *
 *      Routine to generate a "Transmission Start", which looks like:
 *
 *                      _______           _______
 *              DATA:          |_________|
 *                            ____      ____
 *              CLOCK:  _____|    |____|    |____
 *
 * Parameters:
 *      @dataport       data port to access
 *
 * Returns:
 *      No return value.
 */
void Senserion::sTransmitStart ()
{
    pinMode (m_Data_Pin, OUTPUT);             /* Set DATA mode output */
    digitalWrite (m_Data_Pin, HIGH);          /* Start DATA in high state */
    digitalWrite (m_Clock_Pin, LOW);
    SHORT_DELAY;
    digitalWrite (m_Clock_Pin, HIGH);
    SHORT_DELAY;
    digitalWrite (m_Data_Pin, LOW);
    SHORT_DELAY;
    digitalWrite (m_Clock_Pin, LOW);
    MEDIUM_DELAY;
    digitalWrite (m_Clock_Pin, HIGH);
    SHORT_DELAY;
    digitalWrite (m_Data_Pin, HIGH);
    SHORT_DELAY;
    digitalWrite (m_Clock_Pin, LOW);
    SHORT_DELAY;

    pinMode (m_Data_Pin, INPUT);
    digitalWrite (m_Data_Pin, HIGH);
}

/**
 * sConnectionReset
 *
 *      Routine to generate a transmission reset, i.e. reset the SHT1x
 *      to a known state to begin a transmission.  It produces a pulse
 *      train that looks like this:
 *         _____________________________________________________         _____
 *   DATA:                                                      |_______|
 *            _    _    _    _    _    _    _    _    _        ___     ___
 *   SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |___
 *
 * Parameters:
 *      @dataport       data port to access
 *
 * Returns:
 *      No return value.
 */
void Senserion::sConnectionReset ()
{
    unsigned char ix;
    pinMode (m_Data_Pin, OUTPUT);             /* Set Data to output mode */
    digitalWrite (m_Data_Pin, HIGH);          /* Start Data in high state */
    digitalWrite (m_Clock_Pin, LOW);          /* Start Clock in low state */
    /* Now generate 9 clock "pulses" */
    for (ix = 0; ix < 9; ix++) 
	{
        digitalWrite (m_Clock_Pin, HIGH);
		MEDIUM_DELAY;
        digitalWrite (m_Clock_Pin, LOW);
		MEDIUM_DELAY;
    }
    sTransmitStart();                  /* Follow with start pulse */
}

/**
 * sSoftReset
 *
 *      Routine to do a "soft" reset, i.e. send a "Reset" command to the SHT1x
 *
 * Parameters:
 *      @dataport       data port to access
 *
 * Returns:
 *      0 for success, 1 if bad response from SHT1x
 */
char Senserion::sSoftReset()
{
    sConnectionReset();                /* Reset SHT1x communication */
    return sWriteByte (RESET);          /* Send command and return result */
}

/**
 * doCRC
 *
 *      Routine to calculate the CRC while message is sent / received
 *
 * Parameters:
 *      @ch             character to be added to CRC
 *      @crc            crc to which character is to be added
 *
 * Returns:
 *      Target CRC value is updated
 */
#define CRC_POLY        0x31            /* CRC polynomial x**8 + x**5 + x**4 */
void Senserion::doCRC (unsigned char ch, unsigned char *crc)
{
    int ix;
    unsigned char b7;
    
    for (ix = 0; ix < 8; ix++) {
        b7 = ch ^ *crc;
        *crc <<= 1;
        ch <<= 1;
        if (b7 & 0x80)
            *crc ^= CRC_POLY;
    }
    return;
}
        
/**
 * sMeasure
 *
 *      Routine to make a measurement of either temperature or humidity, and
 *      return the result.
 *
 * Parameters:
 *      @pValue         pointer to where value should be stored
 *      @command        command to be sent to the SHT1x
 *      @singleFlag     Flag to show a single byte only should be read
 *      @dataport       data port to access
 *
 * Returns:
 *      Returns the status from the 'read' of the data, and places the value
 *      read into the the locations pointed at by the arguments.  Note that the
 *      SHT1x returns data as (MSB, LSB) so this routine stores the
 *      (short integer) value in reverse sequence.
 */
char Senserion::sMeasure (unsigned char *pValue, unsigned char command, unsigned char singleFlag)
{
    unsigned char error;                /* holds return value from routine */
    unsigned int ix;                    /* used for 'wait for data' loop */
    unsigned char ch, crc, revCRC;
    
    crc = 0;                            /* Initialize CRC to zero */
    sTransmitStart();                  /* Start transmission of command */
    error = sWriteByte (command);       /* Send the requested command */
    /* Note that sWriteByte leaves DATA in input mode */
    doCRC (command, &crc);              /* Include command in CRC */
    if (debug && Verbos) {
        Serial.print("After 'command': CRC is 0x");
        Serial.println(crc, HEX);
    }
    for (ix = 0; ix < 240; ix++){
		delay(1);                       /* This delay is needed for long cables */
        if (!digitalRead (m_Data_Pin))
            break;
    }
    if (digitalRead (m_Data_Pin)) 
         if (Verbos) 
       Serial.println("DATA did not go low after writing command");
    if (!singleFlag) {                  /* If a 2-byte reply */
        ch = sReadByte (ACK);           /* Read MSB of data */
        doCRC (ch, &crc);               /* Include in CRC */
        if (debug && Verbos) {
            Serial.print("After MSB: CRC is 0x");
            Serial.println(crc, HEX);
        }
        *(pValue + 1) = ch;             /* Store MSB byte */
    }
    ch = sReadByte (ACK);               /* Read LSB of data */
    doCRC (ch, &crc);                   /* Include in CRC */
    *pValue = ch;                       /* Store LSB byte */
    if (debug&& (Verbos)) {
        Serial.print("After LSB: CRC is 0x");
        Serial.println(crc, HEX);
    }
    ch = sReadByte (NOACK);             /* Read msg CRC, don't send ACK */
    revCRC = 0;
    for (ix = 0; ix < 8; ix++) {
      if ((0x80 >> ix) & ch)
        revCRC |= (1 << ix);
    }
    if (debug&& Verbos) {
        Serial.print("After Checksum: CRC is 0x");
        Serial.print(crc, HEX);
        Serial.print(", received value was 0x");
        Serial.println(revCRC, HEX);
    }
    if (crc != revCRC) {
		if (Verbos){
			Serial.print("CRC error in reply (command was 0x");
			Serial.print(command, HEX);
			Serial.print("CRC is 0x");
			Serial.print(crc, HEX);
			Serial.print(", received value was 0x");
			Serial.println(revCRC, HEX);
			Serial.println(") - resetting SHT1x connection");
		}
        sConnectionReset();
    }
    return error;
}

/**
 * calcTempHumid
 *
 *      Routine to calculate the "true" temperature and humidity based upon
 *      the "tick" values read from the SHT1x.  The SHT1x is set to operate in
 *      12-bit mode for humidity, and 14-bit mode for temperature.  The
 *      conversion constants are taken from the SHT1x datasheet, assuming a
 *      supply voltage of 5.0V.
 *
 * Parameters:
 *      @pHumidity      pointer to humidity value
 *      @pTemperature   pointer to temperature value
 *
 * Returns:
 *      Input values of temperature and humidity are overwritten with their
 *      calculated "true" values.
 */
void Senserion::calcTempHumid (float *pHumidity, float *pTemperature)
{
  //const float C1=-4.0;              // for 12 Bit    
  //const float C2=+0.0405;           // for 12 Bit    
  //const float C3=-0.0000028;        // for 12 Bit    
  //const float T1=+0.01;             // for 14 Bit @ 5V    
  //const float T2=+0.00008;           // for 14 Bit @ 5V     

	// SHTxx constants 
	//#define C1  -4.0 
	//#define C2  0.0405 
	//#define C3  -0.0000028 
	//
	//#define D1  -40.0 
	//#define D2  0.04 
	//
	//#define T1  0.01 
	//#define T2  0.00008 

    /* Constants for conversion of reading to relative humidity */
#define         C1      -4.0  //V3
#define         C2      +0.0405//V3
#define         C3      -0.0000028//V3

//#define         C1      -2.0468
//#define         C2      +0.0367
//#define         C3      -0.0000015955
    /* Constants for temperature-compensated relative humidity */
#define         T1      +0.01
#define         T2      +0.00008
    /* Constants for conversion of temperature reading to Centigrade */
#define         D1      -40.20	//5.0V operation
#define         D2      +0.01

    float rh = *pHumidity;      /* relative humidity (input value) */
    float rhLin;                /* Linear value of humidity */
    float rhTrue;               /* Temperature-compensated humidity value */
    float t = *pTemperature;    /* input value for temperature */
    float tC;                   /* Temperature converted to Celsius */

    tC = D1 + (t * D2);         /* Linear conversion of temperature */
    rhLin = (C3 * rh * rh) + (C2 * rh) + C1;    /* "ticks" to relative H */
    rhTrue = (tC - 25) * (T1 + (T2 * rh)) + rhLin;
    /* Assure our relative humidity isn't out of range (> 100% or < 0.1%) */
    if (rhTrue > 100.0)
        rhTrue = 100.0;
    else if (rhTrue < 0.1)
        rhTrue = 0.1;
    /* Finally, return the calculated values */
    *pTemperature = tC;
    *pHumidity = rhTrue;
}

/**
 * calcDewPoint
 *
 *      Routine to calculate the dew point based upon relative humidity
 *      and temperature.  I have no idea what it's doing, but since it
 *	comes from the Sensirion literature, it's probably correct :-).
 *
 * Parameters:
 *      @humidity       value of relative humidity
 *      @temperature    value of temperature
 *
 * Returns:
 *      Calculated dew point
 */
float Senserion::calcDewPoint (float humidity, float temperature)
{
    float logEx;
    logEx = 0.66077 + (7.5 * temperature) / (237.3 + temperature)
            + (log10(humidity) - 2);
    return (logEx - 0.66077) * 237.3 / (0.66077 + 7.5 - logEx);
}

bool Senserion::Measure(float *humidity, float *temperature, float *DewPoint)
{
	float fHumidity;            /* working value for humidity calculation */
    float fTemperature;         /* working value for temperature calculation */
    float dewPoint;             /* calculated Dew Point value */

	int humidVal;               /* humidity value read from SHT1x */
    int tempVal;                /* temperature value from SHT1x */

	int error = sMeasure ((unsigned char *)&humidVal, MEASURE_HUMI, 0);
	if (debug && Verbos) {
		Serial.print("In main loop: humidVal is ");
		Serial.print(humidVal, HEX);
		Serial.print(" and return value is ");
		Serial.println(error, DEC);
	}
	error += sMeasure ((unsigned char *)&tempVal, MEASURE_TEMP, 0);
	if (debug && Verbos) {
		Serial.print("In main loop: tempVal is ");
		Serial.print(tempVal, HEX);
		Serial.print(" and return value is ");
		Serial.println(error, DEC);
	}
	if (error)
	{
		sConnectionReset();
	}
	else 
	{
		fHumidity = float(humidVal);
		fTemperature = float(tempVal);
		calcTempHumid (&fHumidity, &fTemperature);
		dewPoint = calcDewPoint (fHumidity, fTemperature);
                if (Verbos) {
         		printReading ("Temperature is ", &fTemperature, " degrees Celsius");
        		printReading ("Humidity is ", &fHumidity, "%");
        		printReading ("Dew point is ", &dewPoint, " degrees Celsius");
                }
	}
	*humidity = fHumidity;
	*temperature = fTemperature;
	*DewPoint = dewPoint;
	return (error==0);
}

bool Senserion::Measure(char *humidity, char *temperature, char *DewPoint)
{
  float temp;
  float hum;
  float dew;
  if (!Measure(&temp, &hum, &dew)) return false;
  
  int num;
  char str[10];
    
  splitFloat (&temp, &num, str, 2);
  itoa(num,temperature, 10); 
  strcat(temperature, ".");
  strcat(temperature, str);
  
  splitFloat (&hum, &num, str, 2);
  itoa(num,humidity, 10); 
  strcat(humidity, ".");
  strcat(humidity, str);

  splitFloat (&dew, &num, str, 2);
  itoa(num,DewPoint, 10); 
  strcat(DewPoint, ".");
  strcat(DewPoint, str);
  return true;
}

/**
 * splitFloat
 *
 *      This routine takes a float as input and returns the integer part and
 *	the fractional part, to the number of decimal places specified.  The
 *	only reason I wrote it is because I couldn't find any existing routine
 *	to print out a float in a reasonable format (with decimal places)
 *
 * Parameters:
 *      @fNum        The floating point number to be dissected
 *      @pInt        Pointer to an integer to contain the integer part
 *      @pFrac       Pointer to a string to contain the fraction
 *                   Note: the caller must assure the string is large enough
 *      @decPlaces   Number of decimal places for the operation
 *
 * Returns:
 *      The values calculated are placed in the locations specified.
 */
void Senserion::splitFloat (float *fNum, int *pInt, char *pFrac, int decPlaces) {

     int ix;
     int frac;
     float fVal;

     /* Round the input according to precision, plus fudge for noise */
     fVal = *fNum + (0.5 * pow((float)10.0, (float)(-decPlaces))) + 0.00001;
     *pInt = fVal;          /* Return truncated integer value */     
     /*
      * Now isolate just the fractional part of the original number
      */
     fVal = fVal - (float)(*pInt);  /* Remove the integral part */
     /* Convert the fraction into a simple integer */
     frac = fVal * pow ((float)10.0, (float)decPlaces);
     /* Now format it as a leading-zero string of digits */
     pFrac += decPlaces;    /* point to string terminator position */
     *pFrac-- = 0;          /* put in terminator */
     for (ix = 0; ix < decPlaces; ix++) {
         *pFrac-- = (frac % 10) | 0x30;  /* put in digits in reverse order */
         frac /= 10;
     }
}

/**
 * printReading
 *
 *      Routine to print out the value of caculated data, using a common format
 *      of {label} {int value}.{single digit fraction}{suffix}
 *
 * Parameters:
 *      @label          string for starting label
 *      @pVal           pointer to float value to display
 *      @suffix         string to append to value
 *
 * Returns:
 *      nothing
 */
void Senserion::printReading (char *label, float *pVal, char *suffix) {
    int num;
    char str[10];
    
    splitFloat (pVal, &num, str, 2);
    Serial.print(label);
    Serial.print(num, DEC);
    Serial.print(".");
    Serial.print(str);
    Serial.println(suffix);
}

unsigned char Senserion::GetStatusRegister()
{
	unsigned char error;        /* return value for routine calls */
	unsigned char statusVal;    /* contents of status register */
	error = sMeasure ((unsigned char *)&statusVal, STATUS_REG_R, 1);
	return statusVal;
}



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

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

