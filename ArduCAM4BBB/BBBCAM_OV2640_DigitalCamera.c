/*
 ============================================================================
 Name        : BBBCAM_OV2640_DigitalCamera.c
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "UTFT_SPI.h"
#include "BBBCAM.h"

#define BOOL int
#define TRUE 1
#define FALSE 0


#define OV2640_CHIPID_HIGH 	0x0A
#define OV2640_CHIPID_LOW 	0x0B

void setup()
{
  uint8_t vid,pid;
  uint8_t temp;

  UTFT();
  ArduCAM(OV2640);
  printf("ArduCAM Start!\n");

  //Check if the ArduCAM SPI bus is OK
  write_reg(ARDUCHIP_TEST1, 0x55);
  temp = read_reg(ARDUCHIP_TEST1);
  if(temp != 0x55)
  {
  	printf("SPI interface Error!\n");
  	while(1);
  }

  //Change MCU mode
  write_reg(ARDUCHIP_MODE, 0x00);

  InitLCD();

  //Check if the camera module type is OV2640
  rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
  //printf("vid is : %x",vid);
  rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
  //printf("   pid is : %x\n",pid);
  if((vid != 0x26) || (pid != 0x42))
  	printf("Can't find OV2640 module!\n");
  else
  	printf("OV2640 detected\n");

  //Change to BMP capture mode and initialize the OV2640 module
  set_format(BMP);

  InitCAM();
}

int main(void)
{
	int nmemb = 1;
	BOOL isShowFlag = TRUE;
	setup();

	while(1)
	{
		uint8_t buf[256];
		static int i = 0;
		static int k = 0;
		static int n = 0;
		uint8_t temp,temp_last;
		uint8_t start_capture = 0;

		//Wait trigger from shutter buttom
		if(read_reg(ARDUCHIP_TRIG) & SHUTTER_MASK)
		{
			isShowFlag = FALSE;
			write_reg(ARDUCHIP_MODE, 0x00);
			set_format(JPEG);
			InitCAM();

			OV2640_set_JPEG_size(OV2640_640x480);
			//OV2640_set_JPEG_size(OV2640_1600x1200);
			//Wait until buttom released
			while(read_reg(ARDUCHIP_TRIG) & SHUTTER_MASK);
			sleep(1);
			start_capture = 1;
		}
		else
		{
			if(isShowFlag )
			{
				temp = read_reg(ARDUCHIP_TRIG);

				if(!(temp & VSYNC_MASK))				 			//New Frame is coming
				{
					write_reg(ARDUCHIP_MODE, 0x00);    		//Switch to MCU
					resetXY();
					write_reg(ARDUCHIP_MODE, 0x01);    		//Switch to CAM
					while(!(read_reg(ARDUCHIP_TRIG)&0x01)); 	//Wait for VSYNC is gone
				}
			}
		}
		if(start_capture)
		{
			//Flush the FIFO
			flush_fifo();
			//Clear the capture done flag
			clear_fifo_flag();
			//Start capture
			capture();
			printf("Start Capture\n");
		}

		if(read_reg(ARDUCHIP_TRIG) & CAP_DONE_MASK)
		{

			printf("Capture Done!\n");

			//Construct a file name
			memset(filePath,0,20);
			strcat(filePath,"/home/");
			getnowtime();
			strcat(filePath,nowtime);
			strcat(filePath,".jpg");
			//Open the new file
			fp = fopen(filePath,"w+");
			if (fp == NULL)
			{
				printf("open file failed");
				return 0;

			}
			i = 0;
			temp = read_fifo();
			//Write first image data to buffer
			buf[i++] = temp;

			//Read JPEG data from FIFO
			while( (temp != 0xD9) | (temp_last != 0xFF) )
			{
				temp_last = temp;
				temp = read_fifo();
				//Write image data to buffer if not full
				if(i < 256)
					buf[i++] = temp;
				else
				{
					//Write 256 uint8_ts image data to file
					fwrite(buf,256,nmemb,fp);
					i = 0;
					buf[i++] = temp;
				}
			}
			//Write the remain uint8_ts in the buffer
			if(i > 0)
				fwrite(buf,i,nmemb,fp);

			//Close the file
			fclose(fp);

			//Clear the capture done flag
			clear_fifo_flag();
			//Clear the start capture flag
			start_capture = 0;

			set_format(BMP);
			InitCAM();
			isShowFlag = TRUE;
		}
	}
}
