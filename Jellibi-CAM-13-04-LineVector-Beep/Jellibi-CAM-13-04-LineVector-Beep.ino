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

Pixy2   pixy;
PIDLoop headingLoop(1000, 0, 0, false);

#define X_CENTER      (pixy.frameWidth / 2) // 화면 가로 중앙 좌표

#define pinBuzzer  3 // 부저 핀 번호

////////////////////////////////////////  setup()

void setup() 
{
  pinMode( pinBuzzer, OUTPUT ); // 출력 핀으로 설정  
  noTone( pinBuzzer );  // 스피커/부저 끄기(음소거)

  pixy.init();
  
  pixy.setLamp(1, 1);      // 위/아래 조명 LED 모두 켜기
  pixy.changeProg("line"); // "line_tracking" 모드 설정
  pixy.setServos(500, 0);  // Pan= 500(정면중앙), Tilt= 0(가장아래)
}

////////////////////////////  loop()

void loop()
{
  // Pixy로 부터 최신 인식 데이터(벡터/교차로/바코드)를 가져온다.
  int res = pixy.line.getMainFeatures();  // Pixy에서 정보를 가져온다.
  
  if( res <= 0 ) // Error(<0) 이거나 또는 인식된 내용이 없음
  {
    noTone( pinBuzzer ); // 음소거(mute)
  }
  else if( res & LINE_VECTOR ) // 벡터 정보에 라인이 감지됨
  {
    // 앞으로 나아가는 벡터의 끝인 m_x1에 대한 변이값 계산
    int error = (int32_t) pixy.line.vectors->m_x1 - (int32_t) X_CENTER;
    headingLoop.update( error );  // heading error에 대해 PID 계산 반영

    // 만약 벡터가 전진(화살표가 위쪽 방향인 상태)이면 정상
    if( pixy.line.vectors->m_y0 > pixy.line.vectors->m_y1 )
    {
      tone( pinBuzzer, 262 );  // 도 
      delay( 500 );
    }
    else  // 만약 벡터가 아래쪽을 향하면, 후진
    {
      tone( pinBuzzer, 392 );  // 솔
      delay( 500 );
    }
  }
  delay( 50 );
}
