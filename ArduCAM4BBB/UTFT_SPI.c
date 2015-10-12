/*
 ============================================================================
 Name        : UTFT_SPI.c
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 ============================================================================
 */


#include "UTFT_SPI.h"
#include "BBBCAM.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>



void UTFT()
{
	model = SSD1289;
	disp_x_size=239;
	disp_y_size=319;
	display_transfer_mode=8;

	display_model=model;
}



void LCD_Write_COM_DATA(char com1,int dat1)
{
     LCD_Write_COM(com1);
     LCD_Write_DATA(dat1>>8,dat1);
}

void LCD_Write_COM(char VL)
{
	bus_write(0xBE, VL);
}

void LCD_Write_DATA(char VH,char VL)
{
	bus_write(0xBF, VH);
  	bus_write(0xBF, VL);
}

void LCD_Writ_Bus(char VH,char VL, uint8_t mode)
{
	LCD_Write_DATA(VH,VL);
}

void InitLCD()
{
	//orient=orientation;
	orient=LANDSCAPE;

	LCD_Write_COM_DATA(0x00,0x0001);
	LCD_Write_COM_DATA(0x03,0xA8A4);
	LCD_Write_COM_DATA(0x0C,0x0000);
	LCD_Write_COM_DATA(0x0D,0x080C);
	LCD_Write_COM_DATA(0x0E,0x2B00);
	LCD_Write_COM_DATA(0x1E,0x00B7);
	LCD_Write_COM_DATA(0x01,0x693F);//693f
	LCD_Write_COM_DATA(0x02,0x0600);
	LCD_Write_COM_DATA(0x10,0x0000);
	LCD_Write_COM_DATA(0x11,0x6078);//6078
	LCD_Write_COM_DATA(0x05,0x0000);
	LCD_Write_COM_DATA(0x06,0x0000);
	LCD_Write_COM_DATA(0x16,0xEF1C);
	LCD_Write_COM_DATA(0x17,0x0003);
	LCD_Write_COM_DATA(0x07,0x0233);
	LCD_Write_COM_DATA(0x0B,0x0000);
	LCD_Write_COM_DATA(0x0F,0x0000);
	LCD_Write_COM_DATA(0x41,0x0000);
	LCD_Write_COM_DATA(0x42,0x0000);
	LCD_Write_COM_DATA(0x48,0x0000);
	LCD_Write_COM_DATA(0x49,0x013F);
	LCD_Write_COM_DATA(0x4A,0x0000);
	LCD_Write_COM_DATA(0x4B,0x0000);
	LCD_Write_COM_DATA(0x44,0xEF00);
	LCD_Write_COM_DATA(0x45,0x0000);
	LCD_Write_COM_DATA(0x46,0x013F);
	LCD_Write_COM_DATA(0x30,0x0707);
	LCD_Write_COM_DATA(0x31,0x0204);
	LCD_Write_COM_DATA(0x32,0x0204);
	LCD_Write_COM_DATA(0x33,0x0502);
	LCD_Write_COM_DATA(0x34,0x0507);
	LCD_Write_COM_DATA(0x35,0x0204);
	LCD_Write_COM_DATA(0x36,0x0204);
	LCD_Write_COM_DATA(0x37,0x0502);
	LCD_Write_COM_DATA(0x3A,0x0302);
	LCD_Write_COM_DATA(0x3B,0x0302);
	LCD_Write_COM_DATA(0x23,0x0000);
	LCD_Write_COM_DATA(0x24,0x0000);
	LCD_Write_COM_DATA(0x25,0x8000);
	LCD_Write_COM_DATA(0x4f,0x0000);
	LCD_Write_COM_DATA(0x4e,0x0000);
	LCD_Write_COM(0x22);

	//setColor(255, 255, 255);
	//setBackColor(0, 0, 0);
	cfont.font=0;
	clrScr();
}

void setXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{

	if (orient==LANDSCAPE)
	{
		swap(unsigned int, x1, y1);
		swap(unsigned int, x2, y2)
		y1=disp_y_size-y1;
		y2=disp_y_size-y2;
		swap(unsigned int, y1, y2)
	}


	LCD_Write_COM_DATA(0x44,(x2<<8)+x1);
	LCD_Write_COM_DATA(0x45,y1);
	LCD_Write_COM_DATA(0x46,y2);
	LCD_Write_COM_DATA(0x4e,x1);
	LCD_Write_COM_DATA(0x4f,y1);
	LCD_Write_COM(0x22);
}

void clrXY()
{
	if (orient==PORTRAIT)
		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}

void resetXY()
{
	clrXY();
}

void clrScr()
{
	long i;

	clrXY();

	for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
	{
		if (display_transfer_mode!=1)
			LCD_Writ_Bus(0x00,0x00,display_transfer_mode);
		else
		{
			LCD_Writ_Bus(1,0,display_transfer_mode);
			LCD_Writ_Bus(1,0,display_transfer_mode);
			//LCD_Writ_Bus(00,0x55,display_transfer_mode);
		}
	}

}
/*
void setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}
*/
void LCD_Disp_Filp()
{
	LCD_Write_COM_DATA(0x11,0x6068);//6078
	LCD_Write_COM(0x22);
}

void LCD_Disp_Normal()
{
	LCD_Write_COM_DATA(0x11,0x6078);//6078
	LCD_Write_COM(0x22);
}

void fillScr(uint8_t r, uint8_t g, uint8_t b)
{
	long i;
	char ch, cl;

	ch=((r&248)|g>>5);
	cl=((g&28)<<3|b>>3);

	clrXY();


	for (i=0; i<((disp_x_size+1)*(disp_y_size+1)); i++)
	{
		if (display_transfer_mode!=1)
			LCD_Writ_Bus(ch,cl,display_transfer_mode);
		else
		{
			LCD_Writ_Bus(1,ch,display_transfer_mode);
			LCD_Writ_Bus(1,cl,display_transfer_mode);
		}
	}
}

void setColor(uint8_t r, uint8_t g, uint8_t b)
{
	fcolorr=r;
	fcolorg=g;
	fcolorb=b;
}

void setBackColor(uint8_t r, uint8_t g, uint8_t b)
{
	bcolorr=r;
	bcolorg=g;
	bcolorb=b;
}

void setPixel(uint8_t r,uint8_t g,uint8_t b)
{
	LCD_Write_DATA(((r&248)|g>>5),((g&28)<<3|b>>3));	// rrrrrggggggbbbbb
}

void drawPixel(int x, int y)
{
	setXY(x, y, x, y);
	setPixel(fcolorr, fcolorg, fcolorb);
	clrXY();
}

void dispBitmap(FILE *fp)
{
	char VH,VL;
	int i,j = 0;
	for(i = 0 ;i < BMPIMAGEOFFSET; i++)
		fgetc(fp);
  	for(i = 0; i < 320; i++)
  	for(j = 0; j < 240; j++)
  	{
	    VL = fgetc(fp);
	    //Serial.write(VL);
	    VH = fgetc(fp);
    	//Serial.write(VH);
	    LCD_Write_DATA(VH,VL);
  	}
  	clrXY();
}
