int piezo = 5;

void setup() {  
  pinMode(piezo, OUTPUT);  
}

void loop() {  
  tone(piezo, 262); //도
  delay(500);
  noTone(piezo);
}
