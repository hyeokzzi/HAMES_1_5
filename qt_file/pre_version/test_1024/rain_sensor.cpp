#include "rain_sensor.h"
#include "mainwindow.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

int read_mcp3208_adc();
Rain_Sensor::Rain_Sensor(QObject *parent) : QThread(parent)
{
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
    pinMode(CS_MCP3208, OUTPUT);
}
void Rain_Sensor::run()
{
    int adcValue_light = 0;

    while(!m_stopFlag)
    {
        // Insert Your Code
        adcValue_light = read_mcp3208_adc();
        //
//        printf("detect rain!\n");
//        emit ThreadEnd(adcValue_light);
        sleep(1);
    }
}

void Rain_Sensor::stop()
{
    m_stopFlag = true;
}

int read_mcp3208_adc()
{
    unsigned char buff[3];
    int adcValue = 0;

    buff[0] = (0x01 & 0xff);
    buff[1] = (0xa0 & 0xff) ;
    buff[2] = 0x00;

    digitalWrite(CS_MCP3208, 0);
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

    buff[1] = 0x0f & buff[1];
    adcValue = (buff[1] << 8 ) | buff[2];

    digitalWrite(CS_MCP3208, 1);

    return adcValue;
}
