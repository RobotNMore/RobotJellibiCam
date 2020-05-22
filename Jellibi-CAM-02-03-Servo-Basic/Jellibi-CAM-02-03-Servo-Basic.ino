#include <Servo.h> 
 
Servo myservo;

#define pinServo = 5;  // 서보모터 핀 번호

void setup() 
{ 
  myservo.attach(servoPin); // 서보모터 연결
} 
 
void loop() 
{
  int pos;

  // 0도에서 175도까지 5도씩 각도증가 회전
  for(pos= 0; pos < 175; pos += 5) 
  { 
    myservo.write(pos); // 서보모터 회전
    delay(20); // 회전할 여유시간 (ms)
  }
  
  // 180도에서 5도까지 5도씩 각도감소 회전
  for(pos= 180; pos > 5; pos -= 5)
  { 
    myservo.write(pos); // 서보모터 회전
    delay(20); // 회전할 여유시간 (ms)
  } 
}
