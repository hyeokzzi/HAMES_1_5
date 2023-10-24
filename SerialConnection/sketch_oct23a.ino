<<<<<<< HEAD
void setup() {
  Serial.begin(9600);
  pinMode(22, OUTPUT); 
}
void loop() {
  if(Serial.available() > 0){
    char read_data = (char)Serial.read();
    if(read_data == '1') {
      digitalWrite(22,HIGH);
      delay(2000);
      digitalWrite(22, LOW);
      delay(1000);
    }
  }
}
=======
void setup() {
  Serial.begin(9600);
  pinMode(22, OUTPUT); 
}
void loop() {
  if(Serial.available() > 0){
    char read_data = (char)Serial.read();
    if(read_data == '1') {
      digitalWrite(22,HIGH);
      delay(2000);
      digitalWrite(22, LOW);
      delay(1000);
    }
  }
}
>>>>>>> 1c149415d8c739775c60cc6123e52728ed9a84a7
