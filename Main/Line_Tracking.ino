void FollowLine() { //Main action for the robot to follow the line
  GetSensorStatus();
  LinePIDFilter();
  ShiftSpeed(Motor);
}

void LineTurnLeft() { //Turn left in line mode
  Motor[1] = -INITIAL_SPEED/5;
  Motor[2] = INITIAL_SPEED/1.5;
  ShiftSpeed(Motor);
  delay(300);
  while (!ReadLine(3)) {
    ShiftSpeed(Motor);
    delay(50);
  }
  StopAllMotor();
}

void LineTurnRight() { //Turn right in line mode
  Motor[1] = INITIAL_SPEED/1.5;
  Motor[2] = -INITIAL_SPEED/5;
  ShiftSpeed(Motor);
  delay(300);
  while (!ReadLine(3)) {
    ShiftSpeed(Motor);
    delay(50);
  }
  StopAllMotor();
}
