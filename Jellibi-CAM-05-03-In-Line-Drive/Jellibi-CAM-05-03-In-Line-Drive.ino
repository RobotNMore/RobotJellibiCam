//////////////  바닥의 라인트레이스 IR센서

#define pinLT1  A6 // 1번(왼쪽) IR센서 연결 핀
#define pinLT2  A7 // 2번(오른쪽) IR센서 연결 핀

// WHITE=[0~190~410]... 560 ...[710~925~1023]=BLACK
#define LT_AJDUST       60  // 빨간색 픽시의 센서값은 +60 이동
#define LT_MAX_WHITE   410 + LT_AJDUST // 흰색으로 판단하는 최대값
#define LT_MID_VALUE   560 + LT_AJDUST // 흑백 판단 경계값(중간값)
#define LT_MIN_BLACK   710 + LT_AJDUST // 검은색으로 판단하는 최소값

////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

#define pinDIR1   7 // 1번(왼쪽)모터 방향 지정용 연결 핀
#define pinPWM1   5 // 1번(왼쪽)모터 속력 지정용 연결 핀

#define pinDIR2   8 // 2번(오른쪽)모터 방향 지정용 연결 핀
#define pinPWM2   6 // 2번(오른쪽)모터 속력 지정용 연결 핀

////////////////////  모터 회전 동작

#define FORWARD   0 // 전진 방향
#define BACKWARD  1 // 후진 방향

void  drive(int dir1, int power1, int dir2, int power2)
{
  boolean dirHighLow1, dirHighLow2;

  if(dir1 == FORWARD)  // 1번(왼쪽)모터 방향
    dirHighLow1 = HIGH;
  else // BACKWARD
    dirHighLow1 = LOW;
  
  if(dir2 == FORWARD)  // 2번(오른쪽)모터
    dirHighLow2 = LOW;
  else // BACKWARD
    dirHighLow2 = HIGH;

  digitalWrite(pinDIR1, dirHighLow1);
  analogWrite(pinPWM1, power1);

  digitalWrite(pinDIR2, dirHighLow2);
  analogWrite(pinPWM2, power2);
}

void  Forward( int power )  // 전진
{
  drive(FORWARD, power, FORWARD, power);
}

void  Backward( int power )  // 후진
{
  drive(BACKWARD, power, BACKWARD, power);
}

void  TurnLeft( int power )  // 좌회전
{
  drive(BACKWARD, power, FORWARD, power);
}

void  TurnRight( int power )  // 우회전
{
  drive(FORWARD, power, BACKWARD, power);
}

void Stop()  // 정지
{
  analogWrite(pinPWM1, 0);
  analogWrite(pinPWM2, 0);
}

////////////////////

void  setup()
{
  // 모터 제어 핀들을 모두 출력용으로 설정
  
  pinMode( pinDIR1, OUTPUT ); // 1번(왼쪽)모터 방향 핀
  pinMode( pinPWM1, OUTPUT ); // 1번(왼쪽)모터 속력 핀

  pinMode( pinDIR2, OUTPUT ); // 2번(오른쪽)모터 방향 핀
  pinMode( pinPWM2, OUTPUT ); // 2번(오른쪽)모터 속력 핀
}

int Power = 80;  // 기본 속력 (약간 느리게)

void  StopAndBackward() // 정지한 후 뒤로 물러나기
{
  Stop();
  delay( 30 );
  Backward( Power );
  delay( 700 );
}

void  loop()
{
  int v1 = analogRead( pinLT1 );
  int v2 = analogRead( pinLT2 );

  if( (LT_MIN_BLACK < v1) && (LT_MIN_BLACK < v2) )
  { // 양쪽 IR센서 모두 검정색을 감지한 경우
    StopAndBackward(); // 살짝 뒤로 물러나기
   
    if( v1 > v2 )  // 만약 왼쪽이 좀 더 검은색이면
      TurnRight( Power ); // 오른쪽으로 방향 전환
    else
      TurnLeft( Power );
    delay( 356 - Power ); // 
  }
  else if( v1 > LT_MIN_BLACK ) // 왼쪽(IR1)만 검정
  {
    TurnRight( Power ); // 우회전
    delay( 356 - Power );
  }
  else if( v2 > LT_MIN_BLACK ) // 오른쪽(IR2)만 검정
  {
    TurnLeft( Power ); // 좌회전
    delay( 356 - Power );
  }

  Forward( Power ); // 전진
}
