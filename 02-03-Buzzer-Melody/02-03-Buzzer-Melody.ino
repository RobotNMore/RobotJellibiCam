#define pinBuzzer  3 // 부저 핀 번호

void  setup() {
  pinMode( pinBuzzer, OUTPUT ); // 출력 핀으로 설정  
  noTone( pinBuzzer );  // 스피커 끄기(음소거)
}

void  loop() {
  tone( pinBuzzer, 262 );  // 도(4옥타브 C)
  delay( 500 );
  tone( pinBuzzer, 294 );  // 레(4옥타브 D)
  delay( 500 );
  tone( pinBuzzer, 330 );  // 미(4옥타브 E)
  delay( 500 );
  tone( pinBuzzer, 349 );  // 파(4옥타브 F)
  delay( 500 );
  tone( pinBuzzer, 392 );  // 솔(4옥타브 G)
  delay( 500 );
  noTone( pinBuzzer );     // 음소거(mute)
  delay( 5000 );
}
