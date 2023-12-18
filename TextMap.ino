#include <NewPing.h>

#define TRIGGER_PIN_FORWARD 25
#define ECHO_PIN_FORWARD 26

#define TRIGGER_PIN_LEFT 14
#define ECHO_PIN_LEFT 27

#define TRIGGER_PIN_RIGHT 12
#define ECHO_PIN_RIGHT 13

#define MAX_DISTANCE 300

#define size 30

// Định nghĩa chân điều khiển động cơ bên trái
#define LEFT_MOTOR_ENA  2  // Chân kích hoạt động cơ bên trái (ENA)
#define LEFT_MOTOR_IN1  4  // Chân điều khiển hướng quay 1
#define LEFT_MOTOR_IN2  5  // Chân điều khiển hướng quay 2

// Định nghĩa chân điều khiển động cơ bên phải
#define RIGHT_MOTOR_ENB 15  // Chân kích hoạt động cơ bên phải (ENB)
#define RIGHT_MOTOR_IN3 16  // Chân điều khiển hướng quay 3
#define RIGHT_MOTOR_IN4 17  // Chân điều khiển hướng quay 4


// NewPing setup of pins and maximum distance
NewPing sonar_forward(TRIGGER_PIN_FORWARD, ECHO_PIN_FORWARD, MAX_DISTANCE);
NewPing sonar_left(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonar_right(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);


unsigned int distance_forward;
unsigned int distance_left;
unsigned int distance_right;

int parityPosition = 1;

bool objForward;
bool objLeft;
bool objRight;

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);

  pinMode(RIGHT_MOTOR_IN3, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {

  
  
  delay(1000);
    // Đo khoảng cách
  distance_forward = sonar_forward.ping_cm();
  distance_left = sonar_left.ping_cm();
  distance_right = sonar_right.ping_cm();

  if (distance_forward >= size) objForward = 1;
  else objForward = 0;

  if (distance_left >= size) objLeft = 1;
  else objLeft = 0;

  if (distance_right >= size) objRight = 1;
  else objRight = 0;

  Serial.print("Robot dang o hang thu :");
  Serial.println(parityPosition);
  Serial.println();

  Serial.print("### ");
  Serial.print(distance_forward);
  //Serial.print("cm");
  Serial.println(" ###");

  Serial.print(distance_left);
  //Serial.print("cm");
  Serial.print(" ### ");
  Serial.println(distance_right);
  //Serial.println("cm");
 
  Serial.println("#########");
  Serial.println("");

  if (parityPosition % 2 == 1)
  {
    if(objForward == 1 )
    {
      goForward();
      stayStop();
    } 
    else
    {
      if(objRight == 1)
      {
        turnRight();
        stayStop();
        goForward();
        stayStop();
        turnRight();
        stayStop();
        parityPosition += 1;
      }
    }
  }
  else
  {
    if((objForward == 1) )
    {
      goForward();
      stayStop();
    } 
    else
    {
      if(objLeft == 1)
      {
        turnLeft();
        stayStop();
        goForward();
        stayStop();
        turnLeft();
        stayStop();
        parityPosition += 1;
      }
    }
  }

}

void goBack() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);

  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, HIGH);

  delay(500);  // Chờ 2 giây
}

void goForward() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);

  digitalWrite(RIGHT_MOTOR_IN3, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
  Serial.println("Tien");

  delay(550);  // Chờ 2 giây
}

void turnRight()  {
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, HIGH);

  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  Serial.println("Re phai");

  delay(620);
}

void turnLeft() {

  digitalWrite(RIGHT_MOTOR_IN3, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);

  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  Serial.println("Re Trai");

  delay(620);

}

void stayStop() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN3, LOW);
  digitalWrite(RIGHT_MOTOR_IN4, LOW);
  delay(500);
}