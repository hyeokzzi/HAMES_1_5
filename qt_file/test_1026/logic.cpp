#include "logic.h"
#include "mainwindow.h"

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;
extern int gYsig;

Logic::Logic(QObject *parent) : QThread(parent)
{
    pre_detected = 0;
    tmp_detected = 0;
    pre_dist = 0;
    status = CLOSE;
    fd = serialOpen("/dev/ttyACM0",9600);
    serialPutchar(fd,'x');
}

void Logic::run()
{
    while(!m_stopFlag)
    {
        int msg = 0b00000000;

        // motor
//        if (rainClose() == 1 || gyroClose() == 1) status = CLOSE;
//        if (rainClose() == 1) status = CLOSE;
//        else status = OPEN;

        if (status == CLOSE)
        {
            if (gUwave > CLOSE_LENGTH)
            {
                msg += (1 << WINDOW_SET);
            }
        }
        else
        {
            if (gUwave > OPEN_LENGTH)
            {
                msg += (1 << WINDOW_SET);
                msg += (1 << WINDOW_DIR); // ccw
            }
        }

        // led (TODO: QT button input)
//        msg += 1 << LED;

        // buzzer
        if (pirUwaveBuzzer() == 1)
        {
            msg += (1 << BUZZER);
        }

        serialPutchar(fd, msg);
        emit ThreadEnd(gUwave);

       sleep(1);
    }

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
