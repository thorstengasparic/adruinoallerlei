/*
 * This program is an adaptation of the 8051 Sample Program provided
 * by Sensirion.  A CRC check, using program calculation, is added,
 * again based upon code suggested by Sensirion.
 *
 * There are several points at which a short delay is required.  Although
 * only a few microseconds should be sufficient, in order to assure that
 * we can extend the connection to the SHT1x away from the Arduino, I have
 * defined three constants - SHORT_DELAY, MEDIUM_DELAY and LONG_DELAY - so that
 * one can easily experiment with them to determine reasonable values.
 */

#define DATA    10              /* Arduino pin for data read/write */
#define CLOCK   11              /* Arduino pin for toggling the clock */

#define NOACK   0               /* Flags to tell read_byte routine whether */
#define ACK     1                /* or not to send an ACK after the read   */ 

/* Define the SHT1x commands to be their command codes */
#define         MEASURE_TEMP    0x03
#define         MEASURE_HUMI    0x05
#define         STATUS_REG_W    0x06
#define         STATUS_REG_R    0x07
#define         RESET           0x1e

/* Following constants are in microseconds */
#define         LONG_DELAY      delayMicroseconds(50)
#define         MEDIUM_DELAY    delayMicroseconds(10)
#define         SHORT_DELAY     delayMicroseconds(5)

unsigned char debug;          /* When set, intermediate data is printed */

/**
 * sWriteByte
 *
 *      Routine to write a byte to the SHT1x and check for the acknowledge
 *
 * Parameters:
 *      @value          byte value to be written
 *
 * Returns:
 *      0 for success, 1 if no Acknowledge received from SHT1x
 */
char sWriteByte(unsigned char value)
{
    unsigned char ix;                   /* loop index */
    unsigned char error;                /* result of the write */

    pinMode (DATA, OUTPUT);
    for (ix = 0x80; ix; ix >>= 1) {
        digitalWrite (DATA, ix & value);/* Next bit to I/O port */
        SHORT_DELAY;			/* Shouldn't be needed */
        digitalWrite (CLOCK, HIGH);	/* Set clock signal high */
        MEDIUM_DELAY;			/* some delay needed */
        digitalWrite (CLOCK, LOW);	/* Set clock back to low */
    }
    pinMode (DATA, INPUT);              /* Prepare to read the ACK bit */
    digitalWrite (DATA, HIGH);          /* Engage pull-up resistor */
    digitalWrite (CLOCK, HIGH);         /* Send 9th clock for ack) */
    SHORT_DELAY;
    error = digitalRead (DATA);         /* Expect pulled down by SHT1x */
    digitalWrite (CLOCK, LOW);          /* complete the clock pulse */
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
 *
 * Returns:
 *      The value read from the SHT1x
 */
char sReadByte (unsigned char sendAck)
{
    unsigned char ix;                   /* loop index */
    unsigned char val = 0;              /* for building the received data */

    /*
     *  Note to Bill:   we should assure DATA is input by default
     *                  and get rid of these next two lines
     */
    pinMode (DATA, INPUT);              /* Set data pin for input mode */
    digitalWrite (DATA, HIGH);          /* Engage pull-up resistor */

    for (ix = 0x80; ix; ix >>= 1) {
        digitalWrite (CLOCK, HIGH);     /* High tells SHT1x we're reading */
        SHORT_DELAY;
        if (digitalRead (DATA))
            val |= ix;                  /* If DATA high, set corr. bit */
        digitalWrite (CLOCK, LOW);      /* Tell SHT1x ready for next bit */
        SHORT_DELAY;
    }
    pinMode (DATA, OUTPUT);             /* Change mode to prepare for ack */
    digitalWrite (DATA, !sendAck);      /* Set DATA LOW if sendAck requested */
    SHORT_DELAY;
    digitalWrite (CLOCK, HIGH);         /* Let SHT1x get the data */
    MEDIUM_DELAY;                       /* delay for safety */
    digitalWrite (CLOCK, LOW);          /* Signal we're done with this */
    pinMode (DATA, INPUT);              /* Return Arduino pin to input */
    digitalWrite (DATA, HIGH);          /* And engage the pull-up */
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
 *      None
 *
 * Returns:
 *      No return value.
 */
void sTransmitStart (void)
{
    pinMode (DATA, OUTPUT);             /* Set DATA mode output */
    digitalWrite (DATA, HIGH);          /* Start DATA in high state */
    digitalWrite (CLOCK, LOW);
    MEDIUM_DELAY;
    digitalWrite (CLOCK, HIGH);
    MEDIUM_DELAY;
    digitalWrite (DATA, LOW);
    MEDIUM_DELAY;
    digitalWrite (CLOCK, LOW);
    LONG_DELAY;
    digitalWrite (CLOCK, HIGH);
    MEDIUM_DELAY;
    digitalWrite (DATA, HIGH);
    MEDIUM_DELAY;
    digitalWrite (CLOCK, LOW);
    /* This routine will normally be followed by a write, so leave pinMode */
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
 *      None
 *
 * Returns:
 *      No return value.
 */
void sConnectionReset (void)
{
    unsigned char ix;
    pinMode (DATA, OUTPUT);             /* Set Data to output mode */
    digitalWrite (DATA, HIGH);          /* Start Data in high state */
    digitalWrite (CLOCK, LOW);          /* Start Clock in low state */
    /* Now generate 9 clock "pulses" */
    for (ix = 0; ix < 9; ix++) {
        SHORT_DELAY;
        digitalWrite (CLOCK, HIGH);
        SHORT_DELAY;
        digitalWrite (CLOCK, LOW);
    }
    sTransmitStart ();                  /* Follow with start pulse */
}

/**
 * sSoftReset
 *
 *      Routine to do a "soft" reset, i.e. send a "Reset" command to the SHT1x
 *
 * Parameters:
 *      None
 *
 * Returns:
 *      0 for success, 1 if bad response from SHT1x
 */
char sSoftReset (void)
{
    sConnectionReset ();                /* Reset SHT1x communication */
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
void doCRC (unsigned char ch, unsigned char *crc)
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
 *
 * Returns:
 *      Returns the status from the 'read' of the data, and places the value
 *      read into the the locations pointed at by the arguments.  Note that the
 *      SHT1x returns data as (MSB, LSB) so this routine stores the
 *      (short integer) value in reverse sequence.
 */
char sMeasure (unsigned char *pValue, unsigned char command,
               unsigned char singleFlag)
{
    unsigned char error;                /* holds return value from routine */
    unsigned int ix;                    /* used for 'wait for data' loop */
    unsigned char ch, crc, revCRC;
    
    crc = 0;                            /* Initialize CRC to zero */
    sTransmitStart ();                  /* Start transmission of command */
    error = sWriteByte (command);       /* Send the requested command */
    /* Note that sWriteByte leaves DATA in input mode */
    doCRC (command, &crc);              /* Include command in CRC */
    if (debug) {
        Serial.print("After 'command': CRC is 0x");
        Serial.println(crc, HEX);
    }
    for (ix = 0; ix < 65535; ix++)
        if (!digitalRead (DATA))
            break;
    if (digitalRead (DATA)) 
         Serial.println("DATA did not go low after writing command");
    if (!singleFlag) {                  /* If a 2-byte reply */
        ch = sReadByte (ACK);           /* Read MSB of data */
        doCRC (ch, &crc);               /* Include in CRC */
        if (debug) {
            Serial.print("After MSB: CRC is 0x");
            Serial.println(crc, HEX);
        }
        *(pValue + 1) = ch;             /* Store MSB byte */
    }
    ch = sReadByte (ACK);               /* Read LSB of data */
    doCRC (ch, &crc);                   /* Include in CRC */
    *pValue = ch;                       /* Store LSB byte */
    if (debug) {
        Serial.print("After LSB: CRC is 0x");
        Serial.println(crc, HEX);
    }
    ch = sReadByte (NOACK);             /* Read msg CRC, don't send ACK */
    revCRC = 0;
    for (ix = 0; ix < 8; ix++) {
      if ((0x80 >> ix) & ch)
        revCRC |= (1 << ix);
    }
    if (debug) {
        Serial.print("After Checksum: CRC is 0x");
        Serial.print(crc, HEX);
        Serial.print(", received value was 0x");
        Serial.println(revCRC, HEX);
    }
    if (crc != revCRC) {
        Serial.print("CRC error in reply (command was 0x");
        Serial.print(command, HEX);
        Serial.print("CRC is 0x");
        Serial.print(crc, HEX);
        Serial.print(", received value was 0x");
        Serial.println(revCRC, HEX);
        Serial.println(") - resetting SHT1x connection");
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
void calcTempHumid (float *pHumidity, float *pTemperature)
{
    /* Constants for conversion of reading to relative humidity */
#define         C1      -4.0
#define         C2      +0.0405
#define         C3      -0.0000028
    /* Constants for temperature-compensated relative humidity */
#define         T1      +0.01
#define         T2      +0.00008
    /* Constants for conversion of temperature reading to Centigrade */
#define         D1      -40.00
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
float calcDewPoint (float humidity, float temperature)
{
    float logEx;
    logEx = 0.66077 + (7.5 * temperature) / (237.3 + temperature)
            + (log10(humidity) - 2);
    return (logEx - 0.66077) * 237.3 / (0.66077 + 7.5 - logEx);
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
void splitFloat (float *fNum, int *pInt, char *pFrac, int decPlaces) {

     int ix;
     int frac;
     float fVal;

     /* Round the input according to precision, plus fudge for noise */
     fVal = *fNum + (0.5 * pow(10.0, (float)(-decPlaces))) + 0.00001;
     *pInt = fVal;          /* Return truncated integer value */     
     /*
      * Now isolate just the fractional part of the original number
      */
     fVal = fVal - (float)(*pInt);  /* Remove the integral part */
     /* Convert the fraction into a simple integer */
     frac = fVal * pow (10.0, (float)decPlaces);
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
void printReading (char *label, float *pVal, char *suffix) {
    int num;
    char str[10];
    
    splitFloat (pVal, &num, str, 1);
    Serial.print(label);
    Serial.print(num, DEC);
    Serial.print(".");
    Serial.print(str);
    Serial.println(suffix);
}

/**
 * setup
 *
 *      This is the routine required by the Arduino software to initialize
 *      anything needed by the main loop.  We set up the DATA and CLOCK ports
 *      to a beginning state.
 */
void setup()
{
    Serial.begin(9600);         /* Open Arduino serial communications */
    pinMode (CLOCK, OUTPUT);
    pinMode (DATA, OUTPUT);
    sConnectionReset ();        /* Reset the device */
}

void loop()
{
    char cmd;                   /* command input by user */
    int humidVal;               /* humidity value read from SHT1x */
    int tempVal;                /* temperature value from SHT1x */
    unsigned char statusVal;    /* contents of status register */
    float fHumidity;            /* working value for humidity calculation */
    float fTemperature;         /* working value for temperature calculation */
    float dewPoint;             /* calculated Dew Point value */
    unsigned char error;        /* return value for routine calls */

    while (Serial.available() > 0) {  /* when a serial connection exists */
        cmd = Serial.read();    /* Read user comand */
        error = 0;
        switch (cmd) {
            case 'r':
            case 'R':
                /* Read request - read in temperature and humidity */
                error += sMeasure ((unsigned char *)&humidVal, MEASURE_HUMI, 0);
                if (debug) {
                    Serial.print("In main loop: humidVal is ");
                    Serial.print(humidVal, HEX);
                    Serial.print(" and return value is ");
                    Serial.println(error, DEC);
                }
                error += sMeasure ((unsigned char *)&tempVal, MEASURE_TEMP, 0);
                if (debug) {
                    Serial.print("In main loop: tempVal is ");
                    Serial.print(tempVal, HEX);
                    Serial.print(" and return value is ");
                    Serial.println(error, DEC);
                }
                if (error)
                    sConnectionReset();
                else {
                    fHumidity = float(humidVal);
                    fTemperature = float(tempVal);
                    calcTempHumid (&fHumidity, &fTemperature);
                    dewPoint = calcDewPoint (fHumidity, fTemperature);
                    printReading ("Temperature is ", &fTemperature,
				  "\xb0 Celsius");
                    printReading ("Humidity is ", &fHumidity, "%");
                    printReading ("Dew point is ", &dewPoint, "\xb0 Celsius");
                }
                break;
            case 'd':            /* "Toggle" debug flag for printing */
            case 'D':            /* intermediate data */
                debug ^= 1;
                if (debug)
                    Serial.println("**** Debugging enabled ****");
                else
                    Serial.println("**** Debugging disabled ****");
                break;
            case 's':            /* Read status register */
            case 'S':
                /* Read request - read in temperature and humidity */
                error += sMeasure ((unsigned char *)&statusVal, STATUS_REG_R, 1);
                Serial.print("Status register contains 0x");
                Serial.println(statusVal, HEX);
                break;
            default:
                Serial.println("Unrecognized command.");
        }
    }
}


