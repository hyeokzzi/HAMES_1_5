#include "mpu_sensor.h"
#include "mainwindow.h"

extern double gGyroX;
extern double gGyroY;

MPU_Sensor::MPU_Sensor(QObject *parent) : QThread(parent)
{

}

void MPU_Sensor::run()
{
    fd = wiringPiI2CSetup(Device_Address);  /*Initializes I2C with device Address*/
    fd1 = serialOpen("/dev/ttyACM0",9600);
    MPU6050_Init(); /* Initializes MPU6050 */
    serialPutchar(fd1, 'x');

    while(!m_stopFlag)
    {
        AcX = read_raw_data(ACCEL_XOUT_H);
        AcY = read_raw_data(ACCEL_YOUT_H);
        AcZ = read_raw_data(ACCEL_ZOUT_H);
        GyX = read_raw_data(GYRO_XOUT_H);
        GyY = read_raw_data(GYRO_YOUT_H);
        GyZ = read_raw_data(GYRO_ZOUT_H);

        static int32_t AcXSum = 0, AcYSum = 0, AcZSum=0;
        static int32_t GyXSum = 0, GyYSum = 0, GyZSum=0;
        static double AcXOff = 0, AcYOff = 0, AcZOff=0;
        static double GyXOff = 0, GyYOff = 0, GyZOff=0;
        static int cnt_sample=1000;

        if(cnt_sample>0){
            AcXSum += AcX; AcYSum += AcY; AcZSum += AcZ;
            GyXSum += GyX; GyYSum += GyY; GyZSum += GyZ;
            cnt_sample--;
            if(cnt_sample == 0){
                AcXOff = AcXSum / 1000.0;
                AcYOff = AcYSum / 1000.0;
                AcZOff = AcZSum / 1000.0;
                GyXOff = GyXSum / 1000.0;
                GyYOff = GyYSum / 1000.0;
                GyZOff = GyZSum / 1000.0;
            }
            delay(1);
        }
        double AcXD = AcX - AcXOff;
        double AcYD = AcY - AcYOff;
    //    double AcZD = AcZ - AcZOff+16384;
        double GyXD = GyX - GyXOff;
        double GyYD = GyY - GyYOff;
        double GyZD = GyZ - GyZOff;

        static unsigned long t_prev = 0;
        unsigned long t_now = micros();
        double dt = (t_now - t_prev)/1000000.0;
        t_prev = t_now;

        const float GYROXYZ_TO_DEGREES_PER_SEC = 131;
        double GyXR = GyXD/GYROXYZ_TO_DEGREES_PER_SEC;
        double GyYR = GyYD/GYROXYZ_TO_DEGREES_PER_SEC;
        double GyZR = GyZD/GYROXYZ_TO_DEGREES_PER_SEC;

        static double gyAngleX = 0.0, gyAngleY= 0.0, gyAngleZ=0.0;

        gyAngleX += GyXR*dt;
        gyAngleY += GyYR*dt;
        gyAngleZ += GyZR*dt;

        const float RADIANS_TO_DEGREES = 180/3.14159;
        double AcYZD = sqrt(pow(AcY, 2) + pow(AcZ, 2));
        double AcXZD = sqrt(pow(AcX, 2) + pow(AcZ, 2));
        double acAngleY = atan(-AcXD/AcYZD)*RADIANS_TO_DEGREES;
        double acAngleX = atan(-AcYD/AcXZD)*RADIANS_TO_DEGREES;
        double acAngleZ=0;

        const double ALPHA = 0.96;
        static double cmAngleX =0.0, cmAngleY=0.0, cmAngleZ =0.0;
        cmAngleX = ALPHA*(cmAngleX+GyXR*dt)+(1.0-ALPHA)*acAngleX;
        cmAngleY = ALPHA*(cmAngleY+GyYR*dt)+(1.0-ALPHA)*acAngleY;
        cmAngleZ = gyAngleZ;

        static int cnt_loop;
        cnt_loop++;
        if(cnt_loop%100 != 0)	continue;  //for output speed

		gGyroX = cmAngleX;
		gGyroY = cmAngleY;

        emit ThreadEnd(cmAngleX);
        emit ThreadEnd(cmAngleY);
        sleep(1);
    }
}

void MPU_Sensor::stop()
{
    m_stopFlag = true;
}

void MPU_Sensor::MPU6050_Init(){

    wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
    wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
    wiringPiI2CWriteReg8 (fd, CONFIG, 0);		/* Write to Configuration register */
    wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
    wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */
    }

short MPU_Sensor::read_raw_data(int addr){
    int16_t high_byte,low_byte,value;
    high_byte = wiringPiI2CReadReg8(fd, addr);
    low_byte = wiringPiI2CReadReg8(fd, addr+1);  //ex) ACCEL_XOUT_H + 1 == ACCEL_XOUT_L
    value = (high_byte << 8) | low_byte;
    return value;
}
