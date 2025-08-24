#include <Servo.h>

Servo myservo;  
int pos = 0; 
int pumpPin = 11;     
int servoPin = 12; 

// Motor pin mapping
const int ENA = 5;   
const int IN1 = 6;   
const int IN2 = 7;

const int ENB = 10;   
const int IN3 = 8;   
const int IN4 = 9;

int speedValue = 200;

char cmd;

static bool pumpState = false;


void setup() {
  
 myservo.attach(servoPin);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  myservo.write(90); 

  Serial.begin(9600);
  Serial.println("Enter command: W=F, S=B, A=L, D=R, X=STOP ,S=breake , E=Extinguish ,p=pumb , ");

}

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


  /*void brakeMotors() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
*/

void loop() {
  
if (Serial.available()) {
    cmd = Serial.read();
    cmd = toupper(cmd);

    if (cmd == 'E') {  
      digitalWrite(pumpPin, HIGH);
      for (int j = 0; j < 3; j++) {
        for (int pos = 60; pos <= 120; pos += 2) {
          myservo.write(pos);
          delay(15);
        }
        for (int pos = 120; pos >= 60; pos -= 2) {
          myservo.write(pos);
          delay(15);
        }
      }
      digitalWrite(pumpPin, LOW);
      myservo.write(90);
    }
    
    else if (cmd == 'P') {
     pumpState = !pumpState;  //
     digitalWrite(pumpPin, pumpState ? HIGH : LOW);
}

    else if (cmd == 'F') moveForward(speedValue);
    else if (cmd == 'B') moveBackward(speedValue);
    else if (cmd == 'L') turnLeft(speedValue);
    else if (cmd == 'R') turnRight(speedValue);
    else if (cmd == 'X') stopMotors();
    //else if (cmd == 'S') breakeMotors();
   
 }
}
