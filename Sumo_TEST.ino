int sensor = 500; //ปรับค่าแสง sensor ควรเป็นค่าระหว่างสีดำและสีขาว

void setup()
{
  Serial.begin(9600);

  pinMode(5, OUTPUT);//ขา IN1 ของ Drive motor 1
  pinMode(6, OUTPUT);//ขา IN2 ของ Drive motor 1

  pinMode(9, OUTPUT);//ขา D1 ของ Drive motor 1 และ Drive motor 2
  pinMode(10, OUTPUT);//ขา D2 ของ Drive motor 1 และ Drive motor 2

  pinMode(3, OUTPUT);//ขา IN1 ของ Drive motor 2
  pinMode(11, OUTPUT);//ขา IN2 ของ Drive motor 2

  digitalWrite(9, 0);//ขา D1 จ่าย 0 เพื่อให้มอเตอร์ทำงาน
  digitalWrite(10, 1);//ขา D2 จ่าย 1 เพื่อให้มอเตอร์ทำงาน

  do
  {
    backward(150);
  }
  while (analogRead(A0) > sensor && analogRead(A1) > sensor);
}

void loop()
{
  if (analogRead(A6) > sensor && analogRead(A7) > sensor) //ถ้าเซนเซอร์แสงสองตัวหน้าอ่านค่าได้มากกว่าที่ตั้ง หรือ เจอสีขาว
  {
    int sonicRead = sonic(7, 8);
    if (sonicRead > 0 && sonicRead < 60)
    {
      forward(255);
    }
    else
    {
      forward(180);
    }
  }
  else if (analogRead(A6) < sensor && analogRead(A7) > sensor) //ถ้าเซนเซอร์แสง A6 อ่านค่าได้น้อยกว่าที่ตั้ง หรือ เจอดำ และ เซนเซอร์แสง A7 อ่านค่าได้มากกว่าที่ตั้ง หรือ เจอสีขาว
  {
    backward(200); delay(500);
    for (int i = 30; i >= 0; i--)
    {
      left(150); delay(30);
      int sonicRead = sonic(7, 8);
      if (sonicRead > 0 && sonicRead < 60)
      {
        break;
      }
    }
  }
  else if (analogRead(A6) > sensor && analogRead(A7) < sensor) //ถ้าเซนเซอร์แสง A7 อ่านค่าได้น้อยกว่าที่ตั้ง หรือ เจอดำ และ เซนเซอร์แสง A6 อ่านค่าได้มากกว่าที่ตั้ง หรือ เจอสีขาว
  {
    backward(200); delay(500);
    for (int i = 30; i >= 0; i--)
    {
      right(150); delay(30);
      int sonicRead = sonic(7, 8);
      if (sonicRead > 0 && sonicRead < 60)
      {
        break;
      }
    }
  }
  else // หรือเจอดำทั้งคู่
  {
    backward(60);
  }
}

int sonic(int Trig, int Echo)  //ฟังชั่นอ่านค่า Ultrasonic โดยระบุขา Trig และ Echo ลงในวงเล็บตามลำดับ
{
  long duration;
  int cm;
  pinMode(Trig, OUTPUT);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(Trig, LOW);
  pinMode(Echo, INPUT);
  duration = pulseIn(Echo, HIGH);

  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  return cm;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void forward(int speeds) //ฟังชั่นเดินหน้า
{
  analogWrite(5, speeds); digitalWrite(6, 0);
  analogWrite(3, speeds); digitalWrite(11, 0);
}

void backward(int speeds) //ฟังชั่นถอยหลัง
{
  analogWrite(6, speeds); digitalWrite(5, 0);
  analogWrite(11, speeds); digitalWrite(3, 0);
}

void right(int speeds) //ฟังชั่นเลี้ยวขวา
{
  analogWrite(6, speeds); digitalWrite(5, 0);
  analogWrite(3, speeds); digitalWrite(11, 0);
}

void left(int speeds) //ฟังชั่นเลี้ยวซ้าย
{
  analogWrite(5, speeds); digitalWrite(6, 0);
  analogWrite(11, speeds); digitalWrite(3, 0);
}
