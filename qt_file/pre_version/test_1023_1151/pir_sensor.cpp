#include "pir_sensor.h"
#include "mainwindow.h"

PIR_Sensor::PIR_Sensor(QObject *parent) : QThread(parent)
{

}
void PIR_Sensor::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code

        //
        emit ThreadEnd(idx);
        sleep(1);
    }
}

void PIR_Sensor::stop()
{
    m_stopFlag = true;
}
