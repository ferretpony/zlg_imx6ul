#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define AI8_PATH    "/sys/devices/platform/soc/2100000.aips-bus/2198000.adc/iio:device0/in_voltage8_raw"


int main(void)
{
    int fd,ret;
    double vref = 3.30;
    double voltage,get_voltage;
    char data[20];

    fd = open(AI8_PATH,O_RDONLY);
    if (fd < 0)
    {
        perror("open A18_DATA_PATH error!\n");
        return -1;
    }

    for(int i = 0;i<10;i++)
    {
        ret = read(fd,data,sizeof(data));
        if (ret < 0)
        {
            perror("read data error!\n");
            return -1;
        }
        
        get_voltage = atof(data);
        voltage = vref*(get_voltage/4096);
        printf("get value:%g,voltage:%.3f\n",get_voltage,voltage);        
    }

    return 0;
}
