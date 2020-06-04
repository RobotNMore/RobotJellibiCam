//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

#include <Pixy2.h>
#include <PIDLoop.h>

#define MAX_SPEED     180 // 최고 속력
#define SPEED_FAST    90  // 빠른 속력
#define SPEED_SLOW    50  // 느린 속력

#define X_CENTER      (pixy.frameWidth / 2) // 화면 가로 중앙 좌표

Pixy2   pixy;
PIDLoop headingLoop(1000, 0, 0, false);

////////////////////  모터 1번(왼쪽)과 2번(오른쪽)

#define pinDIR1   7 // 1번(왼쪽)모터 방향 지정용 연결 핀
#define pinPWM1   5 // 1번(왼쪽)모터 속력 지정용 연결 핀

#define pinDIR2   8 // 2번(오른쪽)모터 방향 지정용 연결 핀
#define pinPWM2   6 // 2번(오른쪽)모터 속력 지정용 연결 핀

////////////////////  모터 회전 동작

#define FORWARD   0 // 전진 방향
#define BACKWARD  1 // 후진 방향

void  Drive2( int32_t deltaLeft, int32_t deltaRight )
{
  boolean dirHighLow1, dirHighLow2;

  if(deltaLeft >= 0)  // 1번(왼쪽)모터 방향
    dirHighLow1 = HIGH;
  else // BACKWARD
    dirHighLow1 = LOW;
  
  if(deltaRight >= 0)  // 2번(오른쪽)모터
    dirHighLow2 = LOW;
  else // BACKWARD
    dirHighLow2 = HIGH;

  int spd1 = abs(deltaLeft);
  int spd2 = abs(deltaRight);

  if(spd1 > MAX_SPEED)  spd1 = MAX_SPEED;
  if(spd2 > MAX_SPEED)  spd2 = MAX_SPEED;
  
  digitalWrite(pinDIR1, dirHighLow1);
  analogWrite(pinPWM1, spd1);

  digitalWrite(pinDIR2, dirHighLow2);
  analogWrite(pinPWM2, spd2);
}

void Stop()  // 정지
{
  analogWrite(pinPWM1, 0);
  analogWrite(pinPWM2, 0);
}

////////////////////////////////////////  setup()

void setup() 
{
  // 모터 제어 핀들을 모두 출력용으로 설정
  
  pinMode( pinDIR1, OUTPUT ); // 1번(왼쪽)모터 방향 핀
  pinMode( pinPWM1, OUTPUT ); // 1번(왼쪽)모터 속력 핀

  pinMode( pinDIR2, OUTPUT ); // 2번(오른쪽)모터 방향 핀
  pinMode( pinPWM2, OUTPUT ); // 2번(오른쪽)모터 속력 핀
  
  Stop(); // 정지

  pixy.init();
  
  pixy.setLamp(1, 1);        // 위/아래 조명 LED 모두 켜기
  pixy.changeProg("line");   // "line_tracking" 모드 설정
  //pixy.setServos(500, 1000); // Pan= 정면중앙, Tilt= 가장아래
  
//  pixy.setServos(0, 0); // Pan= 우측, Tilt= 가장아래
//  delay( 2000 );
//  pixy.setServos(500, 500); // Pan= 정면, Tilt= 중간높이
//  delay( 2000 );
//  pixy.setServos(1000, 1000); // Pan= 좌측, Tilt= 가장위
//  delay( 2000 );
  pixy.setServos(600, 500); // Pan= 정면, Tilt= 중간높이
  delay( 100 );
  pixy.setServos(550, 250); // Pan= 정면, Tilt= 중간높이
  delay( 100 );
  pixy.setServos(500, 0); // Pan= 정면, Tilt= 가장아래
  delay( 100 );
}

////////////////////////////  loop()

void loop()
{
  // Pixy로 부터 최신 인식 데이터(벡터/교차로/바코드)를 가져온다.
  int res = pixy.line.getMainFeatures();  // Pixy로 부터 최신 데이터를 가져온다.
  
  if( res <= 0 ) // Error(<0) 이거나 또는 인식된 내용이 없으면(0) 정지
  {
    Stop();
  }
  
  else if( res & LINE_VECTOR ) // 벡터 정보에 라인이 감지됨
  {
    // 앞으로 나아가는 벡터의 끝인 m_x1에 대한 변이값 계산
    int error = (int32_t) X_CENTER - (int32_t) pixy.line.vectors->m_x1;
    headingLoop.update( error );  // heading error에 대해 PID 계산 반영

    // heading을 왼쪽과 오른쪽 속력 성분으로 분리
    int left = -headingLoop.m_command;
    int right = headingLoop.m_command;

    // 만약 벡터가 전진(화살표가 위쪽 방향인 상태)이면 정상
    if( pixy.line.vectors->m_y0 > pixy.line.vectors->m_y1 )
    {
      if( pixy.line.vectors->m_flags & LINE_FLAG_INTERSECTION_PRESENT )
      { // 만약 교차로가 감지되면, 그냥 지나치지 않도록 속도를 느리게 설정
        left += SPEED_SLOW;
        right += SPEED_SLOW;
      }
      else // 만약 교차로가 없으면, 빠르게 진행하도록 설정
      {
        left += SPEED_FAST;
        right += SPEED_FAST;
      }    
    }
    else  // 만약 벡터가 아래쪽을 향하면, 후진하도록 설정
    {
      left -= SPEED_SLOW;
      right -= SPEED_SLOW;  
    }
    
    Drive2( left, right );  // 실제 주행속도(모터회전) 조정
  }
}
