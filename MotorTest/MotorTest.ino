const int MotorInput[2] = {10, 9};
const int MotorOutput[2] = {11, 8};

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(MotorInput[i], OUTPUT);
    pinMode(MotorOutput[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i=0; i<255; i+=2) {
    int temp[2] = {i, i};
    ShiftSpeed(temp);
    Serial.println(i);
    delay(200);
  }
  int temp[2] = {0, 0};
  ShiftSpeed(temp);
  delay(200);
}

void StopAllMotor() { //Idle the robot
  int temp[2] = {0};
  ShiftSpeed(temp);
}

void ShiftSpeed(int *MotorSpeed) { //Shift the speed to the motors
  MotorMapping(MotorSpeed);
  for (int i = 0; i < 2; i++) {
//    Serial.print(MotorSpeed[0]);
//    Serial.print("  ");
//    Serial.println(MotorSpeed[1]);
    if (MotorSpeed[i] >= 0) {
      analogWrite(MotorInput[i], MotorSpeed[i]);
      digitalWrite(MotorOutput[i], LOW);
    } else {
      digitalWrite(MotorInput[i], LOW);
      analogWrite(MotorOutput[i], -MotorSpeed[i]);
    }
  }
}

void MotorMapping(int *MotorSpeed) {
  int maxx = MotorSpeed[0];
  maxx = (maxx<MotorSpeed[1])?MotorSpeed[1]:maxx;
  if (maxx>255) {
    double ratio =(double) 255/maxx;
    for (int i=0; i<2; i++) {
      MotorSpeed[i]*=ratio;
    }
  }
}

