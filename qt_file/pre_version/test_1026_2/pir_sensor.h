#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

<<<<<<< HEAD:qt_file/pre_version/test_1026_2/pir_sensor.h
#include <QThread>
#include <QDebug>
#include <unistd.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PIR_GPIO_IN 17

class PIR_Sensor: public QThread
{
    Q_OBJECT
public:
    explicit PIR_Sensor(QObject *parent = 0);
    void stop();

    uint8_t getPirData();
    int m_stopFlag = false;

private:
    void run();
    int idx = 2;
    int _detected;

signals:
    void ThreadEnd(int);
};
=======
>>>>>>> main:qt_file/test_1024/pir_sensor.h
#endif // PIR_SENSOR_H
