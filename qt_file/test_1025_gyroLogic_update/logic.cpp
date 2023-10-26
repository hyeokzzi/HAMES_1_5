#include "logic.h"
#include "mainwindow.h"

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;

Logic::Logic(QObject *parent) : QThread(parent)
{
    pre_detected = 0;
    tmp_detected = 0;
    pre_dist = 0;
    status = 0;
}

void Logic::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code
        int buf[3];

        // motor
        if (uwaveClose() == 1 || gyroClose() == 1) status = CLOSE;
        else status = OPEN;

        if (status == CLOSE)
        {
            if (gUwave > CLOSE_LENGTH)
            {
                buf[0] = SET;
                buf[1] = CW;
            }
            else
            {
                buf[0] = UNSET;
            }
        }
        else
        {
            if (gUwave > OPEN_LENGTH)
            {
                buf[0] = SET;
                buf[1] = CCW;
            }
            else
            {
                buf[0] = UNSET;
            }
        }

        // led (TODO)

        // buzzer
        if (pirUwaveBuzzer() == 1) buf[0] = SET;
        else buf[0] = UNSET;

        //
       emit ThreadEnd(buf[0]);
//        emit ThreadEnd(gRain);
       sleep(1);
    }
}

void Logic::runMotor()
{

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
