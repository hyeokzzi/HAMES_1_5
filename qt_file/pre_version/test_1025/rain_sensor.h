#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208 8 //GPIO 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 //1Mhz

class Rain_Sensor: public QThread
{
    Q_OBJECT
public:
    explicit Rain_Sensor(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;

private:
    void run();
    int idx = 3;

signals:
    void ThreadEnd(int);
};

#endif // RAIN_SENSOR_H
