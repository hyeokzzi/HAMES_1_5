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
