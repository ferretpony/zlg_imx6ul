EXEC = led
OBJS = led.o
 
CROSS = arm-linux-gnueabihf-
CC = $(CROSS)gcc 
STRIP = $(CROSS)strip
CFLAGS = -Wall -g -std=gnu99 -O2
 
all: clean $(EXEC)
 
$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(STRIP) $@
 
clean:
	-rm -f $(EXEC) *.o
