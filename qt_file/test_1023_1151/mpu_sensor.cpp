#include "mpu_sensor.h"
#include "mainwindow.h"

MPU_Sensor::MPU_Sensor(QObject *parent) : QThread(parent)
{

}
void MPU_Sensor::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code

        //
        emit ThreadEnd(idx);
        sleep(1);
    }
}

void MPU_Sensor::stop()
{
    m_stopFlag = true;
}

