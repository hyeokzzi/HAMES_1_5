#include "pir_sensor.h"
#include "mainwindow.h"
#include "gpio.h"

extern int gPir;
extern int gOpenButton;
extern int gCloseButton;

PIR_Sensor::PIR_Sensor(QObject *parent) : QThread(parent)
{
   pinMode(PIR_GPIO_IN, INPUT);
   pinMode(OPEN_BTN_GPIO, INPUT);
   pinMode(CLOSE_BTN_GPIO, INPUT);
}

void PIR_Sensor::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code
        gPir = digitalRead(PIR_GPIO_IN);
        gOpenButton = digitalRead(OPEN_BTN_GPIO);
        gCloseButton = digitalRead(CLOSE_BTN_GPIO);

        //
       emit ThreadEnd(gPir);
       sleep(1);
    }
}

uint8_t PIR_Sensor::getPirData()
{
    return _detected;
}

void PIR_Sensor::stop()
{
    m_stopFlag = true;
}
