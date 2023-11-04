#include "rain_sensor.h"
#include "mainwindow.h"

Rain_Sensor::Rain_Sensor(QObject *parent) : QThread(parent)
{

}
void Rain_Sensor::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code

        //
        emit ThreadEnd(idx);
        sleep(1);
    }
}

void Rain_Sensor::stop()
{
    m_stopFlag = true;
}

