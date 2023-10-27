#include <wiringPi.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <deque>
#include <cmath>
using namespace std;

#define PIR_GPIO_IN 0
#define UWAVE_TRIG_PIN 1
#define UWAVE_ECHO_PIN 29

#define MAX_Q_SIZE 35
#define DIST_TH 1

deque<int> Q;

void setupPin();
int readUWaveData();
uint8_t readPirData();
double calcStdev();

int main(void) // writeBuzzerData
{
	if (wiringPiSetup() == -1) // wPi
		exit(1);

	uint8_t detected = 0;
	uint8_t pre_detected = 0;
	uint8_t tmp_detected = 0;

	int dist = 0;
	int pre_dist = 0;

	bool buzzer = 0;

	setupPin();

	while (1)
	{
		delay(100);

		detected = readPirData();
		dist = readUWaveData();

        printf("\nPIR state = %d\n", detected);
		printf("Distance: %dcm\n", dist);

		if (Q.size() == MAX_Q_SIZE) Q.pop_front();
		Q.push_back(dist);

		tmp_detected = detected;

		if ((pre_detected == 0) && (tmp_detected == 1))
		{
			printf("~~~ Detected ~~~\n");

			double stdev = calcStdev();
			printf("stdev = %f\n", stdev);

			if (stdev > DIST_TH)
			{
				printf("--------------------------- !!! WARNING !!! ---------------------------\n");
				buzzer = 1;
			}
			else
			{
				buzzer = 0;
			}
		}

		pre_detected = tmp_detected;
		pre_dist = dist;
	}

	return 0;
}

void setupPin()
{
	pinMode(PIR_GPIO_IN, INPUT);
	pinMode(UWAVE_TRIG_PIN, OUTPUT);
	pinMode(UWAVE_ECHO_PIN, INPUT);
}

int readUWaveData()
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

double calcStdev()
{
	// printf("calcStdev..\n");
	// printf("Q.size() = %d\n", Q.size());
	for (int i = 0; i < Q.size(); i++) printf("%d ", Q[i]);
	printf("\n");

    double sum1 = 0;
    double sum2 = 0;
    double avg = 0;
    double var = 0;
    double stdev = 0;

    for (int i = 0; i < Q.size(); i++)
    {
        sum1 += Q[i];
    }
    avg = sum1 / static_cast<double>(Q.size());

    for (int i = 0; i < Q.size(); i++)
    {
        sum2 += pow((Q[i] - avg), 2);
    }
    var = sum2 / static_cast<double>(Q.size() - 1);
    stdev = sqrt(var);

    return stdev;
}
