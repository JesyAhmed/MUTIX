#include <Servo.h>

// --- Pins ---
// Line sensors
#define LEFT_SENSOR 2
#define RIGHT_SENSOR 3

// Flame sensors
#define FLAME_LEFT A0
#define FLAME_CENTER A1
#define FLAME_RIGHT A2

Servo myservo;  
int pos = 0; 
# define PUMP  11     
# define SERVO_PIN 12

// Motor pin mapping
const int ENA = 5;   
const int IN1 = 6;   
const int IN2 = 7;

const int ENB = 4;   
const int IN3 = 8;   
const int IN4 = 9;


// --- Variables ---
int flameThreshold = 300; 
int speedValue = 150;
static bool pumpState = false;

// --- Setup ---
void setup() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW);

  myservo.attach(SERVO_PIN);
  myservo.write(90); 

  Serial.begin(9600);
 

 }

   // Motor functions

  void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

 void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

 void turnLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

 void turnRight(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

 void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0);
}


// Servo to the right
void servoRight() {
  myservo.write(120);     
}

// Servo to the left
void servoLeft() {
  myservo.write(60);        
}


// --- Extinguish Fire ---
void extinguishFire(int direction) {
  stopMotors();
  Serial.println("Fire detected! Extinguishing...");
   int sensor = FLAME_RIGHT;
  if (direction == 0) {          // Center
    myservo.write(90);
    sensor = FLAME_CENTER;
  } else if (direction == -1) {  // Left
    myservo.write(120);
    sensor = FLAME_LEFT;
  } else  {   // Right
    myservo.write(60);
  }

 while (analogRead(sensor) < flameThreshold) {  
    digitalWrite(PUMP, HIGH);  
    delay(100);                 
  }

 
  digitalWrite(PUMP, LOW); 
  Serial.println("Fire extinguished!");
  

  myservo.write(90);
  digitalWrite(PUMP, LOW);
  Serial.println("Fire extinguished! Continue line following...");
}

// --- Line Following ---
void lineFollow() {
  int left = digitalRead(LEFT_SENSOR);
  int right = digitalRead(RIGHT_SENSOR);

  if (left == LOW && right == LOW) {
    moveForward(speedValue);
  } else if (left == LOW && right == HIGH) {
    turnLeft(speedValue);
  } else if (left == HIGH && right == LOW) {
    turnRight(speedValue);
  } else {
    stopMotors();
  }
}

// --- Loop ---
void loop() {
  int flameLeft = analogRead(FLAME_LEFT);
  int flameCenter = analogRead(FLAME_CENTER);
  int flameRight = analogRead(FLAME_RIGHT);

  Serial.print("Left: "); Serial.print(flameLeft);
  Serial.print("  Center: "); Serial.print(flameCenter);
  Serial.print("  Right: "); Serial.println(flameRight);

  // Fire Detiction
  if (flameCenter < flameThreshold || flameLeft < flameThreshold || flameRight < flameThreshold) {
    if (flameCenter < flameLeft && flameCenter < flameRight) {
      extinguishFire(0);   //Forward
    } else if (flameLeft < flameRight) {
      extinguishFire(-1);  // Left
    } else {
      extinguishFire(1);   // Right
    }
  } else {
    lineFollow();
  }
}
