#include <mcp_can.h>
#include <SPI.h>

#define ENA 6 // 왼쪽 모터 Enable
#define IN1 7 // 왼쪽 모터 제어 신호
#define IN2 8
#define IN3 9 // 오른쪽 모터 제어 신호
#define IN4 10
#define ENB 11 // 오른쪽 모터 Enable

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);

void setup()
{
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    Serial.begin(9600);
    CAN0.begin(CAN_500KBPS); // 500Kbs의 속도로 CAN버스를 초기화 합니다.
    pinMode(2, INPUT);       // 2번 핀에 INT핀이 연결되었습니다.
    pinMode(3, OUTPUT);
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
            // Serial.println(c);
            break;
        case 'b':
            backward();
            break;
        case 'r':
            right();
            break;
        case 'l':
            left();
            break;
        case 's':
            stop();
            break;
        }

        Serial.println(c);
    }

    if (!digitalRead(2)) // 데이터가 수신되면 2번핀이 LOW상태가 됩니다.
    {
        CAN0.readMsgBuf(&len, rxBuf); // 데이터의 길이와 데이터를 읽습니다.
        rxId = CAN0.getCanId();       // 데이터의 ID(식별자)를 읽습니다.
        Serial.print("ID: ");
        Serial.print(rxId, HEX); // ID를 출력합니다.
        Serial.print("  Data: ");
        Serial.println(rxBuf[0], HEX); // 데이터를 출력합니다.
        if (rxBuf[0] <= 50)
        {
            analogWrite(ENA, rxBuf[0] - 10);
        }
        else if (rxBuf[0] == 0)
        {
            /*Serial.println("LED OFF!");
            digitalWrite(3, LOW);*/
        }
    }
    else
    {
        rxId = CAN0.getCanId();
        Serial.println(rxId);
        delay(1000); // 나중에 지워
    }
}

// 전진
void forward()
{
    // 왼쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // 오른쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// 후진
void backward()
{
    // 왼쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // 오른쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

// 좌회전
void left()
{
    // 왼쪽 모터
    digitalWrite(ENA, LOW);

    // 오른쪽 모터
    analogWrite(ENB, 128);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

// 우회전
void right()
{
    // 왼쪽 모터
    analogWrite(ENA, 128);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // 오른쪽 모터
    digitalWrite(ENB, LOW);
}

// 멈춤
void stop()
{
    // 왼쪽 모터
    digitalWrite(ENA, LOW);

    // 오른쪽 모터
    digitalWrite(ENB, LOW);
}