////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

#define pinDIR1   7 // 1번(왼쪽)모터 방향 지정용 연결 핀
#define pinPWM1   5 // 1번(왼쪽)모터 속력 지정용 연결 핀

#define pinDIR2   8 // 2번(오른쪽)모터 방향 지정용 연결 핀
#define pinPWM2   6 // 2번(오른쪽)모터 속력 지정용 연결 핀

// 양쪽 모터 성능차이 보정 (성능이 좋은 쪽의 비율을 줄여서 맞춤)
// 아래 비율은 왼쪽 모터의 성능이 약간 떨어지는 경우 조정값임
float Power1Ratio = 1.00; // 왼쪽 모터 속도 보정비율 (최대= 1.0)
float Power2Ratio = 0.96; // 오른쪽 모터 속도 보정비율 (최대= 1.0)

////////////////////  모터 회전 동작

#define FORWARD   0 // 전진 방향
#define BAKWARD   1 // 후진 방향

void  drive(int dir1, int power1, int dir2, int power2)
{
  boolean dirHighLow1, dirHighLow2;
  int     adjPower1, adjPower2;

  if(dir1 == FORWARD)  // 1번(왼쪽)모터 방향
    dirHighLow1 = HIGH;
  else // BACKWARD
    dirHighLow1 = LOW;

  adjPower1 = power1 * Power1Ratio; // 왼쪽모터 성능 조정
  
  if(dir2 == FORWARD)  // 2번(오른쪽)모터
    dirHighLow2 = LOW;
  else // BACKWARD
    dirHighLow2 = HIGH;

  adjPower2 = power2 * Power2Ratio; // 오른쪽모터 성능 조정

  digitalWrite(pinDIR1, dirHighLow1); // 왼쪽모터 회전 방향
  analogWrite(pinPWM1, adjPower1); // 조정된 왼쪽모터 속력

  digitalWrite(pinDIR2, dirHighLow2); // 오른쪽모터 회전 방향
  analogWrite(pinPWM2, adjPower2); // 조정된 오른쪽모터 속력
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
  delay( 2000 ); 
  Stop();
  delay( 1000 );

  Backward( Power );  // 후진
  delay( 2000 );
  Stop();
  delay( 1000 );
}
