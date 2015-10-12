/*
 ============================================================================
 Name        : UTFT_SPI.h
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 ============================================================================
 */ 

#ifndef SRC_UTFT_SPI_H_
#define SRC_UTFT_SPI_H_

#include <stdint.h>
#include <stdio.h>

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A			0
#define ILI9327			1
#define SSD1289			2
#define ILI9325C		3
#define ILI9325D_8		4
#define ILI9325D_16		5
#define HX8340B_8		6
#define HX8340B_S		7
#define HX8352A			8
#define ST7735			9
#define PCF8833			10
#define S1D19122		11
#define SSD1963_480		12
#define SSD1963_800		13
#define S6D1121_8		14
#define S6D1121_16		15

#define ITDB32			0	// HX8347-A (16bit)
#define ITDB32WC		1	// ILI9327  (16bit)
#define TFT01_32W		1	// ILI9327	(16bit)
#define ITDB32S			2	// SSD1289  (16bit)
#define TFT01_32		2	// SSD1289  (16bit)
#define ITDB24			3	// ILI9325C (8bit)
#define ITDB24D			4	// ILI9325D (8bit)
#define ITDB24DWOT		4	// ILI9325D (8bit)
#define ITDB28			4	// ILI9325D (8bit)
#define TFT01_24_8		4	// ILI9325D (8bit)
#define TFT01_24_16		5	// ILI9325D (16bit)
#define ITDB22			6	// HX8340-B (8bit)
#define ITDB22SP		7	// HX8340-B (Serial)
#define ITDB32WD		8	// HX8352-A (16bit)
#define TFT01_32WD		8	// HX8352A	(16bit)
#define ITDB18SP		9	// ST7735   (Serial)
#define LPH9135			10	// PCF8833	(Serial)
#define ITDB25H			11	// S1D19122	(16bit)
#define ITDB43			12	// SSD1963	(16bit) 480x272
#define ITDB50			13	// SSD1963	(16bit) 800x480
#define ITDB24E_8		14	// S6D1121	(8bit)
#define ITDB24E_16		15	// S6D1121	(16bit)

#define SERIAL_4PIN		4
#define SERIAL_5PIN		5

#define BMPIMAGEOFFSET 66

#define swap(type, i, j) {type t = i; i = j; j = t;}

struct _current_font
{
	uint8_t* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

long disp_x_size, disp_y_size;
struct _current_font	cfont;
uint8_t display_model, display_transfer_mode,model;
uint8_t orient;
uint8_t fcolorr,fcolorg,fcolorb;
uint8_t bcolorr,bcolorg,bcolorb;

void UTFT();

void LCD_Writ_Bus(char VH,char VL, uint8_t mode);
void LCD_Write_DATA(char VH,char VL);
void LCD_Write_COM(char VL);
void LCD_Write_COM_DATA(char com1,int dat1);

void InitLCD();
void clrScr();

//void setFont(uint8_t* font);
void resetXY();
void setXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void clrXY();

void LCD_Disp_Filp();
void LCD_Disp_Normal();

void drawPixel(int x, int y);
void dispBitmap(FILE *fp);

void fillScr(uint8_t r, uint8_t g, uint8_t b);

void setColor(uint8_t r, uint8_t g, uint8_t b);
void setBackColor(uint8_t r, uint8_t g, uint8_t b);

#endif /* SRC_UTFT_SPI_H_ */
