/*
 * font12x16.c
 *
 * Created: 14.08.2012 17:51:09
 *  Author: OliverS
 *
 * $Id: font12x16.c 27 2012-08-15 18:18:23Z olischulz24@googlemail.com $
 */ 

#include "../Include/Fonts.h"
#include <avr/pgmspace.h>

#define BYTESPERCHAR	24UL

static const prog_uchar _font12x16map[] = {
	/*
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x00
	0x00,0x00,0xF0,0x03,0x0C,0x0C,0x02,0x10,0x32,0x11,0x31,0x22,0x01,0x22,0x31,0x22,0x32,0x11,0x02,0x10,0x0C,0x0C,0xF0,0x03,	// 0x01
	0x00,0x00,0xF0,0x03,0xFC,0x0F,0xFE,0x1F,0xCE,0x1E,0xCF,0x3D,0xFF,0x3D,0xCF,0x3D,0xCE,0x1E,0xFE,0x1F,0xFC,0x0F,0xF0,0x03,	// 0x02
	0x00,0x00,0x00,0x00,0xF0,0x00,0xF8,0x01,0xF8,0x03,0xF0,0x07,0xE0,0x0F,0xF0,0x07,0xF8,0x03,0xF8,0x01,0xF0,0x00,0x00,0x00,	// 0x03
	0x00,0x00,0x00,0x00,0x80,0x00,0xC0,0x01,0xE0,0x03,0xF0,0x07,0xF8,0x0F,0xF0,0x07,0xE0,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,	// 0x04
	0x00,0x00,0x80,0x03,0xC0,0x07,0xC0,0x07,0xB8,0x13,0xFC,0x1B,0xFC,0x1F,0xFC,0x1B,0xB8,0x13,0xC0,0x07,0xC0,0x07,0x80,0x03,	// 0x05
	0x00,0x00,0x00,0x00,0x80,0x03,0xC0,0x07,0xE0,0x17,0xF0,0x1B,0xFC,0x1F,0xF0,0x1B,0xE0,0x17,0xC0,0x07,0x80,0x03,0x00,0x00,	// 0x06
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x07
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x08
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x09
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x0A
	0x00,0x00,0x80,0x03,0xC0,0x07,0x60,0x0C,0x20,0x08,0x20,0x08,0x60,0x0C,0xC8,0x07,0xA8,0x03,0x18,0x00,0x78,0x00,0x00,0x00,	// 0x0B
	0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0xF8,0x08,0x8C,0x09,0x04,0x3F,0x04,0x3F,0x8C,0x09,0xF8,0x08,0x70,0x00,0x00,0x00,	// 0x0C
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x0D
	0x00,0x00,0x00,0x06,0x00,0x0F,0x00,0x0F,0xFF,0x07,0x33,0x00,0x66,0x30,0xCC,0x78,0x98,0x79,0xF0,0x3F,0x00,0x00,0x00,0x00,	// 0x0E
	0x00,0x00,0x80,0x00,0xC8,0x09,0xF0,0x07,0x30,0x06,0x18,0x0C,0x1E,0x3C,0x18,0x0C,0x30,0x06,0xF0,0x07,0xC8,0x09,0x80,0x00,	// 0x0F
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x1F,0xF8,0x0F,0xF0,0x07,0xE0,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x10
	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0xC0,0x01,0xE0,0x03,0xF0,0x07,0xF8,0x0F,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x11
	0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x04,0x18,0x0C,0x1C,0x1C,0xFE,0x3F,0x1C,0x1C,0x18,0x0C,0x10,0x04,0x00,0x00,0x00,0x00,	// 0x12
	0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x37,0xFE,0x37,0x00,0x00,0x00,0x00,0xFE,0x37,0xFE,0x37,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x13
	0x00,0x00,0x38,0x00,0x7C,0x00,0xC6,0x00,0x82,0x00,0xFE,0x3F,0xFE,0x3F,0x02,0x00,0xFE,0x3F,0xFE,0x3F,0x02,0x00,0x00,0x00,	// 0x14
	0x00,0x00,0x00,0x00,0xDC,0x08,0xFE,0x19,0x22,0x11,0x22,0x11,0x22,0x11,0x22,0x11,0xE6,0x1F,0xC4,0x0E,0x00,0x00,0x00,0x00,	// 0x15
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x00,	// 0x16
	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x44,0x0C,0x4C,0x0E,0x5C,0xFF,0x7F,0x0E,0x5C,0x0C,0x4C,0x08,0x44,0x00,0x00,0x00,0x00,	// 0x17
	0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x18,0x00,0x1C,0x00,0xFE,0x3F,0x1C,0x00,0x18,0x00,0x10,0x00,0x00,0x00,0x00,0x00,	// 0x18
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x0C,0x00,0x1C,0xFE,0x3F,0x00,0x1C,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,0x00,	// 0x19
	0x00,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xF0,0x07,0xE0,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,	// 0x1A
	0x00,0x00,0x00,0x00,0x80,0x00,0xC0,0x01,0xE0,0x03,0xF0,0x07,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00,	// 0x1B
	0x00,0x00,0x00,0x3F,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,	// 0x1C
	0x00,0x00,0x80,0x00,0xC0,0x01,0xE0,0x03,0xF0,0x07,0x80,0x00,0x80,0x00,0x80,0x00,0xF0,0x07,0xE0,0x03,0xC0,0x01,0x80,0x00,	// 0x1D
	0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x07,0x80,0x07,0xC0,0x07,0xE0,0x07,0xC0,0x07,0x80,0x07,0x00,0x07,0x00,0x06,0x00,0x04,	// 0x1E
	0x00,0x00,0x20,0x00,0x60,0x00,0xE0,0x00,0xE0,0x01,0xE0,0x03,0xE0,0x07,0xE0,0x03,0xE0,0x01,0xE0,0x00,0x60,0x00,0x20,0x00,	// 0x1F
	*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x20
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x00,0xFF,0x33,0xFF,0x33,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x21
	0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x22
	0x00,0x00,0x00,0x02,0x10,0x1E,0x90,0x1F,0xF0,0x03,0x7E,0x02,0x1E,0x1E,0x90,0x1F,0xF0,0x03,0x7E,0x02,0x1E,0x00,0x10,0x00,	// 0x23
	0x00,0x00,0x00,0x00,0x78,0x04,0xFC,0x0C,0xCC,0x0C,0xFF,0x3F,0xFF,0x3F,0xCC,0x0C,0xCC,0x0F,0x88,0x07,0x00,0x00,0x00,0x00,	// 0x24
	0x00,0x00,0x00,0x30,0x38,0x38,0x38,0x1C,0x38,0x0E,0x00,0x07,0x80,0x03,0xC0,0x01,0xE0,0x38,0x70,0x38,0x38,0x38,0x1C,0x00,	// 0x25
	0x00,0x00,0x00,0x00,0x00,0x1F,0xB8,0x3F,0xFC,0x31,0xC6,0x21,0xE2,0x37,0x3E,0x1E,0x1C,0x1C,0x00,0x36,0x00,0x22,0x00,0x00,	// 0x26
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x27,0x00,0x3F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x27
	0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x03,0xFC,0x0F,0xFE,0x1F,0x07,0x38,0x01,0x20,0x01,0x20,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x28
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x20,0x01,0x20,0x07,0x38,0xFE,0x1F,0xFC,0x0F,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x29
	0x00,0x00,0x00,0x00,0x98,0x0C,0xB8,0x0E,0xE0,0x03,0xF8,0x0F,0xF8,0x0F,0xE0,0x03,0xB8,0x0E,0x98,0x0C,0x00,0x00,0x00,0x00,	// 0x2A
	0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x80,0x01,0xF0,0x0F,0xF0,0x0F,0x80,0x01,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00,	// 0x2B
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB8,0x00,0xF8,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x2C
	0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00,	// 0x2D
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x2E
	0x00,0x00,0x00,0x18,0x00,0x1C,0x00,0x0E,0x00,0x07,0x80,0x03,0xC0,0x01,0xE0,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,	// 0x2F
	0x00,0x00,0xF8,0x07,0xFE,0x1F,0x06,0x1E,0x03,0x33,0x83,0x31,0xC3,0x30,0x63,0x30,0x33,0x30,0x1E,0x18,0xFE,0x1F,0xF8,0x07,	// 0x30
	0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x30,0x0C,0x30,0x0E,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,	// 0x31
	0x00,0x00,0x1C,0x30,0x1E,0x38,0x07,0x3C,0x03,0x3E,0x03,0x37,0x83,0x33,0xC3,0x31,0xE3,0x30,0x77,0x30,0x3E,0x30,0x1C,0x30,	// 0x32
	0x00,0x00,0x0C,0x0C,0x0E,0x1C,0x07,0x38,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x39,0x7E,0x1F,0x3C,0x0E,	// 0x33
	0x00,0x00,0xC0,0x03,0xE0,0x03,0x70,0x03,0x38,0x03,0x1C,0x03,0x0E,0x03,0x07,0x03,0xFF,0x3F,0xFF,0x3F,0x00,0x03,0x00,0x03,	// 0x34
	0x00,0x00,0x3F,0x0C,0x7F,0x1C,0x63,0x38,0x63,0x30,0x63,0x30,0x63,0x30,0x63,0x30,0x63,0x30,0xE3,0x38,0xC3,0x1F,0x83,0x0F,	// 0x35
	0x00,0x00,0xC0,0x0F,0xF0,0x1F,0xF8,0x39,0xDC,0x30,0xCE,0x30,0xC7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x39,0x80,0x1F,0x00,0x0F,	// 0x36
	0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x30,0x03,0x3C,0x03,0x0F,0xC3,0x03,0xF3,0x00,0x3F,0x00,0x0F,0x00,0x03,0x00,	// 0x37
	0x00,0x00,0x00,0x0F,0xBC,0x1F,0xFE,0x39,0xE7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x30,0xFE,0x39,0xBC,0x1F,0x00,0x0F,	// 0x38
	0x00,0x00,0x3C,0x00,0x7E,0x00,0xE7,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x38,0xC3,0x1C,0xC3,0x0E,0xE7,0x07,0xFE,0x03,0xFC,0x00,	// 0x39
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x1C,0x70,0x1C,0x70,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x3A
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x9C,0x70,0xFC,0x70,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x3B
	0x00,0x00,0x00,0x00,0xC0,0x00,0xE0,0x01,0xF0,0x03,0x38,0x07,0x1C,0x0E,0x0E,0x1C,0x07,0x38,0x03,0x30,0x00,0x00,0x00,0x00,	// 0x3C
	0x00,0x00,0x00,0x00,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x00,0x00,	// 0x3D
	0x00,0x00,0x00,0x00,0x03,0x30,0x07,0x38,0x0E,0x1C,0x1C,0x0E,0x38,0x07,0xF0,0x03,0xE0,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,	// 0x3E
	0x00,0x00,0x1C,0x00,0x1E,0x00,0x07,0x00,0x03,0x00,0x83,0x37,0xC3,0x37,0xE3,0x00,0x77,0x00,0x3E,0x00,0x1C,0x00,0x00,0x00,	// 0x3F
	0x00,0x00,0xF8,0x0F,0xFE,0x1F,0x07,0x18,0xF3,0x33,0xFB,0x37,0x1B,0x36,0xFB,0x37,0xFB,0x37,0x07,0x36,0xFE,0x03,0xF8,0x01,	// 0x40
	0x00,0x00,0x00,0x38,0x00,0x3F,0xE0,0x07,0xFC,0x06,0x1F,0x06,0x1F,0x06,0xFC,0x06,0xE0,0x07,0x00,0x3F,0x00,0x38,0x00,0x00,	// 0x41
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xE7,0x30,0xFE,0x39,0xBC,0x1F,0x00,0x0F,0x00,0x00,	// 0x42
	0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0x0C,0x0C,0x00,0x00,	// 0x43
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0xFC,0x0F,0xF0,0x03,0x00,0x00,	// 0x44
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0x03,0x30,0x03,0x30,0x00,0x00,	// 0x45
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0x03,0x00,0x03,0x00,0x00,0x00,	// 0x46
	0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC7,0x3F,0xC6,0x3F,0x00,0x00,	// 0x47
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x00,	// 0x48
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x49
	0x00,0x00,0x00,0x0E,0x00,0x1E,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0xFF,0x1F,0xFF,0x07,0x00,0x00,	// 0x4A
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0xE0,0x01,0xF0,0x03,0x38,0x07,0x1C,0x0E,0x0E,0x1C,0x07,0x38,0x03,0x30,0x00,0x00,	// 0x4B
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x00,	// 0x4C
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x1E,0x00,0x78,0x00,0xE0,0x01,0xE0,0x01,0x78,0x00,0x1E,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x00,	// 0x4D
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x0E,0x00,0x38,0x00,0xF0,0x00,0xC0,0x03,0x00,0x07,0x00,0x1C,0xFF,0x3F,0xFF,0x3F,0x00,0x00,	// 0x4E
	0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0xFC,0x0F,0xF0,0x03,0x00,0x00,	// 0x4F
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x83,0x01,0x83,0x01,0x83,0x01,0x83,0x01,0x83,0x01,0xC7,0x01,0xFE,0x00,0x7C,0x00,0x00,0x00,	// 0x50
	0x00,0x00,0xF0,0x03,0xFC,0x0F,0x0E,0x1C,0x07,0x38,0x03,0x30,0x03,0x36,0x07,0x3E,0x0E,0x1C,0xFC,0x3F,0xF0,0x33,0x00,0x00,	// 0x51
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x83,0x01,0x83,0x01,0x83,0x03,0x83,0x07,0x83,0x0F,0xC7,0x1D,0xFE,0x38,0x7C,0x30,0x00,0x00,	// 0x52
	0x00,0x00,0x3C,0x0C,0x7E,0x1C,0xE7,0x38,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC3,0x30,0xC7,0x39,0x8E,0x1F,0x0C,0x0F,0x00,0x00,	// 0x53
	0x00,0x00,0x00,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00,	// 0x54
	0x00,0x00,0xFF,0x07,0xFF,0x1F,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x38,0xFF,0x1F,0xFF,0x07,0x00,0x00,	// 0x55
	0x00,0x00,0x07,0x00,0x3F,0x00,0xF8,0x01,0xC0,0x0F,0x00,0x3E,0x00,0x3E,0xC0,0x0F,0xF8,0x01,0x3F,0x00,0x07,0x00,0x00,0x00,	// 0x56
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x1C,0x00,0x06,0x80,0x03,0x80,0x03,0x00,0x06,0x00,0x1C,0xFF,0x3F,0xFF,0x3F,0x00,0x00,	// 0x57
	0x00,0x00,0x03,0x30,0x0F,0x3C,0x1C,0x0E,0x30,0x03,0xE0,0x01,0xE0,0x01,0x30,0x03,0x1C,0x0E,0x0F,0x3C,0x03,0x30,0x00,0x00,	// 0x58
	0x00,0x00,0x03,0x00,0x0F,0x00,0x3C,0x00,0xF0,0x00,0xC0,0x3F,0xC0,0x3F,0xF0,0x00,0x3C,0x00,0x0F,0x00,0x03,0x00,0x00,0x00,	// 0x59
	0x00,0x00,0x03,0x30,0x03,0x3C,0x03,0x3E,0x03,0x33,0xC3,0x31,0xE3,0x30,0x33,0x30,0x1F,0x30,0x0F,0x30,0x03,0x30,0x00,0x00,	// 0x5A
	0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x5B
	0x00,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0xE0,0x00,0xC0,0x01,0x80,0x03,0x00,0x07,0x00,0x0E,0x00,0x1C,0x00,0x18,	// 0x5C
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x30,0x03,0x30,0x03,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x5D
	0x00,0x00,0x60,0x00,0x70,0x00,0x38,0x00,0x1C,0x00,0x0E,0x00,0x07,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0x60,0x00,	// 0x5E
	0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,	// 0x5F
	/*
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x7E,0x00,0x4E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x60
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0x61
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0x62
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xC0,0x18,0x80,0x08,0x00,0x00,	// 0x63
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x30,0xC0,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x00,	// 0x64
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x3B,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0xC0,0x13,0x80,0x01,0x00,0x00,	// 0x65
	0x00,0x00,0xC0,0x00,0xC0,0x00,0xFC,0x3F,0xFE,0x3F,0xC7,0x00,0xC3,0x00,0xC3,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x66
	0x00,0x00,0x80,0x03,0xC0,0xC7,0xE0,0xCE,0x60,0xCC,0x60,0xCC,0x60,0xCC,0x60,0xCC,0x60,0xE6,0xE0,0x7F,0xE0,0x3F,0x00,0x00,	// 0x67
	0x00,0x00,0xFF,0x3F,0xFF,0x3F,0xC0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00,0x00,0x00,	// 0x68
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x60,0x30,0xEC,0x3F,0xEC,0x3F,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x69
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0xE0,0x00,0xC0,0x60,0xC0,0xEC,0xFF,0xEC,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x6A
	0x00,0x00,0x00,0x00,0xFF,0x3F,0xFF,0x3F,0x00,0x03,0x80,0x07,0xC0,0x0F,0xE0,0x1C,0x60,0x38,0x00,0x30,0x00,0x00,0x00,0x00,	// 0x6B
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x6C
	0x00,0x00,0xE0,0x3F,0xC0,0x3F,0xE0,0x00,0xE0,0x00,0xC0,0x3F,0xC0,0x3F,0xE0,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00,	// 0x6D
	0x00,0x00,0x00,0x00,0xE0,0x3F,0xE0,0x3F,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x3F,0x80,0x3F,0x00,0x00,	// 0x6E
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x60,0x30,0x60,0x30,0x60,0x30,0x60,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0x6F
	0x00,0x00,0xE0,0xFF,0xE0,0xFF,0x60,0x0C,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0xE0,0x1C,0xC0,0x0F,0x80,0x07,0x00,0x00,	// 0x70
	0x00,0x00,0x80,0x07,0xC0,0x0F,0xE0,0x1C,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0x60,0x0C,0xE0,0xFF,0xE0,0xFF,0x00,0x00,	// 0x71
	0x00,0x00,0x00,0x00,0xE0,0x3F,0xE0,0x3F,0xC0,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0x60,0x00,0xE0,0x00,0xC0,0x00,0x00,0x00,	// 0x72
	0x00,0x00,0xC0,0x11,0xE0,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x33,0x60,0x3F,0x40,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x73
	0x00,0x00,0x60,0x00,0x60,0x00,0xFE,0x1F,0xFE,0x3F,0x60,0x30,0x60,0x30,0x60,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x74
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x00,0x38,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0x75
	0x00,0x00,0x60,0x00,0xE0,0x01,0x80,0x07,0x00,0x1E,0x00,0x38,0x00,0x38,0x00,0x1E,0x80,0x07,0xE0,0x01,0x60,0x00,0x00,0x00,	// 0x76
	0x00,0x00,0xE0,0x07,0xE0,0x1F,0x00,0x38,0x00,0x1C,0xE0,0x0F,0xE0,0x0F,0x00,0x1C,0x00,0x38,0xE0,0x1F,0xE0,0x07,0x00,0x00,	// 0x77
	0x00,0x00,0x60,0x30,0xE0,0x38,0xC0,0x1D,0x80,0x0F,0x00,0x07,0x80,0x0F,0xC0,0x1D,0xE0,0x38,0x60,0x30,0x00,0x00,0x00,0x00,	// 0x78
	0x00,0x00,0x00,0x00,0x60,0x00,0xE0,0x81,0x80,0xE7,0x00,0x7E,0x00,0x1E,0x80,0x07,0xE0,0x01,0x60,0x00,0x00,0x00,0x00,0x00,	// 0x79
	0x00,0x00,0x60,0x30,0x60,0x38,0x60,0x3C,0x60,0x36,0x60,0x33,0xE0,0x31,0xE0,0x30,0x60,0x30,0x20,0x30,0x00,0x00,0x00,0x00,	// 0x7A
	0x00,0x00,0x00,0x00,0x80,0x00,0xC0,0x01,0xFC,0x1F,0x7E,0x3F,0x07,0x70,0x03,0x60,0x03,0x60,0x03,0x60,0x00,0x00,0x00,0x00,	// 0x7B
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x3F,0xBF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x7C
	0x00,0x00,0x00,0x00,0x03,0x60,0x03,0x60,0x03,0x60,0x07,0x70,0x7E,0x3F,0xFC,0x1F,0xC0,0x01,0x80,0x00,0x00,0x00,0x00,0x00,	// 0x7D
	0x00,0x00,0x10,0x00,0x18,0x00,0x0C,0x00,0x04,0x00,0x0C,0x00,0x18,0x00,0x10,0x00,0x18,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,	// 0x7E
	0x00,0x00,0x00,0x0F,0x80,0x0F,0xC0,0x0C,0x60,0x0C,0x30,0x0C,0x30,0x0C,0x60,0x0C,0xC0,0x0C,0x80,0x0F,0x00,0x0F,0x00,0x00,	// 0x7F
	0x00,0x00,0xF0,0x01,0xFC,0x07,0x0E,0xCE,0x07,0xDC,0x03,0xF8,0x03,0xF8,0x03,0x18,0x07,0x1C,0x1E,0x0E,0x1C,0x06,0x00,0x00,	// 0x80
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x0C,0x38,0x0C,0x30,0x00,0x30,0x00,0x30,0x0C,0x30,0x0C,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0x81
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x3B,0x60,0x33,0x68,0x33,0x6C,0x33,0x66,0x33,0x62,0x33,0xC0,0x13,0x80,0x03,0x00,0x00,	// 0x82
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x68,0x33,0x6C,0x33,0x66,0x33,0x66,0x33,0x6C,0x33,0x68,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0x83
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x6C,0x33,0x6C,0x33,0x60,0x33,0x60,0x33,0x6C,0x33,0x6C,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0x84
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x60,0x33,0x62,0x33,0x66,0x33,0x6C,0x33,0x68,0x33,0x60,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0x85
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x60,0x33,0x64,0x33,0x6A,0x33,0x6A,0x33,0x64,0x33,0x60,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0x86
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0xB8,0x60,0xB0,0x60,0xF0,0x60,0xF0,0x60,0x30,0xE0,0x38,0xC0,0x18,0x80,0x08,0x00,0x00,	// 0x87
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE8,0x33,0x6C,0x33,0x66,0x33,0x66,0x33,0x6C,0x33,0x68,0x33,0xC0,0x13,0x80,0x03,0x00,0x00,	// 0x88
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xEC,0x33,0x6C,0x33,0x60,0x33,0x60,0x33,0x6C,0x33,0x6C,0x33,0xC0,0x13,0x80,0x03,0x00,0x00,	// 0x89
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x33,0x62,0x33,0x66,0x33,0x6C,0x33,0x68,0x33,0x60,0x33,0xC0,0x13,0x80,0x03,0x00,0x00,	// 0x8A
	0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x30,0x6C,0x30,0xE0,0x3F,0xEC,0x3F,0x0C,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x8B
	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x30,0x6C,0x30,0xE6,0x3F,0xE6,0x3F,0x0C,0x30,0x08,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x8C
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x62,0x30,0xE6,0x3F,0xEC,0x3F,0x08,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0x8D
	0x00,0x00,0x00,0x38,0x00,0x3E,0x83,0x0F,0xE3,0x0D,0x78,0x0C,0x78,0x0C,0xE3,0x0D,0x83,0x0F,0x00,0x3E,0x00,0x38,0x00,0x00,	// 0x8E
	0x00,0x00,0x00,0x38,0x00,0x3E,0x80,0x0F,0xE2,0x0D,0x75,0x0C,0x75,0x0C,0xE2,0x0D,0x80,0x0F,0x00,0x3E,0x00,0x38,0x00,0x00,	// 0x8F
	0x00,0x00,0xF8,0x3F,0xF8,0x3F,0x98,0x31,0x98,0x31,0x9C,0x31,0x9E,0x31,0x9B,0x31,0x99,0x31,0x18,0x30,0x18,0x30,0x00,0x00,	// 0x90
	0x00,0x00,0x80,0x1C,0xC0,0x3E,0x40,0x22,0x40,0x22,0xC0,0x1F,0x80,0x3F,0x40,0x22,0x40,0x22,0xC0,0x33,0x80,0x11,0x00,0x00,	// 0x91
	0x00,0x00,0x00,0x3C,0x80,0x3F,0xF0,0x07,0x7C,0x06,0x1F,0x06,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0xC3,0x30,0x03,0x30,0x00,0x00,	// 0x92
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE8,0x38,0x6C,0x30,0x66,0x30,0x66,0x30,0x6C,0x30,0xE8,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0x93
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xEC,0x38,0x6C,0x30,0x60,0x30,0x60,0x30,0x6C,0x30,0xEC,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0x94
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x62,0x30,0x66,0x30,0x6C,0x30,0x68,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0x95
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x08,0x38,0x0C,0x30,0x06,0x30,0x06,0x30,0x0C,0x30,0x08,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0x96
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x00,0x38,0x02,0x30,0x06,0x30,0x0C,0x30,0x08,0x30,0x00,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0x97
	0x00,0x00,0x00,0x00,0x60,0x00,0xEC,0x81,0x8C,0xE7,0x00,0x7E,0x00,0x1E,0x8C,0x07,0xEC,0x01,0x60,0x00,0x00,0x00,0x00,0x00,	// 0x98
	0x00,0x00,0xE0,0x0F,0xF0,0x1F,0x3B,0x38,0x1B,0x30,0x18,0x30,0x18,0x30,0x1B,0x30,0x3B,0x38,0xF0,0x1F,0xE0,0x0F,0x00,0x00,	// 0x99
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x0C,0x38,0x0C,0x30,0x00,0x30,0x00,0x30,0x0C,0x30,0x0C,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0x9A
	0x00,0x00,0x80,0x2F,0xC0,0x3F,0xE0,0x18,0x60,0x3C,0x60,0x36,0x60,0x33,0xE0,0x31,0xC0,0x38,0xE0,0x1F,0xA0,0x0F,0x00,0x00,	// 0x9B
	0x00,0x00,0x00,0x00,0x00,0x18,0x80,0x1C,0xF8,0x1F,0xFC,0x0B,0x8C,0x18,0x8C,0x18,0x1C,0x18,0x18,0x18,0x00,0x08,0x00,0x00,	// 0x9C
	0x00,0x00,0xF0,0x2F,0xF8,0x3F,0x1C,0x18,0x0C,0x3E,0x8C,0x37,0xEC,0x31,0x7C,0x30,0x18,0x38,0xFC,0x1F,0xF4,0x0F,0x00,0x00,	// 0x9D
	0x00,0x00,0x00,0x00,0x10,0x04,0x30,0x06,0x60,0x03,0xC0,0x01,0xC0,0x01,0x60,0x03,0x30,0x06,0x10,0x04,0x00,0x00,0x00,0x00,	// 0x9E
	0x00,0x00,0x00,0x00,0x00,0x30,0x80,0x70,0x80,0x60,0xFE,0x7F,0xFF,0x3F,0x83,0x00,0x87,0x00,0x06,0x00,0x00,0x00,0x00,0x00,	// 0x9F
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x60,0x33,0x68,0x33,0x6C,0x33,0x66,0x33,0x62,0x33,0x60,0x33,0xE0,0x3F,0xC0,0x3F,0x00,0x00,	// 0xA0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x68,0x30,0xEC,0x3F,0xE6,0x3F,0x02,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xA1
	0x00,0x00,0x80,0x0F,0xC0,0x1F,0xE0,0x38,0x68,0x30,0x6C,0x30,0x66,0x30,0x62,0x30,0xE0,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0xA2
	0x00,0x00,0xE0,0x0F,0xE0,0x1F,0x00,0x38,0x08,0x30,0x0C,0x30,0x06,0x30,0x02,0x30,0x00,0x18,0xE0,0x3F,0xE0,0x3F,0x00,0x00,	// 0xA3
	0x00,0x00,0x00,0x00,0xE0,0x3F,0xE8,0x3F,0x6C,0x00,0x64,0x00,0x6C,0x00,0x68,0x00,0xEC,0x00,0xC4,0x3F,0x80,0x3F,0x00,0x00,	// 0xA4
	0x00,0x00,0xF8,0x3F,0xF8,0x3F,0x72,0x00,0xE3,0x00,0xC1,0x01,0x83,0x03,0x02,0x07,0x03,0x0E,0xF9,0x3F,0xF8,0x3F,0x00,0x00,	// 0xA5
	0x00,0x00,0x70,0x00,0xFA,0x06,0xDB,0x06,0xDB,0x06,0xDB,0x06,0xDB,0x06,0xDB,0x06,0xDB,0x06,0xFF,0x06,0xFE,0x00,0x00,0x00,	// 0xA6
	0x00,0x00,0x3C,0x00,0x7E,0x06,0xE7,0x06,0xC3,0x06,0xC3,0x06,0xC3,0x06,0xC3,0x06,0xE7,0x06,0x7E,0x06,0x3C,0x00,0x00,0x00,	// 0xA7
	0x00,0x00,0x00,0x0E,0x00,0x1F,0x80,0x3B,0xC0,0x31,0xFB,0x30,0x7B,0x30,0x00,0x30,0x00,0x38,0x00,0x1E,0x00,0x0E,0x00,0x00,	// 0xA8
	0x00,0x00,0xF0,0x07,0xF8,0x0F,0x1C,0x1C,0xEC,0x1B,0xEC,0x1B,0xAC,0x18,0xEC,0x1B,0x4C,0x1B,0x1C,0x1C,0xF8,0x0F,0xF0,0x07,	// 0xA9
	0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0x18,0x00,0xF8,0x03,0xF8,0x03,0x00,0x00,	// 0xAA
	0x00,0x00,0x48,0x00,0x7C,0x04,0x7C,0x06,0x40,0x03,0x80,0x01,0xC0,0x00,0x60,0x19,0x30,0x1D,0x10,0x17,0x00,0x12,0x00,0x00,	// 0xAB
	0x00,0x00,0x48,0x00,0x7C,0x04,0x7C,0x06,0x40,0x03,0x80,0x01,0xC0,0x06,0x60,0x07,0x30,0x04,0x10,0x1F,0x00,0x1F,0x00,0x00,	// 0xAC
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x0F,0xF3,0x3F,0xF3,0x3F,0x80,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xAD
	0x00,0x00,0x80,0x00,0xC0,0x01,0x60,0x03,0x20,0x02,0x00,0x00,0x80,0x00,0xC0,0x01,0x60,0x03,0x20,0x02,0x00,0x00,0x00,0x00,	// 0xAE
	0x00,0x00,0x20,0x02,0x60,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x20,0x02,0x60,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x00,0x00,	// 0xAF
	0x55,0x55,0x00,0x00,0xAA,0xAA,0x00,0x00,0x55,0x55,0x00,0x00,0xAA,0xAA,0x00,0x00,0x55,0x55,0x00,0x00,0xAA,0xAA,0x00,0x00,	// 0xB0
	0xAA,0xAA,0x55,0x55,0xAA,0xAA,0x55,0x55,0xAA,0xAA,0x55,0x55,0xAA,0xAA,0x55,0x55,0xAA,0xAA,0x55,0x55,0xAA,0xAA,0x55,0x55,	// 0xB1
	0xAA,0xAA,0xFF,0xFF,0x55,0x55,0xFF,0xFF,0xAA,0xAA,0xFF,0xFF,0x55,0x55,0xFF,0xFF,0xAA,0xAA,0xFF,0xFF,0x55,0x55,0xFF,0xFF,	// 0xB2
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xB3
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xB4
	0x00,0x00,0x00,0x38,0x00,0x3E,0x80,0x0F,0xE4,0x0D,0x7E,0x0C,0x7B,0x0C,0xE1,0x0D,0x80,0x0F,0x00,0x3E,0x00,0x38,0x00,0x00,	// 0xB5
	0x00,0x00,0x00,0x38,0x00,0x3E,0x84,0x0F,0xE6,0x0D,0x7B,0x0C,0x7B,0x0C,0xE6,0x0D,0x84,0x0F,0x00,0x3E,0x00,0x38,0x00,0x00,	// 0xB6
	0x00,0x00,0x00,0x38,0x00,0x3E,0x80,0x0F,0xE1,0x0D,0x7B,0x0C,0x7E,0x0C,0xE4,0x0D,0x80,0x0F,0x00,0x3E,0x00,0x38,0x00,0x00,	// 0xB7
	0x00,0x00,0xF0,0x07,0xF8,0x0F,0x1C,0x1C,0xCC,0x19,0xEC,0x1B,0x2C,0x1A,0x6C,0x1B,0x4C,0x19,0x1C,0x1C,0xF8,0x0F,0xF0,0x07,	// 0xB8
	0xC0,0x06,0xC0,0x06,0xFF,0xFE,0xFF,0xFE,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xB9
	0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xBA
	0xC0,0x06,0xC0,0x06,0xC0,0xFE,0xC0,0xFE,0xC0,0x00,0xC0,0xFF,0xC0,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xBB
	0xC0,0x06,0xC0,0x06,0xFF,0x06,0xFF,0x06,0x00,0x06,0xFF,0x07,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xBC
	0x00,0x00,0x00,0x00,0xE0,0x03,0xF0,0x07,0x38,0x0E,0xFE,0x3F,0xFE,0x3F,0x18,0x0C,0x38,0x0E,0x30,0x06,0x00,0x00,0x00,0x00,	// 0xBD
	0x00,0x00,0x03,0x00,0x0F,0x0A,0x3C,0x0A,0xF0,0x0A,0xC0,0x3F,0xC0,0x3F,0xF0,0x0A,0x3C,0x0A,0x0F,0x0A,0x03,0x00,0x00,0x00,	// 0xBE
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xFF,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xBF
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x01,0xFF,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC0
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xFF,0x01,0xFF,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC1
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0xFF,0x80,0xFF,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC2
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC3
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC4
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xC5
	0x00,0x00,0x00,0x1C,0x40,0x3E,0x68,0x33,0x6C,0x33,0x64,0x33,0x6C,0x33,0x68,0x33,0x6C,0x33,0xE4,0x3F,0xC0,0x3F,0x00,0x00,	// 0xC6
	0x00,0x00,0x00,0x38,0x00,0x3E,0x82,0x0F,0xE3,0x0D,0x79,0x0C,0x7B,0x0C,0xE2,0x0D,0x83,0x0F,0x01,0x3E,0x00,0x38,0x00,0x00,	// 0xC7
	0x00,0x00,0x00,0x00,0xFF,0x07,0xFF,0x07,0x00,0x06,0xFF,0x06,0xFF,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xC8
	0x00,0x00,0x00,0x00,0xC0,0xFF,0xC0,0xFF,0xC0,0x00,0xC0,0xFE,0xC0,0xFE,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xC9
	0xC0,0x06,0xC0,0x06,0xFF,0x06,0xFF,0x06,0x00,0x06,0xFF,0x06,0xFF,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xCA
	0xC0,0x06,0xC0,0x06,0xC0,0xFE,0xC0,0xFE,0xC0,0x00,0xC0,0xFE,0xC0,0xFE,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xCB
	0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFE,0xFF,0xFE,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xCC
	0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xCD
	0xC0,0x06,0xC0,0x06,0xFF,0xFE,0xFF,0xFE,0x00,0x00,0xFF,0xFE,0xFF,0xFE,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,	// 0xCE
	0x00,0x00,0xF6,0x1B,0xFE,0x1F,0x18,0x06,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x18,0x06,0xFE,0x1F,0xF6,0x1B,0x00,0x00,	// 0xCF
	0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x1C,0xFC,0x3E,0xCC,0x33,0x8C,0x33,0x0C,0x3F,0x18,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD0
	0x00,0x00,0xC0,0x00,0xFF,0x3F,0xFF,0x3F,0xC3,0x30,0x03,0x30,0x03,0x30,0x07,0x38,0x0E,0x1C,0xFC,0x0F,0xF0,0x03,0x00,0x00,	// 0xD1
	0x00,0x00,0xF8,0x3F,0xF8,0x3F,0x9C,0x31,0x9E,0x31,0x9B,0x31,0x9B,0x31,0x9E,0x31,0x9C,0x31,0x18,0x30,0x18,0x30,0x00,0x00,	// 0xD2
	0x00,0x00,0xF8,0x3F,0xF8,0x3F,0x9B,0x31,0x9B,0x31,0x98,0x31,0x98,0x31,0x9B,0x31,0x9B,0x31,0x18,0x30,0x18,0x30,0x00,0x00,	// 0xD3
	0x00,0x00,0xF8,0x3F,0xF8,0x3F,0x99,0x31,0x9B,0x31,0x9E,0x31,0x9C,0x31,0x98,0x31,0x98,0x31,0x18,0x30,0x18,0x30,0x00,0x00,	// 0xD4
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD5
	0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x30,0x18,0x30,0xFC,0x3F,0xFE,0x3F,0x1B,0x30,0x19,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD6
	0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x30,0x1E,0x30,0xFB,0x3F,0xFB,0x3F,0x1E,0x30,0x1C,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD7
	0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x30,0x1B,0x30,0xF8,0x3F,0xF8,0x3F,0x1B,0x30,0x1B,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD8
	0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xFF,0x01,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xD9
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x80,0xFF,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,	// 0xDA
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	// 0xDB
	0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,	// 0xDC
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x3F,0xBF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xDD
	0x00,0x00,0x00,0x00,0x00,0x00,0x19,0x30,0x1B,0x30,0xFE,0x3F,0xFC,0x3F,0x18,0x30,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xDE
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,	// 0xDF
	0x00,0x00,0xE0,0x0F,0xF0,0x1F,0x38,0x38,0x18,0x30,0x1C,0x30,0x1E,0x30,0x1B,0x30,0x39,0x38,0xF0,0x1F,0xE0,0x0F,0x00,0x00,	// 0xE0
	0x00,0x00,0x00,0x00,0xC0,0xFF,0xE0,0xFF,0x30,0x21,0x10,0x21,0x10,0x21,0x30,0x33,0xE0,0x3F,0xC0,0x1E,0x00,0x00,0x00,0x00,	// 0xE1
	0x00,0x00,0xE0,0x0F,0xF0,0x1F,0x3C,0x38,0x1E,0x30,0x1B,0x30,0x1B,0x30,0x1E,0x30,0x3C,0x38,0xF0,0x1F,0xE0,0x0F,0x00,0x00,	// 0xE2
	0x00,0x00,0xE0,0x0F,0xF0,0x1F,0x39,0x38,0x1B,0x30,0x1E,0x30,0x1C,0x30,0x18,0x30,0x38,0x38,0xF0,0x1F,0xE0,0x0F,0x00,0x00,	// 0xE3
	0x00,0x00,0x80,0x0F,0xC8,0x1F,0xEC,0x38,0x64,0x30,0x6C,0x30,0x68,0x30,0x6C,0x30,0xE4,0x38,0xC0,0x1F,0x80,0x0F,0x00,0x00,	// 0xE4
	0x00,0x00,0xE0,0x0F,0xF0,0x1F,0x3A,0x38,0x1B,0x30,0x19,0x30,0x1B,0x30,0x1A,0x30,0x3B,0x38,0xF1,0x1F,0xE0,0x0F,0x00,0x00,	// 0xE5
	0x00,0x00,0xF0,0xFF,0xF0,0xFF,0x00,0x0E,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x06,0xF0,0x0F,0xF0,0x0F,0x00,0x00,0x00,0x00,	// 0xE6
	0x00,0x00,0x00,0x00,0x0C,0x30,0xFC,0x3F,0xFC,0x3F,0x6C,0x36,0x60,0x06,0x60,0x06,0xE0,0x07,0xC0,0x03,0x00,0x00,0x00,0x00,	// 0xE7
	0x00,0x00,0x00,0x00,0x03,0x30,0xFF,0x3F,0xFF,0x3F,0x1B,0x36,0x18,0x06,0x18,0x06,0xF8,0x07,0xF0,0x03,0x00,0x00,0x00,0x00,	// 0xE8
	0x00,0x00,0xF8,0x07,0xF8,0x1F,0x00,0x38,0x00,0x30,0x04,0x30,0x06,0x30,0x03,0x30,0x01,0x38,0xF8,0x1F,0xF8,0x07,0x00,0x00,	// 0xE9
	0x00,0x00,0xF8,0x07,0xF8,0x1F,0x04,0x38,0x06,0x30,0x03,0x30,0x03,0x30,0x06,0x30,0x04,0x38,0xF8,0x1F,0xF8,0x07,0x00,0x00,	// 0xEA
	0x00,0x00,0xF8,0x07,0xF8,0x1F,0x01,0x38,0x03,0x30,0x06,0x30,0x04,0x30,0x00,0x30,0x00,0x38,0xF8,0x1F,0xF8,0x07,0x00,0x00,	// 0xEB
	0x00,0x00,0x00,0x00,0x60,0x00,0xE0,0x81,0x80,0xE7,0x10,0x7E,0x18,0x1E,0x8C,0x07,0xE4,0x01,0x60,0x00,0x00,0x00,0x00,0x00,	// 0xEC
	0x00,0x00,0x08,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xC4,0x3F,0xC6,0x3F,0x63,0x00,0x31,0x00,0x18,0x00,0x08,0x00,0x00,0x00,	// 0xED
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xEE
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xEF
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xF0
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x18,0xC0,0x18,0xF0,0x1B,0xF0,0x1B,0xC0,0x18,0xC0,0x18,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xF1
	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xF2
	0x00,0x00,0x44,0x00,0x54,0x04,0x7C,0x06,0x28,0x03,0x80,0x01,0xC0,0x06,0x60,0x07,0x30,0x04,0x10,0x1F,0x00,0x1F,0x00,0x00,	// 0xF3
	0x00,0x00,0x38,0x00,0x7C,0x00,0xC6,0x00,0x82,0x00,0xFE,0x3F,0xFE,0x3F,0x02,0x00,0xFE,0x3F,0xFE,0x3F,0x02,0x00,0x00,0x00,	// 0xF4
	0x00,0x00,0x00,0x00,0xDC,0x08,0xFE,0x19,0x22,0x11,0x22,0x11,0x22,0x11,0x22,0x11,0xE6,0x1F,0xC4,0x0E,0x00,0x00,0x00,0x00,	// 0xF5
	0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x80,0x01,0xB0,0x0D,0xB0,0x0D,0x80,0x01,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00,	// 0xF6
	0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x80,0x00,0x80,0x00,0xC0,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xF7
	0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x00,0x3F,0x00,0x33,0x00,0x33,0x00,0x3F,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xF8
	0x00,0x00,0x00,0x00,0x80,0x01,0xC0,0x03,0x80,0x01,0x00,0x00,0x00,0x00,0x80,0x01,0xC0,0x03,0x80,0x01,0x00,0x00,0x00,0x00,	// 0xF9
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0xC0,0x03,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xFA
	0x00,0x00,0x00,0x00,0x02,0x00,0x1F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xFB
	0x00,0x00,0x00,0x00,0x11,0x00,0x15,0x00,0x15,0x00,0x1F,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xFC
	0x00,0x00,0x00,0x00,0x19,0x00,0x1D,0x00,0x15,0x00,0x17,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xFD
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x03,0xF0,0x03,0xF0,0x03,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// 0xFE
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 	// 0xFF
	*/
};

static PGM_P _font12x16selector(unsigned char c)
{
	return (PGM_P) _font12x16map + (c - 0x20) * BYTESPERCHAR;
}

fontdescriptor_t font12x16 PROGMEM = { 12, 16, _font12x16selector };

