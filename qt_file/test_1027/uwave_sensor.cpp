#include "uwave_sensor.h"
#include "mainwindow.h"
#include "gpio.h"

extern int gUwave;

UWAVE_Sensor::UWAVE_Sensor(QObject *parent) : QThread(parent)
{
    pinMode(UWAVE_TRIG_PIN, OUTPUT);
    pinMode(UWAVE_ECHO_PIN, INPUT);
}
void UWAVE_Sensor::run()
{
    while(!m_stopFlag)
    {
        // Insert Your Code
        long startTime;
        long travelTime;

        digitalWrite(UWAVE_TRIG_PIN, LOW);
        usleep(2);
        digitalWrite(UWAVE_TRIG_PIN, HIGH);
        usleep(20);
        digitalWrite(UWAVE_TRIG_PIN, LOW);

        while (digitalRead(UWAVE_ECHO_PIN) == LOW)
            ;
        startTime = micros();

        while (digitalRead(UWAVE_ECHO_PIN) == HIGH)
            ;
        travelTime = micros() - startTime;

        gUwave = travelTime / 58;
        //
        emit ThreadEnd(gUwave);
        sleep(1);
    }
}

int UWAVE_Sensor::getUwaveData()
{
    return _distance;
}

void UWAVE_Sensor::stop()
{
    m_stopFlag = true;
}
