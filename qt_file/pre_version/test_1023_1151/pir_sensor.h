#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

class PIR_Sensor: public QThread
{
    Q_OBJECT
public:
    explicit PIR_Sensor(QObject *parent = 0);
    void stop();
    int m_stopFlag = false;

private:
    void run();
    int idx = 2;

signals:
    void ThreadEnd(int);
};
#endif // PIR_SENSOR_H
