#include <Pixy2.h>
#include <PIDLoop.h>

Pixy2   pixy; // Pixy2 카메라 선언

PIDLoop panLoop(1000, 0, 0, true); // PID 제어 클래스 (P,I,D,bServo)

/////////////////////////////////////

// 이 샘플에서 TILT 위치는 가운데로 고정하고, PAN 서보를 좌우로 이동한다.
int tiltCenter = 500;  // TILT: 최하위= 0, 가운데= 500, 최상위= 1000

void setup()
{
  pixy.init();  // Pixy2 카메라 초기화

  panLoop.reset(); // Pan PID loop 초기화, 정면(500)
  panLoop.update( panLoop.m_command ); // Pan 회전정보 업데이트
  pixy.setServos( panLoop.m_command, tiltCenter ); // 서보 회전
  delay( 3000 ); // 3초 대기
}

void loop()
{  
  panLoop.update( -500 ); // 우측으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltCenter ); // 서보 회전
  delay( 1000 );

  panLoop.update( 500 ); // 좌측으로 절반(500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltCenter ); // 서보 회전
  delay( 1000 );

  panLoop.update( 500 ); // 좌측으로 절반(500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltCenter ); // 서보 회전
  delay( 1000 );

  panLoop.update( -500 ); // 우측으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltCenter ); // 서보 회전
  delay( 3000 );
}
