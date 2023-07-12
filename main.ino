/*모터 제어해주는 메인 아두이노*/
#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10); // api cs 핀 연결 포트: 10

#define ENB 3 // 왼쪽 모터 Enable
#define IN4 4 // 왼쪽 모터 제어 신호
#define IN3 5

#define ENA 6 // 오른쪽 모터 Enable
#define IN1 7 // 오른쪽 모터 제어 신호
#define IN2 8

unsigned char stmp[8];
unsigned char len = 0;
unsigned char buf[8];
void setup()
{
    Serial.begin(9600);
    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Init Success!");
    attachInterrupt(digitalPinToInterrupt(2), CAN_int, FALLING);
    // 2번핀 인터럽트 설정(falling 때), 인터럽트 들어오면 CAN_int 함수 실행
}
void CAN_int() // 인터럽트 들어올 때만 실행
{

    CAN.readMsgBuf(&len, buf);            // CAN 데이터 가져오기
    unsigned long canID = CAN.getCanId(); // CAN ID 얻기
    Serial.print("\nData from ID: 0x");
    Serial.println(canID, HEX); // 16진수로 ID 출력
    /*for (int i = 0; i < len; i++)
      {
          Serial.print(buf[i]);
          Serial.print("\t");
      }
      */
    Serial.print(buf[0]);
    Serial.print("\n");
}

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();

        switch (c)
        {
        case 'f':
            forward();
            stmp[0] = 'f';

            break;
        case 'b':
            backward();
            stmp[0] = 'b';

            break;
        case 'r':
            right();
            stmp[0] = 'r';
            break;
        case 'l':
            left();
            stmp[0] = 'l';
            break;
        case 's':
            stop();
            stmp[0] = 's';
            break;
        }
        Serial.println("Sending");
        CAN.sendMsgBuf(0x05, 0, 8, stmp); // 데이터 전송
        delay(1000);
        Serial.println(c);
    }
}

// 전진
void forward()
{
    // 왼쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // 오른쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

// 후진
void backward()
{
    // 왼쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    // 오른쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

// 좌회전
void left()
{
    // 왼쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    // 오른쪽 모터
    digitalWrite(ENA, LOW);
}

// 우회전
void right()
{
    // 왼쪽 모터
    digitalWrite(ENB, LOW);

    // 오른쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

// 멈춤
void stop()
{
    // 왼쪽 모터
    digitalWrite(ENB, LOW);

    // 오른쪽 모터
    digitalWrite(ENA, LOW);
}
