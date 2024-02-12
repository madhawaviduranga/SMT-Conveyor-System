#include <AccelStepper.h>

int sensorInPin = 12;
void setup() {
 
  Serial.begin(9600);
  pinMode(sensorInPin, INPUT);
}

void loop() {
 
  int sensorInState = digitalRead(sensorInPin);
  
  if (!sensorInState) {
    Serial.println(sensorInState);
    delay(100);
  } else {
    Serial.println(sensorInState);
    delay(100);
  }

}