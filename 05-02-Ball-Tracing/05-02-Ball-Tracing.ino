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

#include <JellibiButton.h>
JellibiButton _downButton;

#define MAX_TRANSLATE_VELOCITY  225 // 로봇 이동속도 제한

Pixy2 pixy;

PIDLoop panLoop(-200, 0, -200, true);
PIDLoop tiltLoop(200, 0, 200, true);

PIDLoop turnLoop(400, 0, 400, false);
PIDLoop gobackLoop(400, 0, 400, false);

//////////////  버튼 및 부저

#define pinBuzzer   3 // 부저 핀 번호

#define pinBtnRight 4 // 오른쪽 버튼 핀 번호
#define pinBtnDown  A1 // Down 버튼 핀 번호

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

  digitalWrite(pinDIR1, dirHighLow1);
  analogWrite(pinPWM1, abs(deltaLeft));

  digitalWrite(pinDIR2, dirHighLow2);
  analogWrite(pinPWM2, abs(deltaRight));
}

void Stop()  // 정지
{
  analogWrite(pinPWM1, 0);
  analogWrite(pinPWM2, 0);
}

//////////////////////////

int j = 0;

void MoveHead()
{
  if (j <= 20) {
    int angle = map(j, 0, 20, 400, 100);
    pixy.setServos(angle, 200);
    delay(20);
    j++;
  }
  else if (j <= 60) {
    int angle = map(j, 0, 40, 100, 700);
    pixy.setServos(angle, 200);
    delay(20);
    j++;
  }
  else {
    int angle = map(j, 0, 20, 700, 400);
    pixy.setServos(angle, 200);
    j++;
  }
  
  if (j > 80) j = 0;
}

////////////////////////////////////////  setup()

void setup()
{
  // 모터 제어 핀들을 모두 출력용으로 설정
  
  pinMode( pinDIR1, OUTPUT ); // 1번(왼쪽)모터 방향 핀
  pinMode( pinPWM1, OUTPUT ); // 1번(왼쪽)모터 속력 핀

  pinMode( pinDIR2, OUTPUT ); // 2번(오른쪽)모터 방향 핀
  pinMode( pinPWM2, OUTPUT ); // 2번(오른쪽)모터 속력 핀

  pinMode( pinBuzzer, OUTPUT );  

  _downButton.Init( A1, false );
  pinMode( A1, INPUT );
  
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  Stop();

  pixy.init();
  pixy.changeProg("color_connected_components"); // cf) "line_tracking"
  
  pixy.setServos(420, 200); // 팬/틸트 서보를 중앙 위치로
}


// 적어도 0.5초(30 프레임) 이상 경과한 인식된 사물의 블록(block[0])이
// 있으면 해당 인덱스를 리턴하고, 없으면 -1을 리턴
int16_t acquireBlock()
{
  if( pixy.ccc.numBlocks  &&  pixy.ccc.blocks[0].m_age > 30 )
    return  pixy.ccc.blocks[0].m_index;

  return -1;
}


int mm_signature = 0;

// 현재 프레임의 모든 물체인식 블록 중에서
// 주어진 인덱스의 물체 시그니처와 블록 찾기
Block *trackBlock( uint8_t index )
{
  uint8_t i;

  for( i=0; i < pixy.ccc.numBlocks; i++ )
  {
    if( index == pixy.ccc.blocks[i].m_index )
    {
      mm_signature = pixy.ccc.blocks[i].m_signature;
      return &pixy.ccc.blocks[i];
    }
  }

  return NULL;
}


void  StopAndResetMove() // 정지하고, 주행동작 초기화
{
  Stop();
  
  turnLoop.reset();
  gobackLoop.reset();
}


////////////////////////////  loop()

bool bDrive = 0;

void loop()
{
  static int16_t index = -1;
  int32_t panOffset, tiltOffset;
  int left, right;
  Block *block = NULL;

  if( _downButton.Check() )
  {
    bDrive = ~bDrive;
    Stop();
    return;
  }
  
  pixy.ccc.getBlocks();

  if( index == -1 ) // Block 찾기
  {
    mm_signature = 0;
    index = acquireBlock();
  }

  if( index < 0 ) // Active Block이 없으면
  {
    StopAndResetMove();
    index = -1; // Block 찾기
    return;
  }
    
  block = trackBlock( index );

  if( ! block )// 인식된 물체가 없으면
  {
    StopAndResetMove();
    index = -1; // Block 찾기
    return;
  }


  // 카메라 이미지에서 인식된 물체의 Pan/Tilt 변화량 계산
  panOffset = (int32_t) pixy.frameWidth / 2 - (int32_t) block->m_x;
  tiltOffset = (int32_t) block->m_y - (int32_t) pixy.frameHeight / 2;

  // 팬/틸트 변화량 반영
  panLoop.update( panOffset );
  tiltLoop.update( tiltOffset );

  // Pan/Tilt 서보모터 제어
  pixy.setServos( panLoop.m_command, tiltLoop.m_command );


  // calculate translate and rotate errors
  panOffset += panLoop.m_command - PIXY_RCS_CENTER_POS;
  turnLoop.update( panOffset );

  // calculating the distance to maintain from the object
  // --> 물체를 화면 아래쪽 절반에 유지하되, 1/8 이상에서 유지하도록 Tilt 조정
  tiltOffset += tiltLoop.m_command - PIXY_RCS_CENTER_POS 
                - PIXY_RCS_CENTER_POS / 2 + PIXY_RCS_CENTER_POS / 8;
  gobackLoop.update(-tiltOffset);

  // 최대 이동속도 제한
  if (gobackLoop.m_command > MAX_TRANSLATE_VELOCITY)
    gobackLoop.m_command = MAX_TRANSLATE_VELOCITY;


  if( bDrive ) // Down 버튼을 눌러서, 로봇이 공 따라가기 이동을 하는 경우
  {
    // calculate left and right wheel velocities 
    // based on rotation and translation velocities
    left = -turnLoop.m_command + gobackLoop.m_command;
    right = turnLoop.m_command + gobackLoop.m_command;

    left = left / 3;
    right = right / 3;
  
    if( left < 0  || right < 0 )
    {
      while( left < 0 || right < 0 ) {
        left += 50;
        right += 50;
      }
    }

    if (left > 225) left = 225;
    if (right > 225) right = 225;

    // 인식된 물체의 크기(높이)에 따라 거리 결정 (처음 학습시킬 때 크기 기준)
    if (block->m_height >= 130) // 아주 크면, 너무 가까우니 약간 후진
    {
      Drive2( -60, -60 );
      delay( 300 );
    }
    else if( block->m_height > 100 ) // 중간 크기이면, 적정거리 -> 정지
    {
      Stop();
    }
    else  // 작으면, 멀어졌으므로 공 따라가기 (전진/좌회전/우회전)
    {
      Drive2( right, left );
    }
  }
}
