EXEC = adc_test
OBJS = adc_test.o
 
CROSS = arm-linux-gnueabihf-
CC = $(CROSS)gcc 
STRIP = $(CROSS)strip
CFLAGS = -Wall -std=gnu99 -g -O2
 
all: clean $(EXEC)
 
$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(STRIP) $@

clean:
	-rm -f $(EXEC) *.o
