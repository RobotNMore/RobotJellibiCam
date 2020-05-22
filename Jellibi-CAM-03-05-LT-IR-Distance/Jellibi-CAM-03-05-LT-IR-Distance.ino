//////////////  바닥의 라인트레이스 IR센서

#define pinLT1  A6 // 1번(왼쪽) IR센서 연결 핀

//////////////  메인 프로그램

void setup() {
  Serial.begin( 9600 ); // 시리얼 통신 (bps)
}

void loop() {
  int value1 = analogRead(pinLT1);  // IR1 값 읽기

  Serial.print( "IR값= " ); // IR센서로 반사되는 값을 읽음
  Serial.print( value1 );   // 색상이나 반사면 상태에 의존

  if( value1 < 300 )
    Serial.println( ", 0.5 Cm 이내" );
  else if( value1 < 700 )
    Serial.println( ", 1 Cm 이내" );
  else if( value1 < 850 )
    Serial.println( ", 2 Cm 이내" );
  else if( value1 < 950 )
    Serial.println( ", 5 Cm 이내" );
  else if( value1 < 1000 )
    Serial.println( ", 10 Cm 이내" );
  else
    Serial.println( ", 멀거나 없음" );

  delay( 1000 );
}
