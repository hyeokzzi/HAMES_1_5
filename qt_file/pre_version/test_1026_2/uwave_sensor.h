#ifndef UWAVE_SENSOR_H
#define UWAVE_SENSOR_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define UWAVE_TRIG_PIN 18
#define UWAVE_ECHO_PIN 21

class UWAVE_Sensor: public QThread
{
    Q_OBJECT
public:
    explicit UWAVE_Sensor(QObject *parent = 0);
    void stop();

    int getUwaveData();
    int m_stopFlag = false;

private:
    void run();
    int idx = 2;

    int _distance; // cm

signals:
    void ThreadEnd(int);
};
#endif // UWAVE_SENSOR_H
