void FollowLine() { //Main action for the robot to follow the line
  GetSensorStatus();
  LinePIDFilter();
  ShiftSpeed(Motor);
}

void LineTurnLeft() { //Turn left in line mode (not tested)
  Motor[1] = -INITIAL_SPEED/10;
  Motor[2] = INITIAL_SPEED/2;
  ShiftSpeed(Motor);
  delay(200);
  while (!ReadLine(3)) {
    ShiftSpeed(Motor);
    delay(50);
  }
  StopAllMotor();
}

void LineTurnRight() { //Turn right in line mode (not tested)
  Motor[1] = INITIAL_SPEED/2;
  Motor[2] = -INITIAL_SPEED/10;
  ShiftSpeed(Motor);
  delay(200);
  while (!ReadLine(3)) {
    ShiftSpeed(Motor);
    delay(50);
  }
  StopAllMotor();
}

