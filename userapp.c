/*
  This is userapp file for the kernel module
*/

/*
   Necessary Header files
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>           /* ioctl */



/*********************************************************/

/*
       MACROS to generate request code 
*/

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


/*********************************************************/


/*
 * Function definitons  for the ioctl calls
 */
u_int16_t buffer;

int gyro_x (int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, GYRO_X, msg);

    if (return_val == 0) {
        printf("ioctl_ failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int gyro_y(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, GYRO_Y, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int gyro_z(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, GYRO_Z, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int accelerometer_x(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, ACCELEROMETER_X, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int accelerometer_y(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, ACCELEROMETER_Y, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int accelerometer_z(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, ACCELEROMETER_Z, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int compass_x(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, COMPASS_X, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int compass_y(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, COMPASS_Y, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}

int compass_z(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, COMPASS_Z, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}


int bpm_pressure(int f_descript, char *msg)
{
    int return_val;
    return_val = ioctl(f_descript, BPM_PRESSURE, msg);

    if (return_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", return_val);
        exit(-1);
    }
    return 0;
}
/*****************************************************************************/

/*
 *  Main function for IOCTL user app
 */
int main()
{
    int catch,sel;
    int f_descript;
    char *msg = "msg passed by ioctl\n";

    f_descript = open("/dev/imu_char", 0);
    printf("%d\n",f_descript);
    if (f_descript < 0) {
        printf("Can't open device file: %s\n", "/dev/imu_char");
        exit(-1);
    }

    printf("Data to be read from :  \n");
    printf(" 1. Gyroscope x reading \n 2. Gyroscope y reading\n 3. gyroscope z value\n  ");
    printf(" 4. accelerometer x value  \n 5. accelerometer y value \n 6. accelerometer z value \n");
    printf(" 7. Compass x direction  \n 8. Compass Y-direction  \n 9. Compass  Z-direction\n");
    printf("10. Barometeric pressure \n");
     scanf("%d",&sel);
     
     /*
     switch statement for selecting the functionality
     */
     
     switch(sel)
     {
          case 1: gyro_x(f_descript,"1");
                  break;
          case 2: gyro_y(f_descript,"2");
                  break;
          case 3: gyro_z(f_descript,"3");
                  break;
          case 4: accelerometer_x(f_descript,"4");
                  break;
          case 5: accelerometer_y(f_descript,"5");
                  break;
          case 6: accelerometer_z(f_descript,"6");
                  break;
          case 7: compass_x(f_descript,"7");
                  break;
          case 8: compass_y(f_descript,"8");
                  break;
          case 9: compass_z(f_descript,"9");
                  break;
          case 10: bpm_pressure(f_descript,"10");
                  break;
          default: printf("Choose proper option");
                  break;
     }  
 
    catch = read(f_descript, &buffer, sizeof(buffer));
    printf("sensor read value: \n");
    printf("%d\n", sel);
    close(f_descript);
    return 0;
}
/******************/
