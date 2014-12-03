/*************************************************************************
	> File Name: memdev.h
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 29 Oct 2014 06:40:11 PM CST
 ************************************************************************/

#ifndef _MEMDEV_H
#define _MEMDEV_H

#define MEM_NUM 'm'
#define MEM_SET _IOW(MEM_NUM,0,int)
#define MEM_RESTART _IO(MEM_NUM,1)

#endif
