//////////////  바닥의 라인트레이스 IR센서

#define pinLT1  A6 // 1번(왼쪽) IR센서 연결 핀
#define pinLT2  A7 // 2번(오른쪽) IR센서 연결 핀

// 색상 판단: White=[0..410] .. 560 .. [710..1023]=Black
#define LT_AJDUST       60  // 현재 젤리비의 센서 측정 조정값
#define LT_MAX_WHITE   410 + LT_AJDUST // 흰색으로 판단하는 최대값
#define LT_MID_VALUE   560 + LT_AJDUST // 흑백 판단 경계값(중간값)
#define LT_MIN_BLACK   710 + LT_AJDUST // 검은색으로 판단하는 최소값

// 연속 회전 횟수를 4단계까지 나누어 부드럽게 회전
#define MAX_TURN_STEP1    1  // 연속 좌/우 회전 감지 카운터
#define MAX_TURN_STEP2    2  // (속력을 1/4 씩 추가로 감속)
#define MAX_TURN_STEP3    3  //
#define MAX_TURN_STEP4    4  //

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

int Power = 100;  // 기본 속력 (보통 빠르기)

int LeftTurn = 0;   // 왼쪽 연속회전 누적횟수
int RightTurn = 0;  // 오른쪽 연속회전 누적횟수

void  loop()
{
  int v1 = analogRead( pinLT1 );  // 왼쪽 IR 센서값 읽기
  int v2 = analogRead( pinLT2 );  // 오른쪽 IR 센서값 읽기

  if( (LT_MIN_BLACK < v1) && (LT_MIN_BLACK < v2) )
  { // 양쪽 IR센서 모두 검정색을 감지한 경우, (ex) 검정 교차선
    // 1초 정지한 후에 다시 전진 (0.1초 전진)
    Stop();
    delay( 1000 );
    Forward( Power );
    delay( 100 );
    
    LeftTurn = 0;  // 왼쪽 연속회전 누적횟수 초기화
    RightTurn = 0; // 오른쪽 연속회전 누적횟수 초기화
  }
  else if( v1 > LT_MIN_BLACK )  // 왼쪽만 검정, 좌회전
  {
    if ( LeftTurn < MAX_TURN_STEP1 ) // 왼쪽 회전 시작
      drive(FORWARD, Power * 4.0 / 5, FORWARD, Power);
    else if ( LeftTurn < MAX_TURN_STEP2 )
      drive(FORWARD, Power * 3.0 / 4, FORWARD, Power);
    else if ( LeftTurn < MAX_TURN_STEP3 )
      drive(FORWARD, Power / 2, FORWARD, Power);
    else // 연속으로 좌회전이 많이 누적되는 경우
      drive(FORWARD, 0, FORWARD, Power / 2);

    LeftTurn++;    // 왼쪽 연속회전 누적횟수 증가
    RightTurn = 0; // 오른쪽 연속회전 누적횟수 초기화
  }
  else if( v2 > LT_MIN_BLACK )  // 오른쪽만 검정,우회전
  {    
    if ( RightTurn < MAX_TURN_STEP1 ) // 오른쪽 회전 시작
      drive(FORWARD, Power, FORWARD, Power * 4.0 / 5);
    else if ( RightTurn < MAX_TURN_STEP2 )
      drive(FORWARD, Power, FORWARD, Power * 3.0 / 4);
    else if ( RightTurn < MAX_TURN_STEP3 )
      drive(FORWARD, Power, FORWARD, Power / 2);
    else // 연속으로 우회전이 많이 누적되는 경우
      drive(FORWARD, Power / 2, FORWARD, 0);
      
    RightTurn++;  // 왼쪽 연속회전 누적횟수 초기화
    LeftTurn = 0; // 오른쪽 연속회전 누적횟수 증가
  }
  else  // 양쪽 모두 흰색, 계속 전진
  {
    Forward( Power );
    
    LeftTurn = 0;  // 왼쪽 연속회전 누적횟수 초기화
    RightTurn = 0; // 오른쪽 연속회전 누적횟수 초기화
  }
}
