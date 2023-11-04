#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

<<<<<<< HEAD:qt_file/pre_version/test_1024_final/rain_sensor.h
#include <QThread>
#include <QDebug>
#include <unistd.h>

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

=======
>>>>>>> main:qt_file/test_1024/rain_sensor.h
#endif // RAIN_SENSOR_H
