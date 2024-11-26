#include <Arduino.h>

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

const int STEPS_PER_REV = 2048;
void stepMotor(bool clockwise);
void rotateSteps(int steps, bool clockwise);

const int stepSequence[4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1},
};

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.println("Please enter command for rotate C or A: ");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    Serial.print("Command is: ");
    Serial.println(command);
    if (command == 'C') {
      rotateSteps(500, true);
      Serial.println("Rotate clockwise.");
    } else if (command == 'A') {
      rotateSteps(250, false);
      Serial.println("Rotate counterclockwise.");
    }
    Serial.println("Please enter command for rotate C or A: ");
  }
}

void rotateSteps(int steps, bool clockwise) {
  for (int i = 0; i < steps; i++){
  stepMotor(clockwise);
  delay(5);
  }
}

void stepMotor(bool clockwise) {
  static int stepIndex = 0;
  digitalWrite(IN1, stepSequence[stepIndex][0]);
  digitalWrite(IN2, stepSequence[stepIndex][1]);
  digitalWrite(IN3, stepSequence[stepIndex][2]);
  digitalWrite(IN4, stepSequence[stepIndex][3]);


  if (clockwise) {
    stepIndex = (stepIndex + 1) % 4;
  } else {
    stepIndex = (stepIndex + 3) % 4;
  }
}
