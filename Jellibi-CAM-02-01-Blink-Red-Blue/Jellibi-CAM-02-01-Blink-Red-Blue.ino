#define pinLedRed   10  // 빨간색 LED Pin 번호
#define pinLedBlue  11  // 파란색 LED Pin 번호

void setup() {
  pinMode(pinLedRed, OUTPUT);  // 출력 핀으로 설정
  pinMode(pinLedBlue, OUTPUT); // 출력 핀으로 설정
}

void loop() {
  digitalWrite(pinLedRed, HIGH);  // 빨간색 LED 켜기
  digitalWrite(pinLedBlue, LOW);  // 파란색 LED 끄기
  delay(1000);  // 1초 대기
  
  digitalWrite(pinLedRed, LOW);   // 빨간색 LED 끄기
  digitalWrite(pinLedBlue, HIGH); // 파란색 LED 켜기
  delay(1000);  // 1초 대기
}
