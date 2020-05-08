#define PIN_BTN_RIGHT   4 // 오른쪽 버튼 핀 번호

void  setup() {
  pinMode(PIN_BTN_RIGHT, INPUT); // 입력 핀으로 설정
  Serial.begin( 9600 ); // 시리얼 통신 속도 설정
}

void  loop() {
  int value = digitalRead(PIN_BTN_RIGHT); // 값 읽기
  
  Serial.print( "V= " );   // 따옴표 안의 내용 출력
  Serial.println( value ); // 읽은 값 출력 (줄넘김)
  
  delay( 100 );  // 0.1초 후에 다시 버튼 눌림값 체크
}
