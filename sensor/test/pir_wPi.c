#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GPIOIN 0  // gpio 17
#define GPIOOUT 3 // gpio 22

void read_data()
{
	uint8_t State;
	pinMode(GPIOIN, INPUT);
	pinMode(GPIOOUT, OUTPUT);
	printf("Sensor start\n");

	while (1)
	{
		delay(1000);
		State = digitalRead(GPIOIN);
		printf("state = %d\n", State);
		digitalWrite(GPIOOUT, State);
	}
}

int main(void)
{
	if (wiringPiSetup() == -1) // wPi
		exit(1);

	read_data();
	return (0);
}