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
    return;
    
  if( res & LINE_BARCODE ) // 벡터 정보에 BarCode 감지됨
  {
    for( int i=0; i<=pixy.line.barcodes->m_code; i++ )
    { // 인식된 바코드의 (값 + 1) 만큼 소리를 낸다.
      tone( pinBuzzer, 262 ); // 반복 횟수= 코드값 + 1 ("도" 재생)
      delay( 250 );
      noTone( pinBuzzer ); // 음소거(mute)
      delay( 250 );
    }
    delay( 2000 );
  }
}
