#include <Servo.h>

Servo myservo;  
int pos = 0; 
# define pumpPin  11     
# define servoPin  12

// Motor pin mapping
const int ENA = 5;   
const int IN1 = 6;   
const int IN2 = 7;

const int ENB = 3;   
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
  Serial.println("Enter command: W=F, S=B, A=L, D=R, X=STOP ,S=breake , E=Extinguish ,p=pumb ,Y =servoRight , Z=servoLeft ");

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



  void breakeMotors() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}


void loop() {
  if (Serial.available()) {
    cmd = Serial.read();
    cmd = toupper(cmd);

    switch (cmd) {
      case 'Y': servoRight(); break ; //servo to right  
      case 'Z': servoLeft(); break ; // servo to left

      case 'P':  // Toggle pump
        pumpState = !pumpState;
        digitalWrite(pumpPin, pumpState ? HIGH : LOW);
        Serial.println(pumpState ? "Pump ON" : "Pump OFF");
        break;

      case 'F': moveForward(speedValue); break;
      case 'B': moveBackward(speedValue); break;
      case 'L': turnLeft(speedValue); break;
      case 'R': turnRight(speedValue); break;
      case 'X': stopMotors(); break;
      case 'S': breakeMotors(); break;
      default:  // Error handling for invalid commands
        Serial.println("Error: Invalid Command!");
        break;
    }
  }
}
