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

#define MAX_Q_SIZE 30
#define DIST_STDEV_TH 2
#define RAIN_TH 4000

#define CLOSE_LENGTH 3
#define OPEN_LENGTH 18

#define UNSET 0
#define SET 1
#define CLOSE 0
#define OPEN 1
#define MARGIN 2

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

    void printMsg(int msg);

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
    uint8_t stop_moving_cover;
    uint8_t stop_moving_window;

    deque<int> Q;
    int fd;
signals:
    void ThreadEnd(int);
};

#endif // LOGIC_H
