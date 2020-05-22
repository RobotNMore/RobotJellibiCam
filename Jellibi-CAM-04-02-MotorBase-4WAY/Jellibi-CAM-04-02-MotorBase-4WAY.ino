////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

#define pinDIR1   7 // 1번(왼쪽)모터 방향 지정용 연결 핀
#define pinPWM1   5 // 1번(왼쪽)모터 속력 지정용 연결 핀

#define pinDIR2   8 // 2번(오른쪽)모터 방향 지정용 연결 핀
#define pinPWM2   6 // 2번(오른쪽)모터 속력 지정용 연결 핀

////////////////////  모터 회전 동작

#define FORWARD   0 // 전진 방향
#define BAKWARD   1 // 후진 방향

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

void  Forward(int power)  // 전진
{
  drive(FORWARD, power, FORWARD, power);
}

void  Backward(int power)  // 후진
{
  drive(BAKWARD, power, BAKWARD, power);
}

void  TurnLeft(int power)  // 좌회전
{
  drive(BAKWARD, power, FORWARD, power);
}

void  TurnRight(int power)  // 우회전
{
  drive(FORWARD, power, BAKWARD, power);
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

int Power = 100;  // 기본 속력

void  loop()
{
  Forward( Power );  // 전진
  delay( 1000 ); 
  Stop();
  delay( 1000 );

  Backward( Power );  // 후진
  delay( 1000 );
  Stop();
  delay( 1000 );
  
  TurnLeft( Power );  // 좌회전
  delay( 1000 ); 
  Stop();
  delay( 1000 );

  TurnRight( Power );  // 우회전
  delay( 1000 );
  Stop();
  delay( 1000 );
  }
