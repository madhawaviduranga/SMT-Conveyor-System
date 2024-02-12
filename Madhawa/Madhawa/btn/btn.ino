const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;

int currentState2;
int currentState3;
int currentState4;
int currentState5;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
}

void loop() {
  currentState2 = digitalRead(buttonPin2);
  currentState3 = digitalRead(buttonPin3);
  currentState4 = digitalRead(buttonPin4);
  currentState5 = digitalRead(buttonPin5);


  Serial.println("xxxxxxxxxxxxxxx ");
  Serial.println(currentState2);
  Serial.println(currentState3);
  Serial.println(currentState4);
  Serial.println(currentState5);

  Serial.println(" ");
  delay(1000);
}