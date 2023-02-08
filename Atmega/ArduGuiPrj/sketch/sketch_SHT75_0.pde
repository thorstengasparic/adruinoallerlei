//==========================================================================//
//                                                                          //
//   SHT-11 Humidity & Temperature      Version 1.00     December 2008      // 
//                                                                          //
//                                                                          //
//   Written for the Arduino ATmega168 Diecimila and installed & tested     //
//   on December 12,2008                                                    //
//                                                                          //
//   Multiple Internet references were used, combined and modified          //  
//   for this example, such as Arduino forums and nuelectronics.com         //
//                                                                          //
//==========================================================================//
// Devices Used:                                                            //
// Boarduino:  USB Powered - Diecimila                                      // 
// http://www.ladyada.net/make/boarduino/index.html                         //
// The Boarduino is a Solderless Breadboard compatible Arduino              //
//                                                                          //
// Parallax Sensirion SHT-11 module                                         //
// http://www.parallax.com   (Look for -> "SensirionDocs.pdf" )             //
//                                                                          //
//                  The parallax module is a breadboard compatible carrier  //
//                  with the SMD sensor installed by parallax               //
//                  NOTE: Different Pinout than SMD sensor from Sensirion   //
//==========================================================================//
// Notes:                                                                   //
//                                                                          //
// The Parallax module contains built-in Pullup & Data Pin resistors        //
// Sensor Carrier     Boarduino                                             //
// Data Pin 1   -->   Arduino pin 10                                        //
// Clock Pin 3  -->   Arduino pin 11                                        //
// Vss Pin 4    -->   Arduino GND                                           //
// Vdd Pin 8    -->   Arduino 5V                                            //
//==========================================================================//

//==========================================================================//
//                            Preamble                                      //
//==========================================================================//
#define  LED 13

#define  T_CMD  0x03                // See Sensirion Data sheet
#define  H_CMD  0x05
#define  R_STAT 0x07
#define  W_STAT 0x06
#define  RST_CMD 0x1E

//==========================================================================//
// SHT11 Sensor Coefficients from Sesirion Data Sheet
const float C1=-4.0;               // for 12 Bit
const float C2= 0.0405;            // for 12 Bit
const float C3=-0.0000028;         // for 12 Bit
//const float D1=-40.0;              // for 14 Bit @ 5V
//const float D2=0.01;               // for 14 Bit DEGC
const float T1=0.01;               // for 14 Bit @ 5V
const float T2=0.00008;            // for 14 Bit @ 5V
//==========================================================================//
// Sensor Variables
int shtClk   =  11;                // Clock Pin                        
int shtData  =  10;                // Data Pin
int ioByte;                        // data transfer global -  DATA
int ackBit;                        // data transfer glocal  - ACKNOWLEDGE
float retVal;                      // Raw return value from SHT-11 
float temp_degC;                   // working temperature
float temp_degF;                   // working tempeature
float r_temp;                      // raw working temp
float r_humid;                     // Raw working humidity
float dew_point;
float dew_pointF;
//==========================================================================//
// coding variables
int dly;
int timewait;
byte bitmask;

//==========================================================================//
//                                                                          //
//                            Code Body                                     //
//                                                                          //
//==========================================================================//

void setup()
{
 
  pinMode(shtClk, OUTPUT);
  digitalWrite(shtClk, HIGH);     // Clock
  
  pinMode(shtData, OUTPUT);        // Data
  pinMode(LED, OUTPUT);        // LED
  Serial.begin(9600);         // open serial Port for 9600 Baud
  
  Serial.println("Resetting Sensor..");
  SHT_Connection_Reset();
  
  // Fast Flash LED to say we are ready
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  //-----------------------------
  
  Serial.println("Starting Temperature & Humidity reading every 5 seconds.");
}


//==========================================================================//
void loop()
//==========================================================================//
{

 Serial.println("------------------------------------------------------------------------------");
// SHT-11 Get Temperature
       SHT_Measure(T_CMD);                    // retVal = Temperature reading
       r_temp = retVal;
       
        temp_degC = SHT_calc_tempC( retVal);  // Convert to Celcius
          Serial.print("Temperature: ");
          serialPrintFloat(temp_degC);
          Serial.print("C");
          Serial.print('\t');
      
        temp_degF = SHT_calc_tempF( retVal);  // Convert to Fahrenheit
          Serial.print("| Temperature: ");;
          serialPrintFloat(temp_degF);
          Serial.print("F");
          Serial.print('\t');
          Serial.println();
// SHT-11 Get Humidity
      SHT_Measure(H_CMD);                     // retVal = humidity reading
      r_humid = retVal;                         // Store raw humidity value
         Serial.print("Humidity: ");
         // Linear conversion
         float rh_lin = C3 * retVal * retVal + C2 * retVal + C1; 
         // Temperature compensated RH
         float rh_true = (temp_degC * (T1 + T2 * retVal) + rh_lin); 
           if(rh_true>100)rh_true=100;       // deal with rh being outside
           if(rh_true<0.1)rh_true=0.1;       // a physical possible range
         serialPrintFloat(rh_true);
         Serial.print("%");
         Serial.print('\t');
// calculate Dew Point
     dew_point=calc_dewpoint(rh_true,temp_degC); //calculate dew point
     dew_pointF = 9 * dew_point/5 + 32;


        Serial.print("| Dew point:   ");
        serialPrintFloat(dew_point);
        Serial.print("C");
        Serial.print("   ");
        serialPrintFloat(dew_pointF);
        Serial.print("F");

         Serial.println();

// Slow Flash activity LED and create pause between scans
//  ...in this case, 5 secs)      
  timewait = 0;
  while (timewait < 5) {
   digitalWrite(LED, HIGH);
    delay(500);
   digitalWrite(LED, LOW); 
    delay(500);
   timewait++;
  }
      
}


//--[ Subroutines ]---------------------------------------------------
void SHT_Write_Byte(void) {
//--------------------------------------------------------------------
  pinMode(shtData, OUTPUT);
  shiftOut(shtData, shtClk, MSBFIRST, ioByte);
  pinMode(shtData, INPUT);
  digitalWrite(shtData, LOW);
  digitalWrite(shtClk, LOW);
  digitalWrite(shtClk, HIGH);
  ackBit = digitalRead(shtData);
  digitalWrite(shtClk, LOW);
}

int shiftIn() {
  int cwt;
  cwt=0;
  bitmask=128;
  while (bitmask >= 1) {
    digitalWrite(shtClk, HIGH);
    cwt = cwt + bitmask * digitalRead(shtData);
    digitalWrite(shtClk, LOW);
    bitmask=bitmask/2;
  }
  return(cwt);
}

//--------------------------------------------------------------------
void SHT_Read_Byte(void) {
//--------------------------------------------------------------------  
  ioByte = shiftIn();
  digitalWrite(shtData, ackBit);
  pinMode(shtData, OUTPUT);
  digitalWrite(shtClk, HIGH);
  digitalWrite(shtClk, LOW);
  pinMode(shtData, INPUT);
  digitalWrite(shtData, LOW);
}
//--------------------------------------------------------------------
void SHT_Start(void) {
//--------------------------------------------------------------------
// generates a sensirion specific transmission start
// This where Sensirion is not following the I2C standard
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______

  digitalWrite(shtData, HIGH);     // Data pin high
  pinMode(shtData, OUTPUT);
  digitalWrite(shtClk,  HIGH);     // clock high
  digitalWrite(shtData,  LOW);     // data low
  digitalWrite(shtClk,   LOW);     // clock low
  digitalWrite(shtClk,  HIGH);     // clock high
  digitalWrite(shtData, HIGH);     // data high
  digitalWrite(shtClk,  LOW);      // clock low
}


//--------------------------------------------------------------------
void SHT_Connection_Reset(void) {
//--------------------------------------------------------------------  
// connection reset: DATA-line=1 and at least 9 SCK cycles followed by start
// 16 is greater than 9 so do it twice
//      _____________________________________________________         ________
// DATA:                                                     |_______|
//          _    _    _    _    _    _    _    _    _        ___    ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |__|   |______

  shiftOut(shtData, shtClk, LSBFIRST, 0xff);
  shiftOut(shtData, shtClk, LSBFIRST, 0xff);
  SHT_Start();
  
}

//--------------------------------------------------------------------
void SHT_Soft_Reset(void) {
//--------------------------------------------------------------------
  SHT_Connection_Reset();
  
  ioByte = RST_CMD;
  ackBit = 1;
  SHT_Write_Byte();
  delay(15);
}

//--------------------------------------------------------------------
void SHT_Wait(void) {
//--------------------------------------------------------------------
// Waits for SHT to complete conversion
  delay(5);
  dly = 0;
  while (dly < 600) {
    if (digitalRead(shtData) == 0) dly=2600;
    delay(1);
    dly=dly+1;
  }
}



//--------------------------------------------------------------------
void SHT_Measure(int SHT_CMD) {
//--------------------------------------------------------------------
  SHT_Soft_Reset();
  SHT_Start();
   ioByte = SHT_CMD;
  
  SHT_Write_Byte();          // Issue Command
  SHT_Wait();                // wait for data ready
   ackBit = 0;               // read first byte
  
  SHT_Read_Byte();
  int msby;                  // process it as Most Significant Byte (MSB)
   msby = ioByte;
   ackBit = 1;

  SHT_Read_Byte();          // read second byte
   retVal = msby;           // process result to combine MSB with LSB
   retVal = retVal * 0x100;
   retVal = retVal + ioByte;
   if (retVal <= 0) retVal = 1;
}

//--------------------------------------------------------------------
int SHT_Get_Status(void) {
//--------------------------------------------------------------------
  SHT_Soft_Reset();
  SHT_Start();
   ioByte = R_STAT;
  
  SHT_Write_Byte();
  SHT_Wait();
   ackBit = 1;
 
  SHT_Read_Byte();
  return(ioByte);
}



//--------------------------------------------------------------------
int SHT_calc_tempC( float w_temperature)
//--------------------------------------------------------------------
{
// calculate temp with float

float temp1;

// Per the data sheet, these are adjustments to results
temp1 = w_temperature * 0.01;  // divide by 100
temp1 = temp1 - (int)40;       // Subtract 40
return (temp1);
} 

//--------------------------------------------------------------------
int SHT_calc_tempF( int w_temperature) {
//--------------------------------------------------------------------
// calculate temp with float
int temp1;
  temp1 = w_temperature * 0.018;
  temp1 = temp1 - (int)40;
 return (temp1);
} 

//--------------------------------------------------------------------
float calc_dewpoint(float h,float t)
//--------------------------------------------------------------------
// calculates dew point
// input:   humidity [%RH], temperature [°C]
// output:  dew point [°C]
{ float logEx,dew_point;
  logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
  dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
  return dew_point;
}


//--------------------------------------------------------------------
void serialPrintFloat( float f){
//--------------------------------------------------------------------  
// print results properly with float decimal value
 int i;
   Serial.print((int)f);
   Serial.print(".");
    i = (f - (int)f) * 100;
   Serial.print( abs(i) ); 
} 
