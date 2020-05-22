#include <Pixy2.h>
#include <PIDLoop.h>

Pixy2   pixy; // Pixy2 카메라 선언

PIDLoop panLoop(1000, 0, 0, true); // PID 제어 클래스 (P,I,D,bServo)
PIDLoop tiltLoop(1000, 0, 0, true);

/////////////////////////////////////

// 이 샘플에서는 PAN 서보의 좌우 회전과 TILT 서보의 상하 회전을 제어한다.

void setup()
{
  pixy.init();  // Pixy2 카메라 초기화
  
  panLoop.reset(); // Pan PID loop 초기화, 정면(500)
  panLoop.update( panLoop.m_command ); // Pan 회전정보 업데이트

  tiltLoop.reset(); // Tilt PID loop 초기화, 가운데(500)
  tiltLoop.update( tiltLoop.m_command ); // Tilt 회전정보 업데이트
  
  pixy.setServos( panLoop.m_command, tiltLoop.m_command ); // 서보 회전
  delay( 3000 ); // 3초 대기
}


void loop()
{  
  panLoop.update( -500 ); // 우측으로 절반(-500) 회전설정 업데이트
  tiltLoop.update( -500 ); // 아래쪽으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  panLoop.update( 500 ); // 좌측으로 절반(500) 회전설정 업데이트
  tiltLoop.update( 500 ); // 위쪽으로 절반(500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  panLoop.update( 500 ); // 좌측으로 절반(500) 회전설정 업데이트
  tiltLoop.update( 500 ); // 위쪽으로 절반(500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  panLoop.update( -500 ); // 우측으로 절반(-500) 회전설정 업데이트
  tiltLoop.update( -500 ); // 아래쪽으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panLoop.m_command, tiltLoop.m_command ); // 서보 회전
  delay( 3000 );
}
