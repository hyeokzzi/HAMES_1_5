#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define PIR_GPIO_IN 0
// #define PIR_GPIO_OUT 3

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
	int distance;
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
	return distance;
}

uint8_t readPirData()
{
	uint8_t state = digitalRead(PIR_GPIO_IN);
	return state;
}

int main(void)
{
	if (wiringPiSetup() == -1) // wPi
		exit(1);

	uint8_t detected = 0;
	uint8_t pre_detected = 0;
	uint8_t tmp_detected = 0;

	int dist = 0;
	int pre_dist = 0;
	
	setupPin();
	while (1)
	{
		delay(100);

		detected = readPirData();
		printf("PIR state = %d\n", detected);

		dist = readWaveData();
		printf("Distance: %dcm\n\n", dist);

		tmp_detected = detected;

		// if ((pre_detected == 0) && (tmp_detected == 1))
		if (detected == 1)
		{
			printf("~~~ Detected ~~~\n");
			int diff = dist - pre_dist;
			// printf("diff = %d\n", diff);
			if (diff > 5 || diff < -5) printf("--------------------------- diff > 5 ---------------------------\n");
		}

		int diff = dist - pre_dist;
		printf("diff = %d\n", diff);
		// if (diff > 5)
		// {
		// 	printf("diff > 5\n");
		// 	if ((pre_detected == 0) && (tmp_detected == 1))
		// 	{
		// 		printf("~~~ Detected ~~~\n");
		// 	}
		// }

		pre_detected = tmp_detected;
		pre_dist = dist;
	}

	return 0;
}
