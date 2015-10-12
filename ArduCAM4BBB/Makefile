all : OV2640_Playback	OV3640_Playback	OV5642_Playback	OV7670_Playback OV2640_DigitalCamera	OV5642_DigitalCamera

objects = DefaultFonts_SPI.o UTFT_SPI.o BBBCAM.o

OV2640_Playback : $(objects) BBBCAM_OV2640_Playback.o 
	gcc -o OV2640_Playback $(objects) BBBCAM_OV2640_Playback.o
OV3640_Playback : $(objects) BBBCAM_OV3640_Playback.o 
	gcc -o OV3640_Playback $(objects) BBBCAM_OV3640_Playback.o
OV5642_Playback : $(objects) BBBCAM_OV5642_Playback.o 
	gcc -o OV5642_Playback $(objects) BBBCAM_OV5642_Playback.o
OV7670_Playback : $(objects) BBBCAM_OV7670_Playback.o 
	gcc -o OV7670_Playback $(objects) BBBCAM_OV7670_Playback.o
	
OV2640_DigitalCamera : $(objects) BBBCAM_OV2640_DigitalCamera.o 
	gcc -o OV2640_DigitalCamera $(objects) BBBCAM_OV2640_DigitalCamera.o
OV5642_DigitalCamera : $(objects) BBBCAM_OV5642_DigitalCamera.o 
	gcc -o OV5642_DigitalCamera $(objects) BBBCAM_OV5642_DigitalCamera.o

DefaultFonts_SPI.o : DefaultFonts_SPI.c
	gcc -c DefaultFonts_SPI.c
UTFT_SPI.o : UTFT_SPI.c
	gcc -c UTFT_SPI.c
BBBCAM.o : BBBCAM.c
	gcc -c BBBCAM.c 
BBBCAM_OV2640_Playback.o : BBBCAM_OV2640_Playback.c
	gcc -c BBBCAM_OV2640_Playback.c
BBBCAM_OV3640_Playback.o : BBBCAM_OV3640_Playback.c
	gcc -c BBBCAM_OV3640_Playback.c
BBBCAM_OV5642_Playback.o : BBBCAM_OV5642_Playback.c
	gcc -c BBBCAM_OV5642_Playback.c
BBBCAM_OV7670_Playback.o : BBBCAM_OV7670_Playback.c
	gcc -c BBBCAM_OV7670_Playback.c
	
BBBCAM_OV2640_DigitalCamera.o : BBBCAM_OV2640_DigitalCamera.c
	gcc -c BBBCAM_OV2640_DigitalCamera.c
BBBCAM_OV5642_DigitalCamera.o : BBBCAM_OV5642_DigitalCamera.c
	gcc -c BBBCAM_OV5642_DigitalCamera.c
	
clean : 
	rm OV2640_Playback OV3640_Playback OV5642_Playback OV7670_Playback OV2640_DigitalCamera OV5642_DigitalCamera 
	rm *.o