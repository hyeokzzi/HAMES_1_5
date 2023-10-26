#include<Servo.h>
#include <FastLED.h>

#define piezo 5
#define NUM_LEDS 10
#define DATA_PIN 3
#define CLOCK_PIN 13

Servo servo_cover;
Servo servo_window;
CRGB leds[NUM_LEDS];

void stop_c(){
  servo_cover.write(90);
}
void stop_w(){
  servo_window.write(90);
}
void open_c(){
  servo_cover.write(75);
}
void close_c(){
  servo_cover.write(165);
}
void open_w(){
  servo_window.write(75);
}
void close_w(){
  servo_window.write(165);
}
void buzzer_on(){
  tone(piezo,262);
}
void buzzer_off(){
   noTone(piezo);
}
void led_on(){
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Yellow;
  leds[2] = CRGB::Green;
  leds[3] = CRGB::Blue;
  leds[4] = CRGB::Purple;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Yellow;
  leds[7] = CRGB::Green;
  leds[8] = CRGB::Blue;
  leds[9] = CRGB::Purple;
  FastLED.show();
}

void led_off(){
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = CRGB::Black;
  leds[6] = CRGB::Black;
  leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
  leds[9] = CRGB::Black;
  FastLED.show();
}


void setup(){
  // put your setup code here, to run once:
  servo_window.attach(8);
  servo_cover.attach(9);
  pinMode(piezo,OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
 if(Serial.available() > 0){
   char read_data = (char)Serial.read();
    //window
    if(((read_data & 0b00100000) >> 5 ) == 0 ){
        stop_w();
    }
    else{
      if(((read_data & 0b00010000) >> 4 ) == 0){
          open_w();
      }
      else{
          close_w();
      }
    }
    //cover
    if(((read_data & 0b00001000) >> 3 ) == 0 ){
        stop_c();
    }
    else{
      if(((read_data & 0b00000100) >> 2 ) == 0){
          open_c();
      }
      else{
          close_c();
      }
    }
    
    //led
    if(((read_data & 0b00000010) >> 1 ) == 1){
        led_on(); 
    }
    else{
        led_off();
    }
    
    //buzzer
    if((read_data & 0b00000001) == 1){
        buzzer_on();
    }
    else{
        buzzer_off();
    }    
  } 
}
