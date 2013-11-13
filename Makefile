OBJS = d_lcd.o
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -g -Wall
TARGET = main

all: $(TARGET)
$(TARGET): $(OBJS) main.c
	$(CC) $(CFLAGS) $(OBJS) main.c -o $@ 
d_lcd.o: d_lcd.c d_lcd.h
	$(CC) $(CFLAGS) -c d_lcd.c 
clean:
	\rm *.o $(TARGET) 
