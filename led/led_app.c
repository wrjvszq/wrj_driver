/*************************************************************************
	> File Name: led_app.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 29 Oct 2014 08:52:02 PM CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include"led.h"

int main(int agrc,char *argv[])
{
    int fd;
    int cmd;

    if(agrc < 2)
    {
        printf("pelase enter sencond para!\n");
        return 0;
    }

    fd = open("/dev/leddev",O_RDWR);
    
    cmd = atoi(argv[1]);

    if(cmd == 1) 
        ioctl(fd,LED_ON);
    else
        ioctl(fd,LED_OFF);

        return 0;
}

