/*
 * Robot Navigation Program
 * www.robotnav.com
 *
 * (C) Copyright 2013 - 2014 Navigation Solutions, LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
