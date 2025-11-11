รวมโค้ดเรียบร้อย เริ่มการใช้งาน
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

// ---------- ตัวแปรสถานะ ----------
int state = 0; // 0=เริ่มต้น, 1=ทางแรก, 2=เลี้ยวซ้าย, 3=เลี้ยวขวา, 4=เข้าเส้นชัย

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
  delay(500);
}

void loop() {
  int leftSensor = digitalRead(LS);
  int rightSensor = digitalRead(RS);

  Serial.print("State: "); Serial.println(state);

  // ---------- ตรวจจับจุดตัด ----------
  if (leftSensor == line_detect && rightSensor == line_detect) {
    stopMoving();
    delay(200);

    // เปลี่ยนพฤติกรรมตามลำดับการเดิน
    if (state == 0) {
      // จุดตัดแรก → เดินตรง
      moveForward();
      delay(800);
      state = 1;
    } 
    else if (state == 1) {
      // จุดตัดที่สอง → ถอยหลังแล้วเลี้ยวขวา
      backRight();
      state = 2;
    } 
    else if (state == 2) {
      // จุดตัดที่สาม → ถอยหลังแล้วเลี้ยวซ้าย
      backLeft();
      state = 3;
    } 
    else if (state == 3) {
      // จุดสุดท้าย → หยุด
      stopMoving();
      state = 4;
    }
  }
  // ---------- เดินตามเส้น ----------
  else if (leftSensor == line_detect && rightSensor != line_detect) {
    turnRight();
  } 
  else if (leftSensor != line_detect && rightSensor == line_detect) {
    turnLeft();
  } 
  else {
    moveForward();
  }
}

// ---------- ฟังก์ชันเคลื่อนไหว ----------
void moveForward() {
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW); analogWrite(PWM1, baseSpeedR);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW); analogWrite(PWM2, baseSpeedL);
}

void turnRight() {
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH); analogWrite(PWM1, turnSpeed - 10);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW); analogWrite(PWM2, turnSpeed);
  delay(100);
}

void turnLeft() {
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW); analogWrite(PWM1, turnSpeed);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH); analogWrite(PWM2, turnSpeed - 10);
  delay(100);
}

void stopMoving() {
  analogWrite(PWM1, 0); analogWrite(PWM2, 0);
}

void backRight() {
  reverseShort();
  pivotTurnRight();
}

void backLeft() {
  reverseShort();
  pivotTurnLeft();
}

void reverseShort() {
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH); analogWrite(PWM1, baseSpeedR);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH); analogWrite(PWM2, baseSpeedL);
  delay(700);
}

void pivotTurnRight() {
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH); analogWrite(PWM1, baseSpeedR);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW); analogWrite(PWM2, baseSpeedL);
  delay(500);
}

void pivotTurnLeft() {
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW); analogWrite(PWM1, baseSpeedR);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH); analogWrite(PWM2, baseSpeedL);
  delay(500);
}