#include "logic.h"
#include "mainwindow.h"
#include "gpio.h"

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;
extern int gJoystick;
extern int gOpenButton; // Cover Button
extern int gCloseButton; // Cover Button

// init?
extern int gWindowState;
extern int gCoverState;
extern int gOpenDegree;
extern int gLED;
extern int gUserMode; // 0: smart mode, 1: user mode

Logic::Logic(QObject *parent) : QThread(parent)
{
    pre_detected = 0;
    tmp_detected = 0;
    pre_dist = 0;
    stop_moving = 0;

    gWindowState = OPEN;
//    gCoverState = CLOSE;
    gOpenDegree = 100;
    gLED = 0;
    gUserMode = 0;

    fd = serialOpen("/dev/ttyACM0",9600);
    serialPutchar(fd,'x');
}

void Logic::run()
{
    while(!m_stopFlag)
    {
        int msg = 0b00000000;

        if (gWindowState == OPEN)
            qDebug() << QString("gWindowState = ") << OPEN;
        else
            qDebug() << QString("gWindowState = ") << CLOSE;

        qDebug() << QString("stop_moving = ") << stop_moving;


        // Set State
        if (gUserMode == 1) // User Mode
        {
            if (gJoystick < 3000) // up, open
            {
                qDebug() << QString("Joystick OPEN!!!");

//                if (gCoverState != OPEN)
//                {
//                    gCoverState = OPEN;
//                    stop_moving = 0;
//                }
                if (gWindowState != OPEN)
                {
                    gWindowState = OPEN;
                    stop_moving = 0;
                }
            }
            else if (gJoystick < 3500)
            {
                /* do nothing */
            }
            else // down, close
            {
                qDebug() << QString("Joystick CLOSE!!!");

//                if (gCoverState != CLOSE)
//                {
//                    gCoverState = CLOSE;
//                    stop_moving = 0;
//                }
                if (gWindowState != CLOSE)
                {
                    gWindowState = CLOSE;
                    stop_moving = 0;
                }
            }
        }
        else // Smart Mode
        {
            // motor
            if (rainClose() == 1 || gyroClose() == 1)
            {
                gWindowState = CLOSE;
                stop_moving = 0;
            }

            // led (TODO: QT button input)
//            if (gLED == 1)
//            {
//                msg += (1 << LED);
//            }

            // buzzer
            if (pirUwaveBuzzer() == 1)
            {
                msg += (1 << BUZZER);
            }
        }

        // Motor Control
        qDebug() << QString("---------------------");
        if (gWindowState == CLOSE)
        {
            qDebug() << QString("Motor: window close");
            msg = windowClose(msg);
        }
        else
        {
            qDebug() << QString("Motor: window open");
            msg = windowOpen(msg);
        }
        qDebug() << QString("---------------------");
        qDebug() << QString("==========================================");

//        if ((gCoverState == CLOSE) && (gWindowState == CLOSE))
//        {
//            if (gCloseButton == 1) msg = windowClose(msg); // Cover already closed
//            else msg = coverClose(msg);
//        }
//        else if ((gCoverState == OPEN) && (gWindowState == CLOSE))
//        {
//            if (gOpenButton == 1) msg = windowClose(msg); // Cover already opened
//            else msg = coverOpen(msg);
//        }
//        else if ((gCoverState == CLOSE) && (gWindowState == OPEN))
//        {
//            /* WARNING */
//        }
//        else
//        {
//            if (gOpenButton == 1) msg = windowOpen(msg); // Cover already opened
//            else msg = coverOpen(msg);
//        }


        serialPutchar(fd, msg);
        emit ThreadEnd(msg);

       sleep(1);
    }

}

int Logic::coverClose(int msg)
{
    msg += (1 << COVER_SET); // cw, close
    return msg;
}
int Logic::coverOpen(int msg)
{
    msg += (1 << COVER_SET);
    msg += (1 << COVER_DIR); // ccw, open
    return msg;
}
int Logic::windowClose(int msg)
{
    if ((stop_moving == 0) && ((gUwave > CLOSE_LENGTH) && (gUwave < 80)))
    {
        msg += (1 << WINDOW_SET); // cw, close
    }
    else
    {
        stop_moving = 1;
    }
    return msg;
}
int Logic::windowOpen(int msg)
{
//    int th = gOpenDegree / 100 * OPEN_LENGTH;
    int th = OPEN_LENGTH;
    if ((stop_moving == 0) && ((gUwave < th) || (gUwave > 80)))
    {
        msg += (1 << WINDOW_SET);
        msg += (1 << WINDOW_DIR); // ccw, open
    }
    else
    {
        stop_moving = 1;
    }
    return msg;
}

int Logic::gyroClose()
{
    int res = 0;
    if(gGyroX >= 10 || gGyroX <= -10 || gGyroY >= 10 || gGyroY <= -10){
    	if(gUwave){	//gUwave logic required 
    		res = 1;	//close 
		}
	}
    return res;
}

int Logic::rainClose()
{
    int res = 0;

    /* Insert Your Code */
    if (gRain < RAIN_TH) res = 1;
    else res = 0;

    return res;
}

int Logic::uwaveClose()
{
    int res = 0;

    /* Insert Your Code */
    if (gUwave < CLOSE_LENGTH) res = 0;
    else res = 1;

    return res;
}

int Logic::pirUwaveBuzzer()
{
    int res = 0;

    if (Q.size() == MAX_Q_SIZE) Q.pop_front();
    Q.push_back(gUwave);

    tmp_detected = gPir;

    if ((pre_detected == 0) && (tmp_detected == 1))
    {
        double stdev = calcStdev();

        if (stdev > DIST_STDEV_TH) res = 1;
        else res = 0;
    }

    pre_detected = tmp_detected;
    pre_dist = gUwave;

    return res;
}

double Logic::calcStdev()
{
    double sum1 = 0;
    double sum2 = 0;
    double avg = 0;
    double var = 0;
    double stdev = 0;

    for (int i = 0; i < Q.size(); i++)
    {
        sum1 += Q[i];
    }
    avg = sum1 / static_cast<double>(Q.size());

    for (int i = 0; i < Q.size(); i++)
    {
        sum2 += pow((Q[i] - avg), 2);
    }
    var = sum2 / static_cast<double>(Q.size() - 1);
    stdev = sqrt(var);

    return stdev;
}

void Logic::stop()
{
    m_stopFlag = true;
}
