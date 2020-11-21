#define PI 3.14159265359
#define START_ANG 0
unsigned long lastS;
bool first = 1;
int ang = START_ANG, sp = 15, dist = 0;

bool state = 0;



//FIRST CONNECTOR
//#define ENA1_1
#define DIR1_1 27
#define PUL1_1 26
//#define ENA1_2
#define DIR1_2 24
#define PUL1_2 25
#define PUL1_3 23
#define DIR1_3 22
//#define ENA1_3

//SECOND CONNECTOR
//#define ENA2_1
#define DIR2_1 32
#define PUL2_1 33
//#define ENA2_2
#define DIR2_2 30
#define PUL2_2 31
#define PUL2_3 29
#define DIR2_3 28
//#define ENA2_3

//TRIRD CONNECTOR
//#define ENA3_1
#define DIR3_1 34
#define PUL3_1 35
//#define ENA3_2
#define DIR3_2 36
#define PUL3_2 37
#define PUL3_3 39
#define DIR3_3 38
//#define ENA3_3

//FOURTH CONNECTOR
//#define ENA4_1
#define DIR4_1 46
#define PUL4_1 47
//#define ENA4_2
#define DIR4_2 42
#define PUL4_2 43
#define PUL4_3 41
#define DIR4_3 40
//#define ENA4_3

//#define LED1 31
//#define LED2 13
//#define LED3 44
//#define LED4 33
int target = 0;
char DATA = '0';
int s1, s2;
char buffer[11];

int Direction = 1;
void recv(byte num)
{
  for(int i = 0; i < num; i++)
  {
    uint8_t received_data = Serial.read();
    static byte msg = 0;
    static byte data[6];
    if(millis() - lastS >= 800)
      msg = 0;
    data[msg] = received_data;
    if(msg == 5)
    {
      ang = constrain(int((float)((data[0] << 8) | data[1]) / 1000.0 /PI * 180), 0, 360); 
      sp = (((data[2] << 8) | data[3])) / 100; 
      dist = ((data[4] << 8) | data[5]); 
      msg = 0;
    }
    else
      msg++;
  }
  lastS = millis();
}
void setup()
{
  Serial.begin(57600);
  //Serial1.begin(230400);

  //pinMode(ENA1_1, OUTPUT);
  pinMode(DIR1_1, OUTPUT);
  pinMode(PUL1_1, OUTPUT);
  //pinMode(ENA1_2, OUTPUT);
  pinMode(DIR1_2, OUTPUT);
  pinMode(PUL1_2, OUTPUT);
  pinMode(PUL1_3, OUTPUT);
  pinMode(DIR1_3, OUTPUT);
  //pinMode(ENA1_3, OUTPUT);

  //pinMode(ENA2_1, OUTPUT);
  pinMode(DIR2_1, OUTPUT);
  pinMode(PUL2_1, OUTPUT);
  //pinMode(ENA2_2, OUTPUT);
  pinMode(DIR2_2, OUTPUT);
  pinMode(PUL2_2, OUTPUT);
  pinMode(PUL2_3, OUTPUT);
  pinMode(DIR2_3, OUTPUT);
  //pinMode(ENA2_3, OUTPUT);

  //pinMode(ENA3_1, OUTPUT);
  pinMode(DIR3_1, OUTPUT);
  pinMode(PUL3_1, OUTPUT);
  //pinMode(ENA3_2, OUTPUT);
  pinMode(DIR3_2, OUTPUT);
  pinMode(PUL3_2, OUTPUT);
  pinMode(PUL3_3, OUTPUT);
  pinMode(DIR3_3, OUTPUT);
  //pinMode(ENA3_3, OUTPUT);

  //pinMode(ENA4_1, OUTPUT);
  pinMode(DIR4_1, OUTPUT);
  pinMode(PUL4_1, OUTPUT);
  //pinMode(ENA4_2, OUTPUT);
  pinMode(DIR4_2, OUTPUT);
  pinMode(PUL4_2, OUTPUT);
  pinMode(PUL4_3, OUTPUT);
  pinMode(DIR4_3, OUTPUT);
}
bool flag, moveFlag;
unsigned long timer;
unsigned long moveTimer;
long int angle = START_ANG * 100 / 9;
void loop()
{
   while (Serial.available())
   {
      recv(Serial.available());
   }/*
   Serial1.print(ang);
   Serial1.print("  ");
   Serial1.print(sp);
   Serial1.print("  ");
   Serial1.println(dist);
   */
   int speed = 5;
   if(ang > angle * 90 / 1000)
   {
    digitalWrite(DIR1_2, HIGH);
    digitalWrite(DIR2_2, HIGH);
    digitalWrite(DIR3_2, HIGH);
    digitalWrite(DIR4_2, HIGH);
  }
  else if (ang < angle * 90 / 1000) {
    digitalWrite(DIR1_2, LOW);
    digitalWrite(DIR2_2, LOW);
    digitalWrite(DIR3_2, LOW);
    digitalWrite(DIR4_2, LOW);
  }
   if(flag)
   {
    if(millis() - timer >= speed && ang != angle * 90 / 1000)
    {
      digitalWrite(PUL1_2, LOW);
      digitalWrite(PUL2_2, LOW);
      digitalWrite(PUL3_2, LOW);
      digitalWrite(PUL4_2, LOW);
      flag = !flag;
      timer = millis();
      if(ang > angle * 90 / 1000)
        angle++;
      else if (ang < angle * 90 / 1000)
        angle--;
    }
   }
   else
   {
    if(millis() - timer >= speed)
    {
      digitalWrite(PUL1_2, HIGH);
      digitalWrite(PUL2_2, HIGH);
      digitalWrite(PUL3_2, HIGH);
      digitalWrite(PUL4_2, HIGH);
      flag = !flag;
      timer = millis();
    }
   }
   if(sp >= 15)
   {
    digitalWrite(DIR1_3, HIGH);
    digitalWrite(DIR2_3, LOW);
    digitalWrite(DIR3_3, LOW);
    digitalWrite(DIR4_3, HIGH);
   }
   else
   {
    digitalWrite(DIR1_3, LOW);
    digitalWrite(DIR2_3, HIGH);
    digitalWrite(DIR3_3, HIGH);
    digitalWrite(DIR4_3, LOW);
   }
   if(moveFlag)
   {
    if(millis() - moveTimer >= (15 - abs(sp - 15)) / 3)
    {
      digitalWrite(PUL1_3, LOW);
      digitalWrite(PUL2_3, LOW);
      digitalWrite(PUL3_3, LOW);
      digitalWrite(PUL4_3, LOW);
      moveFlag = !moveFlag;
      moveTimer = millis();
    }
   }
   else
   {
    if(millis() - moveTimer >= (15 - abs(sp - 15)) / 3)
    {
      digitalWrite(PUL1_3, HIGH);
      digitalWrite(PUL2_3, HIGH);
      digitalWrite(PUL3_3, HIGH);
      digitalWrite(PUL4_3, HIGH);
      moveFlag = !moveFlag;
      moveTimer = millis();
    }
   }
   //Serial.println(angle * 90 / 1000);
}
