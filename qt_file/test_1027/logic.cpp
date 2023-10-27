#include "logic.h"
#include "mainwindow.h"

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;
extern int gJoystick;
extern int gOpenButton; // Cover Button
extern int gCloseButton; // Cover Button

extern int gWindowState;
extern int gCoverState;
extern int gOpenDegree;
extern int gLED;
extern int gUserMode;

Logic::Logic(QObject *parent) : QThread(parent)
{
    pre_detected = 0;
    tmp_detected = 0;
    pre_dist = 0;
    gWindowState = CLOSE;

    fd = serialOpen("/dev/ttyACM0",9600);
    serialPutchar(fd,'x');
}

void Logic::run()
{
    while(!m_stopFlag)
    {
        int msg = 0b00000000;

        // Motor Control
        if (gWindowState == CLOSE)
        {
            msg = windowClose(msg);
        }
        else
        {
            msg = windowOpen(msg);
        }

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

        // Set State
        if (gUserMode == 1) // User Mode
        {
            if (gJoystick < 3000)
            {
                gCoverState = OPEN;
                gWindowState = OPEN;
            }
            else if (gJoystick < 3500)
            {
                /* do nothing */
            }
            else
            {
                gCoverState = CLOSE;
                gWindowState = CLOSE;
            }
        }
        else // Smart Mode
        {
            // motor
            if (rainClose() == 1 || gyroClose() == 1) gWindowState = CLOSE;
            else gWindowState = OPEN;

            // led (TODO: QT button input)
            if (gLED == 1)
            {
                msg += 1 << LED;
            }

            // buzzer
            if (pirUwaveBuzzer() == 1)
            {
                msg += (1 << BUZZER);
            }
        }

        serialPutchar(fd, msg);
        emit ThreadEnd(gUwave);

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
    if (gUwave > CLOSE_LENGTH)
    {
        msg += (1 << WINDOW_SET); // cw, close
    }
    return msg;
}
int Logic::windowOpen(int msg)
{
    if (gUwave > (gOpenDegree / 100 * OPEN_LENGTH))
    {
        msg += (1 << WINDOW_SET);
        msg += (1 << WINDOW_DIR); // ccw, open
    }

//    if ((gOpenDegree == 0) && (gUwave > OPEN_LENGTH_0))
//    {
//        msg += (1 << WINDOW_SET);
//        msg += (1 << WINDOW_DIR); // ccw, open
//    }
//    else if ((gOpenDegree == 1) && (gUwave > OPEN_LENGTH_1))
//    {
//        msg += (1 << WINDOW_SET);
//        msg += (1 << WINDOW_DIR); // ccw, open
//    }
//    else if ((gOpenDegree == 2) && (gUwave > OPEN_LENGTH_2))
//    {
//        msg += (1 << WINDOW_SET);
//        msg += (1 << WINDOW_DIR); // ccw, open
//    }
//    else if ((gOpenDegree == 3) && (gUwave > OPEN_LENGTH_3))
//    {
//        msg += (1 << WINDOW_SET);
//        msg += (1 << WINDOW_DIR); // ccw, open
//    }
//    else if ((gOpenDegree == 4) && (gUwave > OPEN_LENGTH_FULL))
//    {
//        msg += (1 << WINDOW_SET);
//        msg += (1 << WINDOW_DIR); // ccw, open
//    }
    return msg;
}

int Logic::gyroClose()
{
    int res = 0;
    if(gGyroX >= 35 || gGyroX <= -35 || gGyroY >= 35 || gGyroY <= -35){
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
