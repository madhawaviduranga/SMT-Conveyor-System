#include <AccelStepper.h>
const int stepsPerRevolution = 200;

// Create an AccelStepper object (1 motor, using pins 8 for step and 9 for direction)
AccelStepper stepper2(1, 10, 11);  // clk+ pin 10
AccelStepper stepper1(1, 12, 13);  //clk+ pin 12

const int btnautoMode = 2;     // Connect the Auto mode button to pin 2
const int btnFeedPin = 3;      // Connect the Feed button to pin 3
const int btnBackwardPin = 4;  // Connect the backward button to pin 5
const int btnForwardPin = 5;   // Connect the forward button to pin 4

//Smema IN
const int SignalIn1 = A1;
const int SignalROut1 = 6;  // Relay Out signal 1 pin 6
//Smema Out
const int SignalIn2 = A2;   //
const int SignalROut2 = 7;  // Relay Out signal 1 pin 7

const int PsensorPin = 8;  // proximity sensor 1 pin 12
const int FLimitPin = 9;   //conveyor width Forward limit pin 8

void setup() {
  Serial.begin(9600);

  // Set up the button pins as inputs with pull-up resistors
  pinMode(btnForwardPin, INPUT);
  pinMode(btnBackwardPin, INPUT);
  pinMode(btnFeedPin, INPUT);
  pinMode(btnautoMode, INPUT);

  pinMode(FLimitPin, INPUT);
  // pinMode(BLimitPin, INPUT);

  pinMode(PsensorPin, INPUT);

  //Smema IN
  pinMode(SignalIn1, INPUT);
  pinMode(SignalROut1, OUTPUT);

  //Smema Out
  pinMode(SignalIn2, INPUT);
  pinMode(SignalROut2, OUTPUT);

  // Set the maximum speed and acceleration values (you can adjust these)
  stepper1.setMaxSpeed(10000);  // Maximum steps per second
  stepper2.setMaxSpeed(10000);  // Maximum steps per second
  // stepper1.setSpeed(45);
  stepper1.setAcceleration(10000);  // Acceleration in steps per second^2 1000000
  stepper2.setAcceleration(10000);  // Acceleration in steps per second^2 1000000
}

void loop() {

  // state of the forward and backward buttons
  int btnForwardState = digitalRead(btnForwardPin);
  int btnBackwardState = digitalRead(btnBackwardPin);
  int autoModeState = digitalRead(btnautoMode);
  int FeedState = digitalRead(btnFeedPin);

  int PsensorState = digitalRead(PsensorPin);
  int FlimitState = digitalRead(FLimitPin);
  // int BlimitState = digitalRead(BLimitPin);

  // =================================================================================================
  // =================================== conveyor width adjustment ===================================
  // =================================================================================================

  if (btnForwardState) {
    Serial.println("forward");
    if (!FlimitState) {
      stepper2.stop();
      return;
    }
    stepper2.move(1);
    stepper2.runToPosition();
  }

  if (btnBackwardState) {
    Serial.println("backward");
    if (!FlimitState) {
      stepper2.stop();
      return;
    }
    stepper2.move(-1);
    stepper2.runToPosition();
  }

  // =================================================================================================
  // ===================================== Smema signal generator ====================================
  // =================================================================================================

  //Smema IN
  int SignalIn1State = digitalRead(SignalIn1);

  if (!PsensorState) {
    digitalWrite(SignalROut1, HIGH);
    digitalWrite(SignalROut2, LOW);
  }

  //Smema IN
  int SignalIn2State = digitalRead(SignalIn2);
  if (PsensorState) {
    digitalWrite(SignalROut1, LOW);
    digitalWrite(SignalROut2, HIGH);
  }

  // =================================================================================================
  // ================================== conveyor belt rotation Auto ==================================
  // =================================================================================================

  // Serial.println(btnForwardState);
  // Serial.println(btnBackwardState);
  // Serial.println(FeedState);
  // Serial.println(autoModeState);
  // Serial.println(PsensorState);

  // Serial.println(SignalIn1State);
  // Serial.println(SignalIn2State);
  // Serial.println(" ");
  // delay(100);

  if (!autoModeState) {
    // Serial.println("autoModeState On");
    //Before to Conveyor |--| --> |--|  |--|

    if (!SignalIn1State && PsensorState) {
      Serial.println("Before to Conveyor");
      stepper1.move(1);
      //stepper1.moveTo(400);
      stepper1.runToPosition();
    } else {
      stepper1.stop();
    }

    //Conveyor to Next|--|  |--| --> |--|
    if (!SignalIn2State && !PsensorState) {
      Serial.println("Conveyor to Next");
      stepper1.move(1);
      //stepper1.moveTo(400);
      stepper1.runToPosition();
    } else {
      stepper1.stop();
    }
  }

  // =============================================

  else {
    // Serial.println("autoModeState OFF");

    if (!SignalIn1State && PsensorState) {
      stepper1.move(1);
      //stepper1.moveTo(400);
      stepper1.runToPosition();
    } else {
      stepper1.stop();
    }

    if (autoModeState && FeedState) {
      Serial.println("Feed");
      stepper1.move(1);
      //stepper1.move(1000);
      stepper1.runToPosition();
    } else {
      stepper1.stop();
    }
  }
}