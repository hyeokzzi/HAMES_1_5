#include "logic.h"
#include "mainwindow.h"

extern int gPir;
extern int gUwave;
extern int gRain;
extern double gGyroX;
extern double gGyroY;

Logic::Logic(QObject *parent) : QThread(parent)
{
}

void Logic::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code

        //
       emit ThreadEnd(idx);
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

    return res;
}

int Logic::uwaveClose()
{
    int res = 0;

    /* Insert Your Code */

    return res;
}

int Logic::pirUwaveBuzzer()
{
    int res = 0;

    /* Insert Your Code */

    return res;
}

void Logic::run()
{
    int res = 0;

    /* Insert Your Code */

    return res;
}

void Logic::stop()
{
    m_stopFlag = true;
}
