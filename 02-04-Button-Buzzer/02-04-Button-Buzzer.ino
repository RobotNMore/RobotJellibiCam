#define PIN_BUZZER    3 // 부저 핀 번호
#define PIN_BTN_RIGHT 4 // 오른쪽 버튼 핀 번호

void  setup() {
  pinMode(PIN_BUZZER, OUTPUT);   // 출력 핀으로 설정  
  pinMode(PIN_BTN_RIGHT, INPUT); // 입력 핀으로 설정
  
  noTone(PIN_BUZZER);  // 스피커 끄기(음소거)
}

void  loop() {
  if(digitalRead(PIN_BTN_RIGHT) == 0) // 버튼 눌림?
  {
    tone( PIN_BUZZER, 261 );  // "도" 음 연주
    delay( 500 );
  }

  noTone( PIN_BUZZER );  // 음소거(mute)
  delay( 10 );  // 10 msec 후에 다시 눌림 체크
}
