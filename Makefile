all : OV2640_Playback	OV3640_Playback	OV5642_Playback	OV7670_Playback OV2640_DigitalCamera	OV5642_DigitalCamera

objects = DefaultFonts_SPI.o UTFT_SPI.o PiCAM.o

OV2640_Playback : $(objects) PiCAM_OV2640_Playback.o 
	gcc -o OV2640_Playback $(objects) PiCAM_OV2640_Playback.o
OV3640_Playback : $(objects) PiCAM_OV3640_Playback.o 
	gcc -o OV3640_Playback $(objects) PiCAM_OV3640_Playback.o
OV5642_Playback : $(objects) PiCAM_OV5642_Playback.o 
	gcc -o OV5642_Playback $(objects) PiCAM_OV5642_Playback.o
OV7670_Playback : $(objects) PiCAM_OV7670_Playback.o 
	gcc -o OV7670_Playback $(objects) PiCAM_OV7670_Playback.o
	
OV2640_DigitalCamera : DefaultFonts_SPI.o UTFT_SPI.o PiCAM.o PiCAM_OV2640_DigitalCamera.o 
	gcc -o OV2640_DigitalCamera DefaultFonts_SPI.o UTFT_SPI.o PiCAM.o PiCAM_OV2640_DigitalCamera.o
OV5642_DigitalCamera : DefaultFonts_SPI.o UTFT_SPI.o PiCAM.o PiCAM_OV5642_DigitalCamera.o 
	gcc -o OV5642_DigitalCamera DefaultFonts_SPI.o UTFT_SPI.o PiCAM.o PiCAM_OV5642_DigitalCamera.o

DefaultFonts_SPI.o : DefaultFonts_SPI.c
	gcc -c DefaultFonts_SPI.c
UTFT_SPI.o : UTFT_SPI.c
	gcc -c UTFT_SPI.c
PiCAM.o : PiCAM.c
	gcc -c PiCAM.c 
PiCAM_OV2640_Playback.o : PiCAM_OV2640_Playback.c
	gcc -c PiCAM_OV2640_Playback.c
PiCAM_OV3640_Playback.o : PiCAM_OV3640_Playback.c
	gcc -c PiCAM_OV3640_Playback.c
PiCAM_OV5642_Playback.o : PiCAM_OV5642_Playback.c
	gcc -c PiCAM_OV5642_Playback.c
PiCAM_OV7670_Playback.o : PiCAM_OV7670_Playback.c
	gcc -c PiCAM_OV7670_Playback.c
	
PiCAM_OV2640_DigitalCamera.o : PiCAM_OV2640_DigitalCamera.c
	gcc -c PiCAM_OV2640_DigitalCamera.c
PiCAM_OV5642_DigitalCamera.o : PiCAM_OV5642_DigitalCamera.c
	gcc -c PiCAM_OV5642_DigitalCamera.c
	
clean : 
	rm OV2640_Playback OV3640_Playback OV5642_Playback OV7670_Playback OV2640_DigitalCamera OV5642_DigitalCamera $(objects) /
	PiCAM_OV2640_Playback.o PiCAM_OV3640_Playback.o PiCAM_OV5642_Playback.o PiCAM_OV7670_Playback.o /
	PiCAM_OV2640_DigitalCamera.o PiCAM_OV5642_DigitalCamera.o