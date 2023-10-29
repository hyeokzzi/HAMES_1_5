#ifndef GPIO_H
#define GPIO_H

// cover open/close button
#define OPEN_BTN_GPIO 23
#define CLOSE_BTN_GPIO 24

// PIR sensor
#define PIR_GPIO_IN 17

// ADC (rain, joystick sensor)
#define CS_MCP3208 8 // BCM 8
#define JOYSTICK_SW 5

// ultrasonic wave sensor
#define UWAVE_TRIG_PIN 18   // BCM
#define UWAVE_ECHO_PIN 21   // BCM
//#define UWAVE_TRIG_PIN 1  // wiringPi
//#define UWAVE_ECHO_PIN 29 // wiringPi

#endif // GPIO_H
