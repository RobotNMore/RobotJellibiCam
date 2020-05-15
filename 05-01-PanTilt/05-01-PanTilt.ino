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

Pixy2 pixy;
PIDLoop panLoop(150, 0, 200, true);
PIDLoop tiltLoop(-200, 0, -100, true);

/////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
 
  pixy.init();
  
  // 사물인식 팬/틸트 동작을 위해
  // Color Connected Components 모드 설정 
  pixy.changeProg("color_connected_components");
  // 첫 단어만 사용하여 "color"로 표기 가능
}

void loop()
{  
  int32_t panOffset, tiltOffset;
  
  pixy.ccc.getBlocks(); // Pixy2 카메라의 Active Block 정보 받기
  
  if( pixy.ccc.numBlocks ) // 만약 인식된 사물에 대한 정보가 있으면
  {               
    // 인식된 사물은 큰 것부터 크기 순으로 차례로 저장되며,
    // 여기서는 제일 큰 첫 번째, 즉 [0]번째 사물의 위치 변동에 대해서만 처리한다.
    panOffset = (int32_t) pixy.frameWidth / 2 - (int32_t) pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t) pixy.ccc.blocks[0].m_y - (int32_t) pixy.frameHeight / 2;  

    panLoop.update(panOffset);    // Pan쪽 정보 반영 업데이트
    tiltLoop.update(tiltOffset);  // Tilt쪽 정보 반영 업데이트
  
    pixy.setServos(panLoop.m_command, tiltLoop.m_command); // Pan/Tilt 서보위치 변경  
  }  
  else // 만약 인식된 사물이 없으면 팬/틸트 위치 초기화
  {
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }
}
