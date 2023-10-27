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
#include <wiringSerial.h>
using namespace std;

#define MAX_Q_SIZE 35
#define DIST_STDEV_TH 1
#define RAIN_TH 2500

#define CLOSE_LENGTH 5
#define OPEN_LENGTH 20
//#define OPEN_LENGTH_0 4
//#define OPEN_LENGTH_1 8
//#define OPEN_LENGTH_2 12
//#define OPEN_LENGTH_3 16
//#define OPEN_LENGTH_FULL 20

#define CW 0 // close
#define CCW 1 // open
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
    int stick_signal();
    double calcStdev();

    int coverClose(int msg);
    int coverOpen(int msg);
    int windowClose(int msg);
    int windowOpen(int msg);

    uint8_t pre_detected;
    uint8_t tmp_detected;
    uint8_t pre_dist;

    deque<int> Q;
    int fd;
signals:
    void ThreadEnd(int);
};

#endif // LOGIC_H
