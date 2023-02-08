
#include "stdafx.h"
#include "C:\data\infotek\svn\2010\gat\MainConsolAppl\CppFrame.h"


#define CNTRL00	"0"
#define CNTRL01 "1"
#define CNTRL02 "2"
#define CNTRL03 "3"
#define CNTRL04 "4"
#define CNTRL05 "5"
#define CNTRL06 "6"
#define CNTRL07 "7"
#define CNTRL08 "8"
#define CNTRL09 "9"
#define CNTRL10 "10"
#define CNTRL11 "11"

#define MessageType_Error			"E"
#define MessageType_Information		"I"
#define MessageType_Variable		"V"
#define MessageType_Configuration	"C"

#define GuiCommand_Reset			"RESET" 
#define GuiCommand_Sync				"SYNC" 
#define GuiCommand_InitProject		"00" 
#define GuiCommand_InitTextbox		"01" 
#define GuiCommand_InitSliderBar	"02"
#define GuiCommand_InitChart		"03"

#define ValueCommandType_Text	"00"
#define ValueCommandType_Float	"01"
#define cMaxMessageLen 256
class CArdoGuiMsg
{
public:
	CArdoGuiMsg();
	void SerialInit(long);
	void InfoText(char*);
	void ErrorText(char*);
	void ResetGui(void);
	void TimeSync(void);
	void InitProject(char*, char* );
	void InitTextBox(char* , char* , char* , int );
	void InitSlider(char* , char* , char* , int , double , double );
	void AddGraph(int , int , char* , char* , double , double );
	void Print(int , char* );
	void Print(int , float );
	char *ToString(char *, float );

private:
	char* BuildMessage(char *, char*);
	bool SendMessage(char *);
	int MessageChannel;
	char msgbuffer[cMaxMessageLen];
	char tmpbuffer[cMaxMessageLen];
	char tmpBuf[20];
	char milliBuf[20];

};

char * CArdoGuiMsg::ToString(char * retStr, float f)
{
	char tmpBuf1[20];
	int fV = (int)f;
	int fN = (f - fV) * 100000;
	fN = abs(fN);
	sprintf(tmpBuf1,"%d", fN);
	int i = strlen(tmpBuf1)-1;
	while(i >= 0)
	{
		if (tmpBuf1[i] != '0') break;
		tmpBuf1[i] = 0;
		i--;
	}
	if (strlen(tmpBuf1)==0)
	{
		sprintf(retStr,"%d", fV);
	}
	else
	{
		sprintf(retStr,"%d.%s", fV, tmpBuf1);
	}
	return retStr;
}

CArdoGuiMsg::CArdoGuiMsg(void)
{
		MessageChannel = -1;
}
void CArdoGuiMsg::SerialInit(long baud)
{
	MessageChannel = 1;
	Serial.begin(baud);
}

void CArdoGuiMsg::InfoText(char* txt)
{
	char * tmp = BuildMessage(MessageType_Information, txt);
	SendMessage(tmp);
}
void CArdoGuiMsg::ErrorText(char* txt)
{
	char * tmp = BuildMessage(MessageType_Error, txt);
	SendMessage(tmp);
}

char* CArdoGuiMsg::BuildMessage(char * command, char* content)
{
	char* tmpStrMilli = ltoa(millis(), milliBuf, 10);
	int len = 2;
	len += strlen(command);
	len += strlen(tmpStrMilli);
	len += strlen(content);
	if (len > cMaxMessageLen) return "BuildMessage length error: too long";

	strcpy(msgbuffer, command);
	strcat(msgbuffer, "_");
	strcat(msgbuffer, tmpStrMilli);
	strcat(msgbuffer, "_");
	strcat(msgbuffer, content);
	return msgbuffer;
}

bool CArdoGuiMsg::SendMessage(char* pString)
{
	if (MessageChannel == 1)
	{
		Serial.println(pString);
		return true;
	}
	return false;
}

void CArdoGuiMsg::ResetGui(void)
{
	char * tmp = BuildMessage(MessageType_Configuration, GuiCommand_Reset);
	SendMessage(tmp);
}

void CArdoGuiMsg::TimeSync(void)
{
	char * tmp = BuildMessage(MessageType_Configuration, GuiCommand_Sync);
	SendMessage(tmp);
}

void CArdoGuiMsg::InitProject( char* Name, char* Description)
{
	//string.Format("00_{0}_{1}", Name, Description);
	strcpy(tmpbuffer, GuiCommand_InitProject);

	int len =2;
	len += strlen(tmpbuffer);
	len += strlen(Name);
	len += strlen(Description);
	if (len > cMaxMessageLen) return;

	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, Name);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, Description);
    char * tmp = BuildMessage(MessageType_Configuration, tmpbuffer);
	SendMessage(tmp);
}

void CArdoGuiMsg::InitTextBox(char* TextBoxNumber, char* HeaderText, char* UnitText, int VarId)
{
	//return string.Format("01_{0}_{1}_{2}_{3}", BoxNumber, HeaderText, UnitText, VarId);
	strcpy(tmpbuffer, GuiCommand_InitTextbox);
	strcat(tmpbuffer, "_");

	int len =4;
	len += strlen(TextBoxNumber);
	len += strlen(HeaderText);
	len += strlen(UnitText);
	if (len > cMaxMessageLen) return;

	strcat(tmpbuffer, TextBoxNumber);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, HeaderText);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, UnitText);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", VarId);
	strcat(tmpbuffer, tmpBuf);
    char * tmp = BuildMessage(MessageType_Configuration, tmpbuffer);
	SendMessage(tmp);
}

void CArdoGuiMsg::AddGraph(int chartNo, int VarID, char* GraphName, char* UnitText, double min, double max)
{
	//return string.Format("03_{0}_{1}_{2}_{3}_{4}_{5}", chartNo, varID, GraphName, UnitText, min, max);
	if (cMaxMessageLen < 150) return;

	strcpy(tmpbuffer, GuiCommand_InitChart);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", chartNo);
	strcat(tmpbuffer, tmpBuf);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", VarID);
	strcat(tmpbuffer, tmpBuf);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, GraphName);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, UnitText);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer,ToString(tmpBuf, min));
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer,ToString(tmpBuf, max));
	
    char * tmp = BuildMessage(MessageType_Configuration, tmpbuffer);
	SendMessage(tmp);

}

void CArdoGuiMsg::InitSlider(char* SliderNumber, char* HeaderText, char* UnitText, int VarId, double min, double max)
{
	//return string.Format("02_{0}_{1}_{2}_{3}_{4}_{5}", BoxNumber, HeaderText, UnitText, VarId, min, max);
	int len =24;
	len += strlen(SliderNumber);
	len += strlen(HeaderText);
	len += strlen(UnitText);
	if (len > cMaxMessageLen) return;
	
	strcpy(tmpbuffer, GuiCommand_InitSliderBar);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, SliderNumber);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, HeaderText);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, UnitText);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", VarId);
	strcat(tmpbuffer, tmpBuf);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer,ToString(tmpBuf, min));
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer,ToString(tmpBuf, max));
    char * tmp = BuildMessage(MessageType_Configuration, tmpbuffer);
	SendMessage(tmp);
}


void CArdoGuiMsg::Print(int  VarId, char* content)
{
	//return string.Format("00_{0}_{1}",  VarId, content);
	int len =20;
	len += strlen(content);
	if (len > cMaxMessageLen) return;
	
	strcpy(tmpbuffer, ValueCommandType_Text);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", VarId);
	strcat(tmpbuffer, tmpBuf);
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, content);
	char * tmp = BuildMessage(MessageType_Variable, tmpbuffer);
	SendMessage(tmp);
}

void CArdoGuiMsg::Print(int VarId, float value)
{
	if (cMaxMessageLen < 50) return;
	
	strcpy(tmpbuffer, ValueCommandType_Float);
	strcat(tmpbuffer, "_");
	sprintf(tmpBuf,"%d", VarId);
	strcat(tmpbuffer, tmpBuf);
	strcat(tmpbuffer,ToString(tmpBuf, value));
	strcat(tmpbuffer, "_");
	strcat(tmpbuffer, tmpBuf);
	char * tmp = BuildMessage(MessageType_Variable, tmpbuffer);
	SendMessage(tmp);
}


int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
CArdoGuiMsg ArdoGuiMsg;

void GuiCfg()
{
	ArdoGuiMsg.ResetGui();
	ArdoGuiMsg.InitProject("Test1Project", "Test Projekt");

	ArdoGuiMsg.InitTextBox(CNTRL00, "TextBox 1", "C", 0);
	ArdoGuiMsg.InitSlider(CNTRL00, "Slider 1", "Temp", 0, 0.0, 100.0);

	ArdoGuiMsg.InfoText("Hallo world, Info");
	ArdoGuiMsg.ErrorText("Hallo world, error");

	ArdoGuiMsg.AddGraph(0, 1,  "Temperatur 1", "C", -10.12345, 80.123456);
	ArdoGuiMsg.AddGraph(0, 2,  "Temperatur 2", "C", -10.0, 80);
	ArdoGuiMsg.AddGraph(0, 3,  "Temperatur 3", "C", -10.0, 80);

	ArdoGuiMsg.TimeSync();
}

void setup() 
{
	ArdoGuiMsg.SerialInit(115200);
	Serial.println("Boot...");
	pinMode(ledPin, OUTPUT);     
	GuiCfg();
}
char milliBuf[20];
void loop() 
{
	
	while (Serial.available() > 0) 
	{   
        char ch = Serial.read ();    /* Read user comand */
		if (ch == 'r')
		{
			GuiCfg();
		}

	}
	sensorValue ++;
	ltoa(millis(), milliBuf, 10);
	ArdoGuiMsg.Print( 0, milliBuf);
	ArdoGuiMsg.InfoText("Hallo world, Info");
	digitalWrite(ledPin, HIGH);   // set the LED on
	delay(500);                  // wait for a second
	digitalWrite(ledPin, LOW);    // set the LED off
	delay(500);                  // wait for a second
}

