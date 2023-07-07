#define ENA 6 // 왼쪽 모터 Enable
#define IN1 7 // 왼쪽 모터 제어 신호
#define IN2 8
#define IN3 9 // 오른쪽 모터 제어 신호
#define IN4 10
#define ENB 11 // 오른쪽 모터 Enable

void setup()
{
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    Serial.begin(9600);
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

        default:
            break;
        }

        Serial.println(c);
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