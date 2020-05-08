//////////////  바닥의 라인트레이스 IR센서

#define pinLT1  A6 // 1번(왼쪽) IR센서 연결 핀
#define pinLT2  A7 // 2번(오른쪽) IR센서 연결 핀

// 색상에 따른 IR센서 측정값 샘플 (왼쪽,오른쪽)
//  로봇A: 흰색=(220,164), 회색=(576,541), 검정=(933,919)
//  로봇B: 흰색=(260,330), 회색=(600,640), 검정=(934,950) 

//////////////  메인 프로그램

void setup() {
  Serial.begin( 9600 ); // 시리얼 통신 (bps)
}

void loop() {
  int value1 = analogRead(pinLT1);  // IR1 값 읽기
  int value2 = analogRead(pinLT2);  // IR2 값 읽기

  Serial.print( value1 );
  Serial.print( ", " );
  Serial.print( value2 );
  Serial.println();
  delay(100);
}
