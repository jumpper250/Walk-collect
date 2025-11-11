// ---------- ตั้งค่าขา ----------
int LS = 3;
int RS = 2;

int PWM1 = 10;
int RM1 = 4;
int RM2 = 5;

int PWM2 = 11;
int LM1 = 6;
int LM2 = 7;

int baseSpeedL = 80;
int baseSpeedR = 80;
int turnSpeed = 90;

int line_detect = LOW;

void setup() {
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  Serial.begin(9600);
  stopMoving();
}

void loop() {
  int leftSensor = digitalRead(LS);
  int rightSensor = digitalRead(RS);

  if (leftSensor == line_detect && rightSensor == line_detect) {
    moveForward();
  } else if (leftSensor == line_detect && rightSensor != line_detect) {
    turnRight();
  } else if (leftSensor != line_detect && rightSensor == line_detect) {
    turnLeft();
  } else {
    moveForward();
  }
}

// ---------- ฟังก์ชัน ----------
void moveForward() {
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW); analogWrite(PWM1, baseSpeedR);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW); analogWrite(PWM2, baseSpeedL);
}

void turnRight() {
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH); analogWrite(PWM1, turnSpeed - 10);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW); analogWrite(PWM2, turnSpeed);
  delay(200);
}

void turnLeft() {
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW); analogWrite(PWM1, turnSpeed);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH); analogWrite(PWM2, turnSpeed - 10);
  delay(200);
}

void stopMoving() {
  analogWrite(PWM1, 0); analogWrite(PWM2, 0);
}