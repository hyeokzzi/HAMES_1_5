#include<Servo.h>

//motor
Servo servo;
int value=0;

//joystick
int Xin = A0;
int Yin = A1;
int KEYin =5;

//interrupt_button
int interruptPin = 2;
bool b_interrput = false;

void setup() {
  
 //led
 // pinMode(22, OUTPUT); 

 //motor
  servo.attach(8);
  servo.write(90);

  //joytstick
  pinMode(KEYin,INPUT_PULLUP);

  //button
  pinMode(interruptPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),Stop,CHANGE);

  Serial.begin(9600);
}
void loop() {

  //Serial communication
  if(Serial.available() > 0){
    char read_data = (char)Serial.read();
    if(read_data == '1') {
     servo.write(0);
     delay(5000);
     servo.write(90);
     delay(5000);
    }
    else if(read_data == 'G'){
      servo.write(0);
      delay(5000);
      servo.write(90);
      delay(1000);
    }
  }

  //joystick

  /*int Xvalue, Yvalue, ButtonVal;
  
  Xvalue= analogRead (Xin);                          
  Yvalue= analogRead (Yin);                           
  ButtonVal= digitalRead (KEYin);                   

  if(Yvalue > 510){
     servo.write(0);
     //delay(5000);
  }
  else if(Yvalue>490 && Yvalue <510){
     servo.write(90);
  }
  else if(Yvalue < 490){
     servo.write(180);
    // delay(5000);
  }*/
  if(b_interrput==false)
    servo.write(50);

 /* Serial.print("X = ");
  Serial.println (Xvalue, DEC);                       
  
  Serial.print ("Y = ");
  Serial.println (Yvalue, DEC); 
  if (ButtonVal== HIGH){                            
    Serial.println ("버튼 안눌림");
  }
  else{
    Serial.println ("버튼 눌림");
  }
    
  delay (500);*/

}

void Stop(){
  servo.write(90);
  b_interrput=true;
}
