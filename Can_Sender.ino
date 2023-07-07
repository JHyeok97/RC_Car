#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);

unsigned char stmp1[1] = {0};
unsigned char stmp2[1] = {1};
int Last = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT_PULLUP);
    if (CAN0.begin(CAN_500KBPS) == CAN_OK)
        Serial.print("Can init ok!!\r\n"); // 500Kbs의 속도로 CAN버스를 초기화 합니다.
    else
        Serial.print("Can init fail!!\r\n");
}

void loop()
{
    int Now = 1;
    if (Now == 1)
    {
        Serial.println("Button OFF!");
        digitalWrite(2, LOW);
        CAN0.sendMsgBuf(0x02, 3, 1, stmp1); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
    }
    else if (Now == 0)
    {
        Serial.println("Button ON!");
        digitalWrite(2, HIGH);
        CAN0.sendMsgBuf(0x01, 0, 1, stmp2); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
    }
    delay(1000);

    Now = 0; // 버튼의 상태를 저장합니다.
    if (Now == 1)
    {
        Serial.println("Button OFF!");
        digitalWrite(2, LOW);
        CAN0.sendMsgBuf(0x02, 3, 1, stmp1); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
    }
    else if (Now == 0)
    {
        Serial.println("Button ON!");
        digitalWrite(2, HIGH);
        CAN0.sendMsgBuf(0x01, 0, 1, stmp2); // 데이터를 보냅니다:  id = 0x00, standrad flame, 데이터 길이 = 1, 데이터
    }
    delay(1000);
}
