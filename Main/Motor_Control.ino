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
  int maxx = MotorSpeed[0];
  maxx = (maxx<MotorSpeed[1])?MotorSpeed[1]:maxx;
  if (maxx>255) {
    double ratio =(double) 255/maxx;
    for (int i=0; i<2; i++) {
      MotorSpeed[i]*=ratio;
    }
  }
}
