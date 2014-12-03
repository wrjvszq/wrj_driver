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
#include<linux/input.h>

int main(void)
{
    int fd;
    int count = 0, i = 0;
    struct input_event ev_key;

    fd = open("/dev/event1",0);

    if(fd < 0)
        printf("open file fail\n");

    while(1)
    {
        count = read(fd,&ev_key,sizeof(struct input_event));
        for(i = 0; i < (int)count/sizeof( struct input_event);i++)
        {
            if(EV_KEY == ev_key.type)
            printf("type:%d,code:%d,value:%d\n",ev_key.type,ev_key.code - 1,ev_key.value);
        }
    }

    close(fd);

    return 0;
}
