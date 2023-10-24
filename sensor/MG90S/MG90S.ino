#include<Servo.h>
Servo servo;
int value=0;

void setup() {
  Serial.begin(9600);
 // pinMode(22, OUTPUT); 
  servo.attach(8);
  servo.write(90);
}
void loop() {
  if(Serial.available() > 0){
    char read_data = (char)Serial.read();
    if(read_data == '1') {
      /*digitalWrite(22,HIGH);
      delay(2000);
      digitalWrite(22, LOW);
      delay(1000);*/
     servo.write(0);
     delay(5000);
     servo.write(90);
     delay(5000);
     
    }
  }
}
