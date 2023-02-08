#include <inttypes.h>

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
