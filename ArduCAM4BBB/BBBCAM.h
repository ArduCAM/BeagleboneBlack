 /*
 ============================================================================
 Name        : BBBCAM.h
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 
  Beaglebon Black library support for CMOS Image Sensor
  Copyright (C)2011-2015 ArduCAM.com. All right reserved

  Basic functionality of this library are based on the demo-code provided by
  ArduCAM.com. You can find the latest version of the library at
  http://www.ArduCAM.com

  Now supported controllers:
		-	OV7670
		-	MT9D111
		-	OV7675
		-	OV2640
		-	OV3640
		-	OV5642
		-	OV7660
		-	OV7725

	We will add support for many other sensors in next release.

  Supported MCU platform
 		-	Theoretically support all Arduino families
  	-	Arduino UNO R3				(Tested)
  	-	Arduino MEGA2560 R3		(Tested)
  	-	Arduino Leonardo R3		(Tested)
  	-	Arduino Nano					(Tested)
  	-	Arduino DUE						(Tested)
  	-	Arduino Yun						(Tested)  		
  	-	Beaglebon Black				(Tested)
  	-	Raspberry Pi					(Tested)
  	- ESP8266-12 						(Tested)


  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.ArduCAM.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*------------------------------------
	Revision History:
	2015/01/16  V1.0  by Lee  Inital library for Beaglebone Black.
	2015/10/12 	V1.1	by Lee	Optimization	
--------------------------------------*/

#ifndef SRC_PICAM_H_
#define SRC_PICAM_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define regtype volatile uint8_t
#define regsize uint8_t

#define fontuint8_t(x) cfont.font[x]

#define PROGMEM

#define pgm_read_byte(x)        (*((char *)x))
#define pgm_read_word(x)        ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
#define pgm_read_byte_near(x)   (*((char *)x))
#define pgm_read_byte_far(x)    (*((char *)x))
#define pgm_read_word_near(x)   ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
#define pgm_read_word_far(x)    ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x))))

#define PSTR(x)  x
#if defined F
  #undef F
#endif
#define F(X) (X)

/****************************************************/
/* Sensor related definition 												*/
/****************************************************/
#define BMP 	0
#define JPEG	1

#define OV7670	0
#define MT9D111	1
#define OV7675	2
#define OV5642	3
#define OV3640  4
#define OV2640  5
#define OV9655	6
#define MT9M112	7
#define OV7725	8
#define OV7660	9

#define OV2640_160x120 		0	//160x120
#define OV2640_176x144 		1	//176x144
#define OV2640_320x240 		2	//320x240
#define OV2640_352x288 		3	//352x288
#define OV2640_640x480		4	//640x480
#define OV2640_800x600 		5	//800x600
#define OV2640_1024x768		6	//1024x768
#define OV2640_1280x1024	7	//1280x1024
#define OV2640_1600x1200	8	//1600x1200

/****************************************************/
/* I2C Control Definition 													*/
/****************************************************/
#define I2C_ADDR_8BIT 0
#define I2C_ADDR_16BIT 1
#define I2C_REG_8BIT 0
#define I2C_REG_16BIT 1
#define I2C_DAT_8BIT 0
#define I2C_DAT_16BIT 1

/* Register initialization tables for SENSORs */
/* Terminating list entry for reg */
#define SENSOR_REG_TERM_8BIT                0xFF
#define SENSOR_REG_TERM_16BIT               0xFFFF
/* Terminating list entry for val */
#define SENSOR_VAL_TERM_8BIT                0xFF
#define SENSOR_VAL_TERM_16BIT               0xFFFF

/****************************************************/
/* ArduChip related definition 											*/
/****************************************************/
#define ARDUCHIP_TEST1       	0x00  //TEST register
#define ARDUCHIP_TEST2      	0x01  //TEST register

#define ARDUCHIP_MODE      		0x02  //Mode register
#define MCU2LCD_MODE       		0x00
#define CAM2LCD_MODE       		0x01
#define LCD2MCU_MODE       		0x02

#define ARDUCHIP_TIM       		0x03  //Timming control
#define HREF_LEVEL_MASK    		0x01  //0 = High active , 		1 = Low active
#define VSYNC_LEVEL_MASK   		0x02  //0 = High active , 		1 = Low active
#define LCD_BKEN_MASK      		0x04  //0 = Enable, 			1 = Disable
#define DELAY_MASK         		0x08  //0 = no delay, 			1 = delay one clock
#define MODE_MASK          		0x10  //0 = LCD mode, 			1 = FIFO mode
#define FIFO_PWRDN_MASK	   		0x20  //0 = Normal operation, 	1 = FIFO power down

#define ARDUCHIP_FIFO      		0x04  //FIFO and I2C control
#define FIFO_CLEAR_MASK    		0x01
#define FIFO_START_MASK    		0x02
#define FIFO_RDPTR_RST_MASK     0x10
#define FIFO_WRPTR_RST_MASK     0x20


#define ARDUCHIP_REV       		0x40  //ArduCHIP revision
#define VER_LOW_MASK       		0x3F
#define VER_HIGH_MASK      		0xC0

#define ARDUCHIP_TRIG      		0x41  //Trigger source
#define VSYNC_MASK         		0x01
#define SHUTTER_MASK       		0x02
#define CAP_DONE_MASK      		0x08

/****************************************************/


/****************************************************************/
/* define a structure for sensor register initialization values */
/****************************************************************/
struct sensor_reg {
	uint16_t reg;
	uint16_t val;
};

struct CAM{
	uint8_t m_fmt;
	uint8_t sensor_model;
	uint8_t sensor_addr;
};
//Camera Handle
struct CAM myCAM;

//File Handle
FILE * fp;
char filePath[20];
char nowtime[20];

//I2C handle
int i2c1;
static char *i2cdev1 = "/dev/i2c-1";

//SPI handle
int spi0;
static const char *spidev0 = "/dev/spidev1.0"; 
static uint8_t mode=0;
static uint8_t bits = 8;
static uint16_t delay;
static uint32_t speed = 1000000;

int ArduCAM(uint8_t model);
void InitCAM();

void flush_fifo(void);
void capture(void);
void clear_fifo_flag(void);
uint8_t read_fifo(void);

uint8_t read_reg(uint8_t addr);
void write_reg(uint8_t addr, uint8_t data);

void bus_write(uint8_t address, uint8_t value);
uint8_t bus_read(uint8_t address);

int wrSensorRegs8_8(const struct sensor_reg*);
int wrSensorRegs8_16(const struct sensor_reg*);
int wrSensorRegs8_16(const struct sensor_reg reglist[]);

uint8_t wrSensorReg8_8(uint8_t regID, uint8_t regDat);
uint8_t wrSensorReg8_16(uint8_t regID, uint16_t regDat);
uint8_t wrSensorReg16_8(uint16_t regID, uint8_t regDat);

uint8_t rdSensorReg8_8(uint8_t regID, uint8_t* regDat);
uint8_t rdSensorReg8_16(uint8_t regID, uint16_t* regDat);
uint8_t rdSensorReg16_8(uint16_t regID, uint8_t* regDat);

void OV2640_set_JPEG_size(uint8_t size);
void set_format(uint8_t fmt);

void delayms(int i);


#endif /* SRC_PICAM_H_ */
