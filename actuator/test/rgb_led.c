#define LED_B 3       // B의 핀 번호 3
#define LED_G 4       // G의 핀 번호 4
#define LED_R 5       // R의 핀 번호 5
 
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
}
 
void loop() {
  turnOffAll();                  // LED 다 끕니다.
  
  digitalWrite(LED_B, HIGH);     // 파란 불 켜기
  delay(2000);                   // 3초간 유지
  turnOffAll();                  // 불 다 끄기
  
  digitalWrite(LED_G, HIGH);     // 초록 불 켜기
  delay(2000);                   // 2초간 유지
  turnOffAll();                  // 불 다 끄기
 
 digitalWrite(LED_R, HIGH);      // 빨간 불 켜기
  delay(2000);                   // 2초간 유지
  turnOffAll();                  // 불 다 끄기
}
 
void turnOffAll() {              // turnOffAll 함수 정의
  digitalWrite(LED_B, LOW);      // 파란 불 끄기
  digitalWrite(LED_G, LOW);      // 초록 불 끄기
  digitalWrite(LED_R, LOW);      // 빨간 불 끄기
}

// ref: https://eduino.kr/product/detail.html?product_no=69&cate_no=55&display_group=1