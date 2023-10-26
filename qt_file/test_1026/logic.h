#ifndef LOGIC_H
#define LOGIC_H

#include <QThread>
#include <QDebug>
#include <unistd.h>

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <math.h>
#include <deque>

using namespace std;

#define MAX_Q_SIZE 35
#define DIST_STDEV_TH 1
#define RAIN_TH 2500

#define CLOSE_LENGTH 3
#define OPEN_LENGTH 17

#define CW 0
#define CCW 1
#define UNSET 0
#define SET 1
#define CLOSE 0
#define OPEN 1

enum {
    BUZZER = 0,
    LED,
    COVER_DIR,
    COVER_SET,
    WINDOW_DIR,
    WINDOW_SET
};

class Logic: public QThread
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = 0);
    void stop();

    int m_stopFlag = false;

private:
    void run();

    int gyroClose();
    int rainClose();
    int uwaveClose();
    int pirUwaveBuzzer();

    double calcStdev();

    uint8_t pre_detected;
    uint8_t tmp_detected;
    uint8_t pre_dist;
    uint8_t status; // 1: open, 0: close

    deque<int> Q;

signals:
    void ThreadEnd(int);
};

#endif // LOGIC_H
