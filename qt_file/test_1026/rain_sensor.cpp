#include "rain_sensor.h"
#include "mainwindow.h"

extern int gRain;
extern int gYsig;

int read_mcp3208_adc();
Rain_Sensor::Rain_Sensor(QObject *parent) : QThread(parent)
{
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
    pinMode(CS_MCP3208, OUTPUT);
}
void Rain_Sensor::run()
{
    unsigned char buff[3] = {0x01, 0xa0, 0x00};
    int adcValue = 0;

    buff[0] = (0x01 & 0xff);
    buff[1] = (0xa0 & 0xff) ;
    buff[2] = 0x00;

    while(!m_stopFlag)
    {
        // Insert Your Code

        buff[0] = (0x01 & 0xff);
        buff[1] = (0xa0 & 0xff) ;
        buff[2] = 0x00;

        digitalWrite(CS_MCP3208, 0);
        wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

        buff[1] = 0x0f & buff[1];
//        adcValue = (buff[1] << 8 ) | buff[2];
        gRain = (buff[1] << 8 ) | buff[2];

        digitalWrite(CS_MCP3208, 1);

        buff[0] = (0x01 & 0xff);
        buff[1] = (0xe0 & 0xff) ;
        buff[2] = 0x00;

        digitalWrite(CS_MCP3208, 0);
        wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

        buff[1] = 0x0f & buff[1];
//        adcValue = (buff[1] << 8 ) | buff[2];
        gYsig = (buff[1] << 8 ) | buff[2];

        digitalWrite(CS_MCP3208, 1);
        //
        emit ThreadEnd(gYsig);
        sleep(1);
    }
}

void Rain_Sensor::stop()
{
    m_stopFlag = true;
}
