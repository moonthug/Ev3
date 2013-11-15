#include  <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lms2012.h"
#include "d_lcd.h"

int main()
{
	//Create a structure that will store the LCD information
	LCD my_lcd;
	//Initialize and clear screen
	dLcdInit(my_lcd.Lcd);
	LCDClear(my_lcd.Lcd);
	//Draw and write something
	dLcdRect(my_lcd.Lcd, FG_COLOR, 60, 60, 20, 20);
	dLcdDrawCircle(my_lcd.Lcd, FG_COLOR, 40, 100, 20);
	dLcdFillRect(my_lcd.Lcd, FG_COLOR, 100, 80, 40, 40);
	dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 10, LARGE_FONT, (signed char *)"Hello World");
	dLcdDrawText(my_lcd.Lcd, FG_COLOR, 1, 35, NORMAL_FONT, (signed char *)"BACK BUTTON to exit");
	//Update screen with information
	dLcdUpdate(&my_lcd);
	//Exit
	dLcdExit(); 
	//ToDo: I need to figure how to restore the screen once the program ends
	return 1;
}
