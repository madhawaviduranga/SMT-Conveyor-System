#include <AccelStepper.h>
const int stepsPerRevolution = 200;

AccelStepper stepper(1, 10, 11);
AccelStepper stepper2(1, 12, 13);

const int buttonForwardPin = 5;
const int buttonBackwardPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(buttonForwardPin, INPUT_PULLUP);
  pinMode(buttonBackwardPin, INPUT_PULLUP);

  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(10000);
}

void loop() {
  int buttonForwardState = digitalRead(buttonForwardPin);
  int buttonBackwardState = digitalRead(buttonBackwardPin);

  if (buttonForwardState) {
    Serial.println("buttonForwardState ON.....");
    Serial.println(buttonForwardState);
  } else {
    Serial.println("buttonForwardState OFF......");
    Serial.println(buttonForwardState);
  }

  if (buttonForwardState == LOW) {
    // Move the motor forward one step
    stepper.move(1);
    stepper.runToPosition();
  }

  if (buttonBackwardState == LOW) {
    // Move the motor backward one step
    stepper.move(-1);
    stepper.runToPosition();
  }
}