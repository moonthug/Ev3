#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "lms2012.h"
#include "d_lcd.h"

//Runtime constants
const int MAX_SAMPLES = 100;

//Global variables and constants used by the sensor handling functions
const int XGL_PACKET_SIZE = 10; //2(gyro angle) + 2(gyro rate) + 2(acc x) + 2(acc y) + 2(acc z) 
const char XGL_PORT = 0x0; //EV3 label minus 1

int xgl_device_file;
IIC   *pXgl;

//INITIALIZE DEVICE
int init_xg1300l_gyro()
{
	IICDAT IicDat;
	//Open the device xgl_device_file
	if((xgl_device_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC)) == -1)
	{
		printf("Failed to open device\n");
		return 0; 
	}
	pXgl = (IIC *)mmap(0, sizeof(IIC), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, xgl_device_file, 0);
	if (pXgl == MAP_FAILED)
	{
		printf("Map failed\n");
		return 0;
	}
	//Setup IIC to read 2 packets
	//This part is only needed for devices that use more than one byte
	//or special configuration
	IicDat.Port = XGL_PORT;
	IicDat.Time = 0;
	IicDat.Repeat = 0;
	IicDat.RdLng = XGL_PACKET_SIZE;
	IicDat.WrLng = 2;
	// Set the device I2C address
	IicDat.WrData[0] = 0x01;
	// Specify the register that will be read (0x42 = angle)
	IicDat.WrData[1] = 0x42;
	// Setup I2C comunication
	ioctl(xgl_device_file,IIC_SETUP,&IicDat);
	printf("Device is ready\n");
	return 1;
}

//PROCESS SENSOR DATA
void get_xg1300l_gyro(float *angle, float *rate, float *acc_x, float *acc_y, float *acc_z)
{
	//Compute angle, angular rate and accelerations
	 *acc_z = (pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][0] * 256 + pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][1]) / 100.0;
	 *acc_y = (pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][2] * 256 + pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][3]) / 100.0;
	 *acc_x = (pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][4] * 256 + pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][5]) / 100.0;
	 *rate  = (pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][6] * 256 + pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][7]) / 100.0;
	 *angle = (pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][8] * 256 + pXgl->Raw[XGL_PORT][pXgl->Actual[XGL_PORT]][9]) / 100.0;
}

//CLOSE DEVICE
void close_xg1300l_gyro()
{
	printf("Clossing device\n");
	close(xgl_device_file);
}

int main()
{
	int i;
	float angle;
	float rate;
	float acc_x;
	float acc_y;
	float acc_z;
	char aux_buffer[200];
	
	//Create a structure that will store the LCD information
	LCD my_lcd;
	//Initialize and clear screen
	dLcdInit(my_lcd.Lcd);
	LCDClear(my_lcd.Lcd);

	if(!init_xg1300l_gyro())
		return -1;

	for(i = 0;i<MAX_SAMPLES;i++)
	{ //Print the direct outp from the XG1300L device
		get_xg1300l_gyro(&angle, &rate, &acc_x, &acc_y, &acc_z);
		sprintf(aux_buffer,"Angle: %0.2f [deg]   ", angle);
		dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 20, NORMAL_FONT, (signed char *)aux_buffer);
		printf("%s\n", aux_buffer);
		sprintf(aux_buffer, "Rate:  %0.2f [deg/s]   ", rate);
		dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 40, NORMAL_FONT, (signed char *)aux_buffer);
		printf("%s\n", aux_buffer);
		sprintf(aux_buffer, "AccX:  %0.2f [m/s^2]   ", acc_x);
		dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 60, NORMAL_FONT, (signed char *)aux_buffer);
		printf("%s\n", aux_buffer);
		sprintf(aux_buffer, "AccY:  %0.2f [m/s^2]   ", acc_y);
		dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 80, NORMAL_FONT, (signed char *)aux_buffer);
		printf("%s\n", aux_buffer);
		sprintf(aux_buffer, "AccZ:  %0.2f [m/s^2]   ", acc_z);
		dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 100, NORMAL_FONT, (signed char *)aux_buffer);
		printf("%s\n\n", aux_buffer);
		dLcdUpdate(&my_lcd);
		sleep(1);
	}

	//Close devices
	close_xg1300l_gyro();
	dLcdExit(); 
	return 1;
}
