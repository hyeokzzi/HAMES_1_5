#ifndef MPU_SENSOR_H
#define MPU_SENSOR_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

class MPU_Sensor : public QThread
{
    Q_OBJECT
public:
    explicit MPU_Sensor(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;

private:
    void run();
    int idx = 1;

signals:
    void ThreadEnd(int);
};

#endif // MPU_SENSOR_H
