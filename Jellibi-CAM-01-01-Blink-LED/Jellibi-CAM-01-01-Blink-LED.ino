/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// setup 함수는 전원이 켜지면 제일 먼저 한 번만 실행됨
void setup() {
  // 보드의 10번(빨강 LED) 핀을 출력 핀으로 설정
  pinMode(10, OUTPUT);
}

// loop 함수는 무한 반복 실행됨
void loop() {
  digitalWrite(10, HIGH); // LED 켜기 (전압 레벨이 HIGH)
  delay(1000);            // 1초(1000 ms) 대기
  digitalWrite(10, LOW);  // LED 켜기 (전압 레벨이 LOW)
  delay(1000);            // 1초(1000 ms) 대기
}
