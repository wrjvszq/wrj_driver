/*************************************************************************
	> File Name: my-frist-dev.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 29 Oct 2014 02:22:31 AM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>

struct cdev my_cdev;
dev_t devno;

int my_dev1_regs[5];
int my_dev2_regs[5];

static int mem_open(struct inode *node, struct file *filep)
{
    int num = MINOR(node->i_rdev);

    if( num == 0 )
        filep -> private_data = my_dev1_regs;
    else if( num == 1 )
        filep -> private_data = my_dev2_regs;
    else
        return -ENODEV;

    return 0;

}

static int mem_close(struct inode *node, struct file *filep)
{
    return 0;
}

static ssize_t mem_read(struct file *filep, char __user *buf, size_t size , loff_t *ppos)
{
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    int *reg_base = filep -> private_data;

    if(p >= 5*sizeof(int))
        return 0;
    if(count > 5*sizeof(int) - p)
        count = 5*sizeof(int) - p;
    if(copy_to_user(buf,reg_base + p,count))
    {
        ret = -EFAULT;
    }
    else
    {
        *ppos += count;
        ret = count;
    }

    return ret;
}

static ssize_t mem_write(struct file *filep, const char __user *buf, size_t size , loff_t *ppos)
{
    unsigned long p =  *ppos;
      unsigned int count = size;
      int ret = 0;
      int *register_addr = filep->private_data; 
      
      if (p >= 5*sizeof(int))
        return 0;
      if (count > 5*sizeof(int) - p)
        count = 5*sizeof(int) - p;
        
      if (copy_from_user(register_addr + p, buf, count))
        ret = -EFAULT;
      else
    {
            *ppos += count;
            ret = count;
          
    }

      return ret;
}

static loff_t mem_llseek(struct file *filep, loff_t offset, int whence)
{
    loff_t new_pos = 0;

    switch (whence)
    {
        case SEEK_SET:
            new_pos = 0 + offset;
            break;
        case SEEK_CUR:
            new_pos = filep -> f_pos + offset;
            break;
        case SEEK_END:
            new_pos = 5*sizeof(int) - 1 + offset;
            break;
        default:
            return -EINVAL;
    }

    if((new_pos < 0) || (new_pos >5*sizeof(int)))
        return -EINVAL;

    filep -> f_pos = new_pos;

    return new_pos;
}

static const struct file_operations mem_fops =
{
    .llseek = mem_llseek,
    .read = mem_read,
    .write = mem_write,
    .open = mem_open,
    .release = mem_close,
  
};

static int memdev_init(void)
{
    cdev_init(&my_cdev,&mem_fops);
    alloc_chrdev_region(&devno,0,2,"memdev");
    cdev_add(&my_cdev,devno,2);

    return 0;
}

static void memdev_exit(void)
{
    cdev_del(&my_cdev);
    unregister_chrdev_region(devno,2);

}

module_init(memdev_init);
module_exit(memdev_exit);
