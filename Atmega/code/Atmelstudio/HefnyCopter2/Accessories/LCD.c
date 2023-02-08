/*
 * lcd.c
 *
 * Created: 27.07.2012 10:06:52
 *  Author: OliverS
 *
 * $Id: lcd.c 27 2012-08-15 18:18:23Z olischulz24@googlemail.com $
*/ 


#include "../Include/typedefs.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/wdt.h>

#include <string.h>
#include <stdlib.h>

//#include "../Include/GlobalValues.h"
#include "../Include/IO_config.h"
#include "../Include/GlobalValues.h"
#include "../Include/Sensors.h"
#include "../Include/lcd.h"
#include "../Include/fonts.h"





#define REVERSED	1
static uint8_t _flags = 0;

#define LCDWIDTH	128
#define LCDHEIGHT	64

static uint8_t _screen[LCDWIDTH * LCDHEIGHT / 8];
static uint8_t _curx, _cury;
static fontdescriptor_t _font;

static void sendByte(uint8_t byte)
{
	for (uint8_t i = 8; i; i--)
	{
		LCD_SCL = 0;
		
		if (byte & 0x80) // read MSB [& b10000000]
			LCD_SDA = 1;
		else
			LCD_SDA = 0;
		
		LCD_SCL = 1;
		byte <<= 1;
	}
}

//static void sendCommand(uint8_t command)
//{
	//LCD_CS = 0;
	//LCD_A0 = 0;
	//sendByte(command);
	//LCD_CS = 1;
//}

static void sendData(uint8_t data, uint8_t CommandorData)
{
	LCD_CS = 0;
	LCD_A0 = CommandorData;
	sendByte(data);
	LCD_CS = 1;
}

static void setPos(uint8_t line, uint8_t column)
{
	sendData(0xB0 | (line & 0x07), LCD_COMMAND);
	sendData(0x10 | (column >> 4), LCD_COMMAND);
	sendData(column & 0x0f, LCD_COMMAND);
}

__attribute__ ((section(".lowtext")))
ISR(TIMER0_OVF_vect, ISR_NOBLOCK)
{
	TCNT0_X +=1;
	static uint16_t offset;
	
	if (offset % LCDWIDTH == 0)
		setPos(offset / LCDWIDTH, 0);
		
	sendData(*(_screen + offset++), LCD_DATA);
	offset %= sizeof(_screen);
}

void LCD_SetPos(uint8_t line, uint8_t column)
{
	_curx = column % LCDWIDTH;
	_cury = line * 8;
}

void lcdXY(uint8_t x, uint8_t y)
{
	_curx = x;
	_cury = y;
}

void lcdSetPixel(uint8_t x, uint8_t y, uint8_t on)
{
	static const prog_char masks[8] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
	uint8_t *scr = _screen + x + (y / 8 * LCDWIDTH); 
	uint8_t mask = pgm_read_byte(&masks[y % 8]);
	if ((_flags & REVERSED) ^ !on)
		*scr = *scr & ~mask;
	else
		*scr = *scr | mask;
}

static void lcdSetByte(uint8_t x, uint8_t y, uint8_t b)
{
	uint8_t *scr = _screen + x + (y / 8 * LCDWIDTH); 
	if (_flags & REVERSED)
		*scr = ~b;
	else
		*scr = b;
}


void LCD_Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	// simple optimized bresenham algorithm
	////int8_t dx =  abs(x1 - x0);
	////int8_t sx = x0 < x1 ? 1 : -1;
	////int8_t dy = -abs(y1 - y0);
	////int8_t sy = y0 < y1 ? 1 : -1; 
	////int16_t err = dx + dy, e2; /* error value e_xy */
 ////
	////for(;;)
	////{
		////lcdSetPixel(x0, y0, 1);
		////
		////if (x0 == x1 && y0 == y1)
			////break;
			////
		////e2 = 2 * err;
		////if (e2 > dy) { err += dy; x0 += sx; } /* e_xy + e_x > 0 */
		////if (e2 < dx) { err += dx; y0 += sy; } /* e_xy + e_y < 0 */
	////}
}

void LCD_Rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{
	//uint8_t a;
	//if (x0 > x1) { a = x0; x0 = x1; x1 = a;}
	//if (y0 > y1) { a = y0; y0 = y1; y1 = a;}
	//for (a = x0; a <= x1; a++)
	//{
		//lcdSetPixel(a, y0, color);
		//lcdSetPixel(a, y1, color);
	//}
	//for (a = y0; a <= y1; a++)
	//{
		//lcdSetPixel(x0, a, color);
		//lcdSetPixel(x1, a, color);
	//}
}

void LCD_FillRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{
	//uint8_t a;
	//if (x0 > x1) { a = x0; x0 = x1; x1 = a;}
	//if (y0 > y1) { a = y0; y0 = y1; y1 = a;}
	//for (a = y0; a <= y1; a++)
		//for(uint8_t i = x0; i <= x1; i++)
			//lcdSetPixel(i, a, color);
}
 
void LCD_Clear()
{
	memset(_screen, 0, sizeof(_screen));
	LCD_SetPos(0, 0);
	_flags = 0;
}

void lcdWriteSprite_P(PGM_P sprite, uint8_t sizeX, uint8_t sizeY, uint8_t mode)
{
	uint8_t b = 0;
	for (uint8_t i = 0; i < sizeX; i++)
	{
		for (uint8_t j = 0; j < sizeY; j++)
		{
			if (j % 8 == 0)
					b = pgm_read_byte(sprite++);
					
			if (mode == ROP_COPY)
			{
				if ((_cury % 8 == 0) && (sizeY - j >= 8))
				{
					lcdSetByte(_curx + i, _cury + j, b);
					j += 7; // just +7 b/c the loop increments anyway
				}
				else
					lcdSetPixel(_curx + i, _cury + j, b & 0x01);
			}				
			else if (mode == ROP_PAINT)
			{
				if (b & 0x01)
					lcdSetPixel(_curx + i, _cury + j, 1);
			}			
			b >>= 1;
		}
	}	
}

void lcdWriteGlyph_P(const glyph_t *glyph, uint8_t mode)
{
	uint8_t sizeX = pgm_read_byte(&glyph->sizeX);
	uint8_t sizeY = pgm_read_byte(&glyph->sizeY);
	lcdWriteSprite_P((PGM_P)&glyph->glyph, sizeX, sizeY, mode);
}

void lcdWriteChar(char c)
{
	if (c == '\n')
	{
		_cury += _font.sizeY;
		_curx = 0;
	}
	else
	{
		lcdWriteSprite_P(_font.selector(c), _font.sizeX, _font.sizeY, 0);
		_curx += _font.sizeX;
	}
}

void LCD_WriteString(char *s)
{
	while (*s)
	{
		lcdWriteChar(*s);
		s++;
	}		
}



void LCD_WriteStringex(uint8_t x, uint8_t y, char *str, BOOL LCDReverse)
{
	lcdReverse(LCDReverse);
	LCD_SetPos(x, y);
	while (*str)
	{
		lcdWriteChar(*str);
		str++;
	}		
	lcdReverse(0);
}



void LCD_WriteString_P(PGM_P s)
{
	char c;
	while ((c = pgm_read_byte(s++)))
		lcdWriteChar(c);
}


void LCD_WriteString_Pex(uint8_t x, uint8_t y, PGM_P str, uint8_t len, BOOL LCDReverse)
{
	lcdReverse(LCDReverse);
	LCD_SetPos(x, y);
	LCD_WritePadded_P(str, len);
	lcdReverse(0);
}


void lcdReverse(uint8_t reversed)
{
	if (reversed)
		_flags |= REVERSED;
	else
		_flags &= ~REVERSED;
}


void LCD_WriteSpace(uint8_t len)
{
	for (uint8_t i = 0; i < len; i++)
		lcdWriteChar(32);
}

void LCD_WritePadded(char *s, uint8_t len)
{
	LCD_WriteString(s);
	LCD_WriteSpace(len - strlen(s));
}


void LCD_WritePadded_P(const char *s, uint8_t len)
{
	LCD_WriteString_P(s);
	LCD_WriteSpace(len - strlen_P(s));
}

void LCD_WriteValue_double_ex(uint8_t x, uint8_t y, double value, int8_t len, BOOL LCDReverse)
{
	char s[17];
	dtostrf(value, len-2,2, s);
	//itoa(value, s, 10);
	lcdReverse(LCDReverse);
	LCD_SetPos(x, y);
	LCD_WritePadded(s, len-2);
	lcdReverse(0);

}
void LCD_WriteValue_double(uint8_t x, uint8_t y, double value,  BOOL LCDReverse)
{
	LCD_WriteValue_double_ex(x,y,value,5,LCDReverse);
}

void LCD_WriteValue(uint8_t x, uint8_t y, int16_t value, uint8_t len, BOOL LCDReverse)
{
	char s[7];
	itoa(value, s, 10);
	lcdReverse(LCDReverse);
	LCD_SetPos(x, y);
	LCD_WritePadded(s, len);
	lcdReverse(0);
}

void lcdSetContrast(uint8_t contrast)
{
	uint8_t t = TIMSK0;
	LCD_Disable();
	sendData(0x81, LCD_COMMAND);
	sendData(contrast & 0x3F, LCD_COMMAND); 
	TIMSK0 = t;
}

void LCD_Enable()
{
	// reset timer0 to avoid re-entrant call of ISR b/c it is non blocking
	TCNT0 = 0;
	TIFR0 = _BV(TOV0);
	TIMSK0 |= _BV(TOIE0);	// enable interrupt on overflow
}

void LCD_Disable()
{
	TIMSK0 &= ~_BV(TOIE0);	// disable overflow interrupt
}

void LCD_SelectFont(const fontdescriptor_t *font)
{
	if (font == NULL)
		font = &font6x8;
	memcpy_P(&_font, font, sizeof(_font));
}

static const prog_uchar _initSeq[] = {
	
	0xA2, // set bias to 1/9
	0xA0, // SEG output direction = normal
	0xC8, // COM output direction = reversed
	0x40, // start line = 0
	0xA6, // Normal Display
	0xA4, // display all points = OFF
	0x2F, // Power Control Set
	0x24, // set ra/rb
	0x81, // set contrast
	0x20, // -> to 31
	0xAF, // Display on
	0x00, // (terminator)
	/*
	0xAF, // Display on
	0x40, // start line = 0
	0xA0, // SEG output direction = normal
	0xA6, // Normal Display
	0xA4, // display all points = OFF
	0xA2, // set bias to 1/9
	0xee, // NEW
	0xC8, // COM output direction = reversed
	0x2F, // Power Control Set
	0x24, // set ra/rb
	0xac,
	0x00, // (terminator)
	0xf8,
	0x00,
	0xe3,
	0xff // end of array
	*/
};

void LCD_Init()
{
	// pins
	LCD_CS_DIR = OUTPUT;
	LCD_RST_DIR = OUTPUT;
	LCD_A0_DIR = OUTPUT;
	LCD_SCL_DIR = OUTPUT;
	LCD_SDA_DIR = OUTPUT;

	// init display
	LCD_RST = 0;
	_delay_ms(1);	// version 0.9.9
	LCD_RST = 1;
	_delay_ms(1); // version 0.9.9
	
	const unsigned char* ptr = _initSeq;
	uint8_t c;
	while ((c = pgm_read_byte(ptr++)))
	{
		sendData(c, LCD_COMMAND);
	}	
	LCD_SelectFont(NULL);		// select default font
	
	// use timer0 with clk/8 and overflow
	// at 256 as interrupt based output of data bytes
	// ie every 1024us one byte is send to display. whole screen takes about 105ms
	TCCR0B = _BV(CS01);		// clk/8
	LCD_Enable();
}

