#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IN          0
#define OUT         1

#define LOW         0
#define HIGH        1

#define LED_PIN     110


#define BUF_MAX         4
#define DIRECTION_MAX   50


static int gpio_exprot(int pin)
{
    char buffer[BUF_MAX];
    int len;
    int fd;

    fd = open("/sys/class/gpio/export",O_WRONLY);
    if (fd < 0)
    {
        fprintf(stderr,"Failed to open exprot for writing!\n");
        return(-1);
    }
    
    len = snprintf(buffer,BUF_MAX,"%d",pin);
    if(write(fd,buffer,len) < 0)
    {
        fprintf(stderr,"Fail to exprot gpio!\n");
        return -1;
    }

    close(fd);
    return 0;
}

static int gpio_unexprot(int pin)
{
    char buffer[BUF_MAX];
    int len;
    int fd;

    fd = open("/sys/class/gpio/unexport",O_WRONLY);
    if (fd < 0)
    {
        fprintf(stderr,"Failed to open unexprot for writing!\n");
        return(-1);
    }
    
    len = snprintf(buffer,BUF_MAX,"%d",pin);
    if(write(fd,buffer,len) < 0)
    {
        fprintf(stderr,"Fail to unexprot gpio!\n");
        return -1;
    }

    close(fd);
    return 0;
}

static int gpio_direction(int pin,int dir)
{
    static const char dir_str[] = "in\0out";
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path,DIRECTION_MAX,"/sys/class/gpio/gpio%d/direction",pin);
    fd = open(path,O_WRONLY);
    if(fd < 0 )
    {
        fprintf(stderr,"Failed to open gpio direction for writing!\n");
        return -1;
    }
    if(write(fd,&dir_str[dir == IN?0:3],(dir == IN?2:3)) < 0)
    {
        fprintf(stderr,"Failed to set direction!\n");
        return -1;
    }

    close(fd);
    return 0;
}

static int gpio_read(int pin)
{
    char value_str[3];
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path,DIRECTION_MAX,"/sys/class/gpio/gpio%d/value",pin);
    fd = open(path,O_RDONLY);
    if(fd < 0 )
    {
        fprintf(stderr,"Failed to open gpio value for reading!\n");
        return -1;
    }
    if(read(fd,value_str,sizeof(value_str)) < 0)
    {
        fprintf(stderr,"Failed to read value!\n");
        return -1;
    }

    close(fd);
    return 0;
}

static int gpio_write(int pin,int value)
{
    static const char value_str[] = "01";
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path,DIRECTION_MAX,"/sys/class/gpio/gpio%d/value",pin);
    fd = open(path,O_WRONLY);
    if(fd < 0 )
    {
        fprintf(stderr,"Failed to open gpio value for writing!\n");
        return -1;
    }
    if(write(fd,&value_str[value == LOW?0:1],1) < 0)
    {
        fprintf(stderr,"Failed to write value!\n");
        return -1;
    }

    close(fd);
    return 0;

}

int main (int agrc,char *agrv[])
{
    gpio_exprot(LED_PIN);
    gpio_direction(LED_PIN,OUT);
    printf("led err blink!\n");

    for (int i = 0;i < 10;i++)
    {
      gpio_write(LED_PIN,HIGH);
      sleep(1);
      gpio_write(LED_PIN,LOW);
      sleep(1);
    }
    gpio_write(LED_PIN,LOW);
    gpio_unexprot(LED_PIN);
    printf("led err blink finish!\n");

    return 0;
}
