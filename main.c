/* 
This is kernel module file for IMU sensor 
consisting of MPU9255 and BMP280, for 10 degrees of freedom 
*/

/* 
      Necessary Header files 
*/
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include <linux/uaccess.h>        
#include <linux/time.h>
#include <linux/random.h>
#include <linux/ioctl.h>

/*********************************************************/

/*
       MACROS to generate request code 
*/

#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>
#define MAJOR_NUM 100
#define GYRO_X _IOWR(MAJOR_NUM, 0, char *)

#define GYRO_Y _IOWR(MAJOR_NUM, 1, char *)

#define GYRO_Z _IOWR(MAJOR_NUM, 2, char *)

#define ACCELEROMETER_X _IOWR(MAJOR_NUM, 3, char *)

#define ACCELEROMETER_Y _IOWR(MAJOR_NUM, 4, char *)

#define ACCELEROMETER_Z _IOWR(MAJOR_NUM, 5, char *)

#define COMPASS_X _IOWR(MAJOR_NUM, 6, char *)

#define COMPASS_Y _IOWR(MAJOR_NUM, 7, char *)

#define COMPASS_Z _IOWR(MAJOR_NUM, 8, char *)

#define BPM_PRESSURE _IOWR(MAJOR_NUM, 9, char *)

#define DEVICE_FILE_NAME "/dev/imu_char"

#endif

/********************************************************************************/

static dev_t first_char_dev;      //variable for device number
static struct class *cls;         //varible for the device class
static struct cdev c_dev;         //variable for the character device structure

static uint16_t message;

/**********************************************************************************/

/* 
          file operation function defitions 
*/

static int my_open(struct inode *i, struct file *f)
{
printk(KERN_INFO "inside open():\n");
return 0;
}
static int my_release(struct inode *i, struct file *f)
{
printk(KERN_INFO "inside release():\n");
return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
uint16_t random;  //variable to read random number

printk(KERN_INFO "inside my_read():\n");                           
get_random_bytes(&random, sizeof(random));     // random number generation function
random= random%1023;                           // limiting th er andom number to be of 10 bit length
 
printk(KERN_INFO "random number : %d\n", random);

message=random;

return random;
}
/*********************************************************************************/

/* 
       file operation structure definition 
*/

static struct file_operations fops=
{
.owner=THIS_MODULE,
.read=my_read,
.open=my_open,
.release=my_release
};

/**********************************************************************************/

/* 
      IOCTL driver mode  function definition 
*/

static long ioctl(struct file *file,             
                  unsigned int ioctl_num,        
                  unsigned long ioctl_param)
{
    
    char *temp;
    char ch;

    /*
     * Switch case for the corresponding sensors
     */
    switch (ioctl_num) {
   
    case GYRO_X:    
          temp = (char *)ioctl_param;
          copy_to_user(temp, &message, sizeof(message));
         break;
         
    case GYRO_Y:  
          
         temp = (char *)ioctl_param;
          copy_to_user(temp, &message, sizeof(message));  
         break;
                           
    case GYRO_Z:            
         temp = (char *)ioctl_param;
        copy_to_user(temp, &message, sizeof(message));  
         break;
         
    case ACCELEROMETER_X:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
         break;
         
    case ACCELEROMETER_Y:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);

         break;
                           
    case ACCELEROMETER_Z:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	 

         break; 
         
    case COMPASS_X:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  
         break;
         
    case COMPASS_Y:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	 
         break;
                           
    case COMPASS_Z:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  
         break;  
         
    case BPM_PRESSURE:
         
          temp = (char *)ioctl_param;
          get_user(ch, temp);
         break;
        default :  break;

    }

    return 1;
}

/********************************************************************/

/*
        Device registration and Device node creation
*/
static int __init dev_reg(void)
{
printk(KERN_INFO "dev_reg successful\n\n");
if(alloc_chrdev_region(&first_char_dev,0,2, "BPHC")<0)  // 2 minors numbers each one for MPU9255 and BMP280
{
return -1;
}
printk(KERN_INFO "<Major, Minor> : <%d, %d>\n",MAJOR(first_char_dev),MINOR(first_char_dev));

// device node cration
if((cls=class_create(THIS_MODULE,"char_drv"))==NULL)  
{
unregister_chrdev_region(first_char_dev,2);
return -1;
}

if(device_create(cls,NULL,first_char_dev,NULL,"imu_char")==NULL)
{
class_destroy(cls);
unregister_chrdev_region(first_char_dev,2);
return -1;
}
/*********************************************************/

/*
          linking userspace and kernel space
*/
cdev_init(&c_dev,&fops);
if(cdev_add(&c_dev,first_char_dev,2)== -1)
{
device_destroy(cls,first_char_dev);
class_destroy(cls);
unregister_chrdev_region(first_char_dev,2);
return -1;
} 
return 0;
}

/*******************************************************/

/*
    free or clean up
*/
static void __exit dev_dereg(void)
{
cdev_del(&c_dev);
device_destroy(cls,first_char_dev);
class_destroy(cls);
unregister_chrdev_region(first_char_dev,2);
unregister_chrdev_region(first_char_dev,2);
printk(KERN_INFO "dev_dereg successful");

}
/*****************************************************/


module_init(dev_reg);
module_exit(dev_dereg);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("DEEPAK CHEKURI");
MODULE_DESCRIPTION("Char on Fire");
