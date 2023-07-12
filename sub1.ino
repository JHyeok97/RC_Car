/*센서 값 보내는 서브 아두이노*/
#include <SPI.h>
#include <mcp_can.h>
#include <SoftwareSerial.h>

MCP_CAN CAN(10);               // api cs 핀 연결 포트: 10
SoftwareSerial BTSerial(5, 4); // TXD: 5, RXD: 4

int trigPin = 9;
int echoPin = 8;
int speakerPin = 4;

unsigned char stmp[8];
unsigned char bstmp[8] = {1};

unsigned char len = 0;
unsigned char buf[8];
void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(speakerPin, OUTPUT);
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
    Serial.write(buf[0]);
    Serial.print("\n");
}

void loop()
{
    unsigned long currentMillis = millis();
    unsigned long previousMillis = 0;

    // 초음파 변수 설정 및  거리구하기
    long distance = getdistance();
    // 부저 딜레이 millis() 설정
    int buzzer_delay = 250;
    if (currentMillis - previousMillis >= buzzer_delay)
    {
        previousMillis = currentMillis;
        buzzersound(distance);
    }
    if (distance > 150) // 오버플로우 방지
        distance = 150;
    stmp[0] = distance; // 거리 정보를 stmp1 0번지에 입력

    if (buf[0] == 'b')
    {
        Serial.println("Sending");
        CAN.sendMsgBuf(0x11, 0, 8, stmp); // 데이터 전송
        delay(1000);
    }

    if (BTSerial.available())
    {
        Serial.write(BTSerial.read());
        // bstmp[0] = BTSerial.read();
        // CAN.sendMsgBuf(0x11, 0, 8, bstmp);
    }
    if (Serial.available())
    { //  블루투스로 문자 입력받으면 전송
        BTSerial.write(Serial.read());
    }

    delay(1000);
}

long getdistance()
{
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 17 / 1000;
    return distance;
}

void buzzersound(long dist)
{
    int buzzer_duration = 1000;

    delay(300); // 이거한하면 dist 값이 이상해짐

    if (dist < 5)
    {
        tone(speakerPin, 391, buzzer_duration / 2);
    }
    else if (dist < 20)
    {
        tone(speakerPin, 391, buzzer_duration / 5);
    }
    else if (dist < 40)
    {
        tone(speakerPin, 391, buzzer_duration / 20);
    }
}
