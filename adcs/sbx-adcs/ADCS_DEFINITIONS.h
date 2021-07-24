/*
   This file contains definitions relevant to the ADCS system
   of the QSET CAN-SBX Balloon project.
*/

//Booleans controlling what is being read
#define GPS_get_time
#define GPS_get_coords
#define GPS_get_alt
#define BNO_get_orient
#define BNO_get_gyro
#define BNO_get_acc
#define BNO_get_mag
#define BNO_get_temp
#define MPU_get_gyro
#define MPU_get_acc
#define MPU_get_temp

//controlling read rate
const int file_time = 600000;
const int gps_time = 1000;
const int bno_time = 40;
const int mpu_time = 40;
const int min_time = min(min(gps_time, bno_time), mpu_time);
const int max_time = max(gps_time,max(bno_time,mpu_time));
