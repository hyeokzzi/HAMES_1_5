#ifndef MPU_SENSOR_H
#define MPU_SENSOR_H

#define Device_Address 0x68	/*Device Address/Identifier for MPU6050*/

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

#include <QThread>
#include <QDebug>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


class MPU_Sensor : public QThread
{
    Q_OBJECT

public:
    explicit MPU_Sensor(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;
/*
public slots:
    void printScreen(int);
*/
private slots:
    void MPU6050_Init();
    short read_raw_data(int);

private:
    void run();
    int idx = 0;
    int fd = 0;
    int fd1 = 0;

    int16_t AcX,AcY,AcZ;
    int16_t GyX,GyY,GyZ;

signals:
    void ThreadEnd(int);
};

#endif // MPU_SENSOR_H
