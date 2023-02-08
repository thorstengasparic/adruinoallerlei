#include <IOM128V.H> //Microcontroller specific library, e.g. port definitions    
   
#include <MATH.H>    //Keil library      
#include <STDIO.H>   //Keil library    
#include <MACROS.H>    
  const float C1=-4.0;              // for 12 Bit    
  const float C2=+0.0405;           // for 12 Bit    
  const float C3=-0.0000028;        // for 12 Bit    
  const float T1=+0.01;             // for 14 Bit @ 5V    
  const float T2=+0.00008;           // for 14 Bit @ 5V     
   
unsigned char cwendu1,cwendu2;   
unsigned int uwendu;   
float fwendu;   
   
   
enum {TEMP,HUMI};   
   
   
   
#define noACK 0    
#define ACK   1    
                            //adr  command  r/w    
#define STATUS_REG_W 0x06   //000   0011    0    
#define STATUS_REG_R 0x07   //000   0011    1    
#define MEASURE_TEMP 0x03   //000   0001    1    
#define MEASURE_HUMI 0x05   //000   0010    1    
#define RESET        0x1e   //000   1111    0    
   
   
#define  DATA_SHTxx       (1<<1)                // PF0    
#define  DATA_TO_1()      (PORTF |= DATA_SHTxx)   // PF0='0'        //置0    
#define  DATA_TO_0()      (PORTF &= ~DATA_SHTxx)   // PF0='float'   //置1    
#define  DATA_status()    (PINF & DATA_SHTxx)     // read PF0 pin     
   
#define  SCK_SHTxx       (1<<2)                // PF0    
#define  SCK_TO_0()      (PORTF &= ~SCK_SHTxx)   // PF0='0'    
#define  SCK_TO_1()      (PORTF |= SCK_SHTxx)     // PF0='float'   //置0    
#define  SCK_status()    (PINF & SCK_SHTxx)     // read PF0 pin  //置1    
//----------------------------------------------------------------------------------    
   
void shxx_config()   
{    
   //DDRF  &= ~DATA_SHTxx ;   // 输入模式(上电时为高电平)    
  DDRF |= 0x02;//(1<<1)//DATA_SHTxx;       //配置为输出    
  PORTF |= 0x02;//(1<<1)//DATA_SHTxx ;   // 输出锁存器写0    
     
      
 // DDRF  &= ~SCK_SHTxx;   // 输入模式(上电时为高电平)      
  DDRF |=0x04;//(1<<2);// SCK_SHTxx;        //配置为输出    
  PORTF &= 0xfb;//~SCK_SHTxx;   // 输出锁存器写0    
     
}   
char s_write_byte(unsigned char value)   
//----------------------------------------------------------------------------------    
// writes a byte on the Sensibus and checks the acknowledge     
{    
  unsigned char i,error=0,merror=0;   
  DDRF |=0x06;     
 // for (i=0x80;i>0;i/=2)    
/*// while(i>0)             //shift bit for masking  
  { if (i & value) PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS  
    else PORTF &=0xfd;//DATA=0;                          
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS  
    //_NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;  
    //i=i/2;  
  }  
  */   
  PORTF |=0x02;   
  PORTF &=0xfb;   
  _NOP();_NOP();_NOP();   
  i=0x80;             //shift bit for masking    
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                           
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x40;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;     
    _NOP();_NOP();_NOP();                          
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x20;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                          
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
      
  }   
  i=0x10;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                           
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x08;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                           
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x04;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                           
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x02;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;    
    _NOP();_NOP();_NOP();                           
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();        //pulswith approx. 5 us        
    PORTF &=0xfb;//SCK=0;    
       
  }   
  i=0x01;   
  { if (i & value)    
    PORTF |=0x02;//DATA=1;          //masking value with i , write to SENSI-BUS    
    else PORTF &=0xfd;//DATA=0;                            
    PORTF |=0x04;//SCK=1;                          //clk for SENSI-BUS    
    _NOP();_NOP();_NOP();    
       //pulswith approx. 5 us          
       
       
  }   
     
  PORTF |=0x02;//DATA=1;    
  DDRF &=0xfd;   
  _NOP();_NOP();_NOP();   
  PORTF &=0xfb;//SCK=0;                           //release DATA-line    
      
  _NOP();_NOP();_NOP();                           //clk #9 for ack     
  merror=PINF&0x02;//error=DATA;    
  error=merror;   
  PORTF |=0x04;//SCK=1;      
  _NOP();_NOP();_NOP();                     //check ack (DATA will be pulled down by SHT11)    
  PORTF &=0xfb;//SCK=0;     
  DATA_TO_1();    
  if(error >0)   
  PORTA |=0x04;        
  return error;                   //error=1 in case of no acknowledge    
}   
char s_read_byte(unsigned char ack)   
//----------------------------------------------------------------------------------    
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1"     
{    
  unsigned char i,val=0;   
  //DDRF |=0x04;    
  //DDRF &=0xfd;    
  PORTF |=0x02;//DATA=1;    
  _NOP();_NOP();_NOP();   
                               //release DATA-line    
  //for (i=0x80;i>0;i/=2)     
   i=0x80;            //shift bit for masking    
  { PORTF |=0x04;//SCK=1;    
    _NOP();                          //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;    
        _NOP();             
  }   
  i=0x40;   
  { PORTF |=0x04;//SCK=1;     
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;      
    _NOP();             
  }   
  i=0x20;   
  { PORTF |=0x04;//SCK=1;     
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;     
    _NOP();                         
  }   
  i=0x10;   
  { PORTF |=0x04;//SCK=1;    
    _NOP();                          //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;    
    _NOP();                     
  }   
  i=0x08;   
  { PORTF |=0x04;//SCK=1;     
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;    
    _NOP();                         
  }   
  i=0x04;   
  { PORTF |=0x04;//SCK=1;     
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;     
    _NOP();                     
  }   
  i=0x02;   
  { PORTF |=0x04;//SCK=1;     
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;    
    _NOP();                         
  }   
  i=0x01;   
  { PORTF |=0x04;//SCK=1;    
    _NOP();                         //clk for SENSI-BUS    
    if (PINF&0x02) val=(val | i);        //read bit      
    PORTF &=0xfb;//SCK=0;    
    _NOP();                     
  }   
  DDRF |=0x02;   
  if(ack==0)   
  {PORTF |=0x02;   
  _NOP();   
}   
  else   
  {PORTF &=0xfd;   
  _NOP();   
}   
  //DATA=!ack;                        //in case of "ack==1" pull down DATA-Line    
  PORTF |=0x04;//SCK=1;                            //clk #9 for ack    
   _NOP();_NOP();_NOP();   
            //pulswith approx. 5 us     
  PORTF &=0xfb;//SCK=0;     
  _NOP();_NOP();_NOP();   
                           
  PORTF |=0x02;//DATA=1;     
  DDRF &=0xfd;    
  _NOP();                      //release DATA-line    
  return val;   
}   
   
void s_transstart(void)   
//----------------------------------------------------------------------------------    
// generates a transmission start     
//       _____         ________    
// DATA:      |_______|    
//           ___     ___    
// SCK : ___|   |___|   |______    
{     
   DATA_TO_1();    
   _NOP();   
   SCK_TO_0();                   //Initial state    
   _NOP();   
   SCK_TO_1();   
   _NOP();    
   DATA_TO_0();   
   _NOP();    
   SCK_TO_0();     
   //delay_us(5);                 //pulswith approx. 5 us      
   _NOP();   
   _NOP();   
   _NOP();   
   _NOP();   
   _NOP();   
   SCK_TO_1();   
   _NOP();    
   DATA_TO_1();           
   _NOP();    
   SCK_TO_0();     
   _NOP();        
}    
   
   
void s_connectionreset(void)   
//----------------------------------------------------------------------------------    
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart    
//       _____________________________________________________         ________    
// DATA:                                                      |_______|    
//          _    _    _    _    _    _    _    _    _        ___     ___    
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______    
{     
  unsigned char i;    
  DATA_TO_1();        
  _NOP();   
  SCK_TO_0();                    //Initial state       
  _NOP();   
  for(i=0;i<9;i++)                  //9 SCK cycles    
  { SCK_TO_1();    
    _NOP();   
    SCK_TO_0();   
    _NOP();   
  }   
  s_transstart();                   //transmission start    
}     
   
   
char s_measure(unsigned char *p_checksum, unsigned char mode)   
//----------------------------------------------------------------------------------    
// makes a measurement (humidity/temperature) with checksum    
{    
  unsigned error=0;   
  unsigned int i,j,k;   
   
  s_transstart();                   //transmission start    
  switch(mode){                     //send command to sensor    
    case TEMP   : error+=s_write_byte(MEASURE_TEMP); break;   
    case HUMI   : error+=s_write_byte(MEASURE_HUMI); break;   
    default     : break;        
  }   
  PORTF |=0x02;   
  DDRF &=0xfd;   
  for(k=0;k<65535u;k++)   
  {   
  for (i=0;i<65535u;i++)   
  {   
    j=PINF&0x02;//DATA_status();//PORTF&0x02;    
     if(j==0) break;   
    }    
    if(j==0)   
    break;   
  }   
       
     
     
  if(j) error+=1;                // or timeout (~2 sec.) is reached    
  cwendu1=s_read_byte(ACK);    //read the first byte (MSB)    
  cwendu2=s_read_byte(ACK);    //read the second byte (LSB)    
  uwendu =cwendu1*256+cwendu2;   
  *p_checksum =s_read_byte(noACK);   
     
  if(error>0)   
     PORTA |=0x02;  //read checksum    
  return error;   
}    
void calc_sth11(float *p_temperature)   
//void calc_sth11(float *p_humidity ,float *p_temperature)    
//----------------------------------------------------------------------------------------    
// calculates temperature [癈] and humidity [%RH]     
// input :  humi [Ticks] (12 bit)     
//          temp [Ticks] (14 bit)    
// output:  humi [%RH]    
//          temp [癈]    
{    
   
  //float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit     
  float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit    
  //float rh_lin;                     // rh_lin:  Humidity linear    
  //float rh_true;                    // rh_true: Temperature compensated humidity    
  float t_C;                        // t_C   :  Temperature [癈]    
   
  t_C=t*0.01 - 40;//-327.68;                  //calc. temperature from ticks to [癈]    
  //rh_lin=C3*rh*rh + C2*rh + C1;     //calc. humidity from ticks to [%RH]    
  //rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //calc. temperature compensated humidity [%RH]    
  //if(rh_true>100)rh_true=100;       //cut if the value is outside of    
  //if(rh_true<0.1)rh_true=0.1;       //the physical possible range    
   
  *p_temperature=t_C;               //return temperature [癈]    
  //*p_humidity=rh_true;              //return humidity[%RH]    
}   
   
/*float calc_dewpoint(float h,float t)   
//--------------------------------------------------------------------    
// calculates dew point    
// input:   humidity [%RH], temperature [癈]    
// output:  dew point [癈]    
{ float logEx,dew_point;   
  logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);   
  dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);   
  return dew_point;   
}   
*/   
   
   
   
void main()   
//----------------------------------------------------------------------------------    
// sample program that shows how to use SHT11 functions    
// 1. connection reset     
// 2. measure humidity [ticks](12 bit) and temperature [ticks](14 bit)    
// 3. calculate humidity [%RH] and temperature [癈]    
// 4. calculate dew point [癈]    
// 5. print temperature, humidity, dew point      
   
{ //value temp_val;//humi_val;    
    //unsigned int temp_new;    
  //float dew_point;    
  unsigned char error,checksum;   
  unsigned int i;   
    
     
  DDRA |=0x07;   
   //delay();    
   //delay();    
   //newdelay();    
  //init_uart();    
  //while(1)    
     
   
     
     
   //PORTA &=0xfb;    
   
     
    
  while(1)   
  {   
    shxx_config();   
    s_connectionreset();   
   error=0;   
    //error+=s_measure((unsigned char*) &humi_val.i,&checksum,HUMI);  //measure humidity    
    //error+=s_measure((unsigned char*) &temp_val.i,&checksum,TEMP);  //measure temperature    
    error+=s_measure(&checksum,TEMP);    
    if(error!=0)    
    s_connectionreset();   
    else   
    {      
     //for (i=0;i<60000;i++);        
        
    //PORTA &=0xfb;                //in case of an error: connection reset    
       
     //PORTA &=0xfb;    
        //PORTA =0x02;    
        //humi_val.f=(float)humi_val.i;                   //converts integer to float    
      fwendu=(float)uwendu;    
      calc_sth11(&fwendu);                   //converts integer to float    
      //calc_sth11(&humi_val.f,&temp_val.f);            //calculate humidity, temperature    
      //dew_point=calc_dewpoint(humi_val.f,temp_val.f); //calculate dew point    
      //printf("temp:%5.1fC humi:%5.1f%% dew point:%5.1fC\n",temp_val.f,humi_val.f,dew_point);    
     }   
    if(fwendu>30.0)   
     PORTA |=0x01;   
     else   
     PORTA &=0xfe;   
       
    //----------wait approx. 0.8s to avoid heating up SHTxx------------------------------          
    for (i=0;i<40000;i++);     //(be sure that the compiler doesn't eliminate this line!)    
    //-----------------------------------------------------------------------------------                           
  }   
}  

