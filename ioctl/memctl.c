/*************************************************************************
	> File Name: memctl.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 29 Oct 2014 07:00:21 PM CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#include"memdev.h"

int main(void)
{
    int fd;
    fd = open("/dev/memdev0",O_RDWR);

    ioctl(fd,MEM_SET,115200);
    ioctl(fd,MEM_RESTART);

    close(fd);
    return 0;
}

