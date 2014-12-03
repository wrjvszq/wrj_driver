/*************************************************************************
	> File Name: app_key.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Fri 07 Nov 2014 07:57:00 PM CST
 ************************************************************************/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>

int main(void)
{
    int fd;
    int value;

    fd = open("/dev/210key",0);

    if(fd < 0)
        printf("open file fail\n");

    read(fd,&value,4);
        printf("the key is %d\n",value);

    close(fd);

    return 0;
}
