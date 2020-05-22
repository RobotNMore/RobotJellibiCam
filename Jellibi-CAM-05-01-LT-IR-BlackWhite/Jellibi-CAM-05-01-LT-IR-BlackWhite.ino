//////////////  바닥의 라인트레이스 IR센서

#define pinLT1  A6 // 1번(왼쪽) IR센서 연결 핀
#define pinLT2  A7 // 2번(오른쪽) IR센서 연결 핀

// 색상 판단: White=[0..410] .. 560 .. [710..1023]=Black
#define LT_AJDUST       60  // 현재 젤리비의 센서 측정 조정값
#define LT_MAX_WHITE   410 + LT_AJDUST // 흰색으로 판단하는 최대값
#define LT_MID_VALUE   560 + LT_AJDUST // 흑백 판단 경계값(중간값)
#define LT_MIN_BLACK   710 + LT_AJDUST // 검은색으로 판단하는 최소값

//////////////  메인 프로그램

void setup() {
  Serial.begin( 9600 ); // 시리얼 통신 (bps)
}

void loop() {
  int v1 = analogRead(pinLT1);  // IR1(왼쪽) 값 읽기
  int v2 = analogRead(pinLT2);  // IR2(오른쪽) 값 읽기

  if( (LT_MIN_BLACK < v1) && (LT_MIN_BLACK < v2) )
    Serial.println( "[검은색] [검은색]" );
  else if( v1 > LT_MIN_BLACK )
    Serial.println( "[검은색] [흰  색]" );
  else if( v2 > LT_MIN_BLACK )
    Serial.println( "[흰  색] [검은색]" );
  else
    Serial.println( "[흰  색] [흰  색]" );
  
  delay(100);
}
