#include<Servo.h>
Servo servo_cover;
Servo servo_window;
volatile char data[3];

int bnt_c = 4;
int bnt_o = 5;

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

void setup(){
  // put your setup code here, to run once:
  servo_window.attach(8);
  servo_cover.attach(9);
  pinMode(bnt_c,INPUT_PULLUP);
  pinMode(bnt_o,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
 if(Serial.available() > 0){
    byte len = Serial.readBytes(data, 3);
    if(data[0] == '0'){
      if(bnt_o == 1)
        open_w();
      else if(bnt_c == 1){
        open_c();
        while(bnt_o != 1){
          delay(1);
        }
        stop_c();
        open_w();
      }     
    }
    else if(data[0] == '1'){
       close_w();
    }
    else if(data[0] == '2'){
       stop_w();
    }
    else if(data[0] == '3'){
      open_c();
      while(bnt_o !=1){
        delay(1);
      }
      stop_c();   
    }
    else if(data[0] == '4'){
      close_c();
       while(bnt_c !=1){
        delay(1);
      }
      stop_c();  
    }   
 } 
}
