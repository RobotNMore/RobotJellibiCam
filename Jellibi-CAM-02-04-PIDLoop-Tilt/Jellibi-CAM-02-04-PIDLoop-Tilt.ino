#include <Pixy2.h>
#include <PIDLoop.h>

Pixy2   pixy; // Pixy2 카메라 선언

PIDLoop tiltLoop(1000, 0, 0, true); // PID 제어 클래스 (P,I,D,bServo)

/////////////////////////////////////

// 이 샘플에서 PAN 서보는 가운데로 고정하고, TILT 서보를 상하로 이동한다.
int panCenter = 500;  // PAN: 우측= 0, 가운데= 500, 좌측= 1000

void setup()
{
  pixy.init();  // Pixy2 카메라 초기화
  
  tiltLoop.reset(); // Tilt PID loop 초기화, 가운데(500)
  tiltLoop.update( tiltLoop.m_command ); // Tilt 회전정보 업데이트
  pixy.setServos( panCenter, tiltLoop.m_command ); // 서보 회전
  delay( 3000 ); // 3초 대기
}

void loop()
{  
  tiltLoop.update( -500 ); // 아래쪽으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panCenter, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  tiltLoop.update( 500 ); // 위쪽으로 절반(500) 회전설정 업데이트
  pixy.setServos( panCenter, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  tiltLoop.update( 500 ); // 위쪽으로 절반(500) 회전설정 업데이트
  pixy.setServos( panCenter, tiltLoop.m_command ); // 서보 회전
  delay( 1000 );

  tiltLoop.update( -500 ); // 아래쪽으로 절반(-500) 회전설정 업데이트
  pixy.setServos( panCenter, tiltLoop.m_command ); // 서보 회전
  delay( 3000 );
}
