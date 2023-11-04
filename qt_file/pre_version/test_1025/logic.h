#ifndef LOGIC_H
#define LOGIC_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PIR_GPIO_IN 17

class Logic: public QThread
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);
    void stop();

    int m_stopFlag = false;

    int gyroClose();
    int rainClose();
    int uwaveClose();
    int pirUwaveBuzzer();
    void run();

private:
    void run();
    int idx = 9;

signals:
    void ThreadEnd(int);
};

#endif // LOGIC_H
