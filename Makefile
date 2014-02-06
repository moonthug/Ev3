OBJS = d_lcd.o
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -g 
TARGET = lcd lcd_gyro lcd_acc

all: $(TARGET)
lcd: $(OBJS) main_lcd.c
	$(CC) $(CFLAGS) $(OBJS) main_lcd.c -o $@ 
lcd_gyro: $(OBJS) main_lcd_gyro.c
	$(CC) $(CFLAGS) $(OBJS) main_lcd_gyro.c -o $@ 
lcd_acc: $(OBJS) main_lcd_acc.c
	$(CC) $(CFLAGS) $(OBJS) main_lcd_acc.c -lm -o $@ 
d_lcd.o: d_lcd.c d_lcd.h
	$(CC) $(CFLAGS) -c d_lcd.c 
clean:
	\rm *.o $(TARGET) 
