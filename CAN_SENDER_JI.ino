#include <mcp_can.h>
#include <SPI.h>
#define TRIG 9 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 8 //ECHO 핀 설정 (초음파 받는 핀)
#define buzzer 4 //부저 설정

MCP_CAN CAN0(10);

unsigned char stmp1[10] = {10,20,30,40,50,60,70,80,90,100};
unsigned char stmp2[10] = {15,20,30,40,50,60,70,80,90,100};

void setup() {
    Serial.begin(115200);
  //초음파 핀 설정
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
  //부저 설정
    pinMode(4, OUTPUT);
    //can 통신 초기화
    if(CAN0.begin(CAN_500KBPS) == CAN_OK) Serial.print("Can init ok!!\r\n"); // 500Kbs의 속도로 CAN버스를 초기화 합니다.
    else Serial.print("Can init fail!!\r\n");
}
void loop() {
    unsigned long currentMillis = millis();
    unsigned long previousMillis = 0;
  // 초음파 변수 설정 및  거리구하기 
    long distance = getdistance();
    //부저 딜레이 millis() 설정
    int buzzer_delay =250;
    if (currentMillis -previousMillis >= buzzer_delay )
    {
        previousMillis= currentMillis;
        buzzersound(distance);
    }
    if (distance > 150) // 오버플로우 방지
    distance = 150;
    stmp1[0] = distance; //거리 정보를 stmp1 0번지에 입력
    stmp2[0] = distance; //거리 정보를 stmp2 0번지에 입력
    // 거리에 따라 Now 변수 설정
    int Now = 1;
    if (distance < 40)
    {
    Now = 0;
    }
    else
    {
      Now =1;
    }
    if(Now == 1) 
    {
      CAN0.sendMsgBuf(0x02, 1, 8, stmp1); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
      Serial.println(stmp1[0]);
    }
    else if(Now == 0) 
    {
      CAN0.sendMsgBuf(0x01, 1, 8, stmp2); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
      Serial.println(stmp1[0]);
    }
}
long getdistance()
{
    long duration, distance;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    duration = pulseIn (ECHO, HIGH);
    distance = duration * 17 / 1000; 
    return distance;

}


void buzzersound(long dist)
{
  int buzzer_duration = 1000;
  
  
  delay(300); // 이거한하면 dist 값이 이상해짐

    if (dist < 5)
    {
      tone(buzzer,391 ,buzzer_duration/2);
    }
    else if (dist < 20)
    { 
      tone(buzzer,391 ,buzzer_duration/5);
    }
    else if (dist < 40)
    {
      tone(buzzer,391,buzzer_duration/20);
    }



}

