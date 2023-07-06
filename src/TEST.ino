#include <SoftwareSerial.h>
#define ENA 6  // 왼쪽 모터 Enable
#define IN1 7  // 왼쪽 모터 제어 신호
#define IN2 8  // 왼쪽 모터 제어 신호
#define IN3 9  // 오른쪽 모터 Enable
#define IN4 10 // 오른쪽 모터 제어 신호
#define ENB 11 // 오른쪽 모터 제어 신호
#define blueTX 2
#define blueRX 3
SoftwareSerial btSerial(blueRX, blueTX);

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
}

// 전진코드
void forward()
{
  // 왼쪽 모터
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // 오른쪽 모터
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Serial.println("전진");
}

// 후진코드
void backward()
{
  // 왼쪽 모터
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // 오른쪽 모터
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  // Serial.println("후진");
}

// 좌회전
void left()
{
  // 왼쪽 모터
  digitalWrite(ENA, LOW);

  // 오른쪽 모터
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  // Serial.println("좌회전");
}

// 우회전
void right()
{
  // 왼쪽 모터
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // 오른쪽 모터
  digitalWrite(ENB, LOW);
  // Serial.println("우회전");
}

// 멈춤
void stopCar()
{
  // 오른쪽 모터
  digitalWrite(ENA, LOW);

  // 왼쪽 모터
  digitalWrite(ENB, LOW);
  // Serial.println("정지");
}
