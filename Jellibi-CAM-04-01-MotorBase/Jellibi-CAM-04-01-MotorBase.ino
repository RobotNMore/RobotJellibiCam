////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

#define pinDIR1   7 // 1번(왼쪽)모터 방향 지정용 연결 핀
#define pinPWM1   5 // 1번(왼쪽)모터 속력 지정용 연결 핀

#define pinDIR2   8 // 2번(오른쪽)모터 방향 지정용 연결 핀
#define pinPWM2   6 // 2번(오른쪽)모터 속력 지정용 연결 핀

////////////////////  모터 회전 동작

#define FORWARD   0 // 전진 방향
#define BACKWARD  1 // 후진 방향

void move1(int dir, int power)  // 1번(왼쪽)모터 구동
{
  if(dir == FORWARD)
    digitalWrite(pinDIR1, HIGH);
  else
    digitalWrite(pinDIR1, LOW);
      
  analogWrite(pinPWM1, power);
}

void move2(int dir, int power)  // 2번(오른쪽)모터 구동
{
  if(dir == FORWARD)
    digitalWrite(pinDIR2, LOW);
  else
    digitalWrite(pinDIR2, HIGH);
      
  analogWrite(pinPWM2, power);
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
  move1(FORWARD, Power); // 1번(왼쪽)모터 전진
  delay( 1000 );
  analogWrite(pinPWM1, 0); // 정지
  delay( 1000 );
  
  move1(BACKWARD, Power); // 후진
  delay( 1000 );
  analogWrite(pinPWM1, 0); // 정지
  delay( 1000 );
  
  move2(FORWARD, Power); // 2번(오른쪽)모터 전진
  delay( 1000 );
  analogWrite(pinPWM2, 0); // 정지
  delay( 1000 );

  move2(BACKWARD, Power); // 후진
  delay( 1000 );
  analogWrite(pinPWM2, 0); // 정지
  delay( 1000 );
}
