void StopAllMotor() { //Idle the robot
  int temp[2] = {0};
  ShiftSpeed(temp);
}

void ShiftSpeed(int *MotorSpeed) { //Shift the speed to the motors
  MotorMapping(MotorSpeed);
  //  Serial.print(MotorSpeed[0]);
  //  Serial.print("  ");
  //  Serial.println(MotorSpeed[1]);
  for (int i = 0; i < 2; i++) {
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
  int TEMP_INITIAL_SPEED = 0;
  if (millis() - sys_start < 600) {
    TEMP_INITIAL_SPEED = (float)(INITIAL_SPEED * ((millis() - sys_start)) / 600);
  } else {
    TEMP_INITIAL_SPEED = INITIAL_SPEED;
  }
  int maxx = MotorSpeed[0];
  maxx = (maxx < MotorSpeed[1]) ? MotorSpeed[1] : maxx;
  if (maxx > TEMP_INITIAL_SPEED) {
    double ratio = (double) TEMP_INITIAL_SPEED / maxx;
    for (int i = 0; i < 2; i++) {
      MotorSpeed[i] *= ratio;
    }
  }
}
