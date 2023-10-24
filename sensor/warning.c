#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PIR_GPIO_IN 0
#define PIR_GPIO_OUT 3

#define UWAVE_TRIG_PIN 1
#define UWAVE_ECHO_PIN 29

void setupPin()
{
    pinMode(PIR_GPIO_IN, INPUT);
    pinMode(UWAVE_TRIG_PIN, OUTPUT);
    pinMode(UWAVE_ECHO_PIN, INPUT);
}

int readWaveData()
{
    int distance = 0;
    int pulse = 0;

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

    distance = travelTime / 58;

    delay(200);

    return distance;
}

uint8_t readPirData()
{
    delay(1000);
    return digitalRead(PIR_GPIO_IN);
}

int main(void)
{
	if (wiringPiSetup() == -1) // wPi
		exit(1);

    uint8_t state;
    int distance;

    setupPin();
    while (1)
    {
        state = readPirData();
        printf("PIR state = %d\n", state);

        distance = readWaveData();
        printf("Distance: %dcm\n\n", distance);
    }

	return 0;
}