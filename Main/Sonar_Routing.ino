void SonarRouting() { //Sonar routing remembering the order
  static bool was_interrupted = false;
  static int steps = 0;
  while (!Interrupted() || was_interrupted) {
    if (was_interrupted) {
      if (!Interrupted()) {
        was_interrupted = false;
      }
    }
    SonarPid();
    ShiftSpeed(Motor);
  }
  CheckModeSwitch();
  if (Mode == 0) {
    return;
  }
  int start = millis();
  while (millis() - start < 180) {
    SonarPid();
    ShiftSpeed(Motor);
  }
  StopAllMotor();
  delay(100);
  switch (Directions[steps++]) {
    case -1: {
        Mode = 0;
        break;
      }
    case 0: {
        TurnLeft();
        break;
      }
    case 1: {
        break;
      }
    case 2: {
        TurnRight();
        break;
      }
    case 3: {
        TurnAround();
        break;
      }
  }
  was_interrupted = true;
}

void SonarWallRouting() { //Track the wall with sonar sensor
  if (Interrupted()) {
    CheckModeSwitch();
    if (Mode == 0) {
      return;
    }
    switch (DecideDirection()) {
      case 0: {
          TurnLeft();
          break;
        }
      case 1: {
          break;
        }
      case 2: {
          TurnRight();
          break;
        }
      case 3: {
          TurnAround();
          break;
        }
    }
  }
  SonarPid();
  ShiftSpeed(Motor);
}

bool Interrupted() { //Check if the robot path is "interrupted"
  if (GetDistance(0) > 20 || GetDistance(2) > 20) {
    Serial.println("Interrupted");
    return true;
  }
  else return false;
}

void TurnLeft() { //Turn left in sonar mode
  int tracking_distance = GetDistance(0);
  int motor[2] = { -INITIAL_SONAR_SPEED / 5, INITIAL_SONAR_SPEED};
  ShiftSpeed(motor);
  delay(1000);
//  while (abs(GetDistance(1) - tracking_distance) > 5) {
//    ShiftSpeed(motor);
//    delay(50);
//  }
  StopAllMotor();
}

void TurnRight() { //Turn right in sonar mode
  int tracking_distance = GetDistance(2);
  int motor[2] = { INITIAL_SONAR_SPEED, -INITIAL_SONAR_SPEED / 5};
  ShiftSpeed(motor);
  delay(1000);
//  while (abs(GetDistance(1) - tracking_distance) > 5) {
//    ShiftSpeed(motor);
//    delay(50);
//  }
  StopAllMotor();
}

void TurnAround() { //Turn around in sonar mode
  int distance[2] = {GetDistance(0), GetDistance(1)};
  int motor[2] = {INITIAL_SONAR_SPEED, -INITIAL_SONAR_SPEED};
  ShiftSpeed(motor);
  delay(100);
  while (abs(GetDistance(0) - distance[1]) < 1.5 && abs(GetDistance(1) - distance[0]) < 1.5) {
    ShiftSpeed(motor);
    delay(50);
  }
}

int DecideDirection() { //Decide which direction to run
  static int i = 0;
  if (GetDistance(0) > 9) {
    return 0;
  } else if (GetDistance(1) > 9) {
    return 1;
  } else if (GetDistance(2) > 9) {
    return 2;
  } else return 3;
  //  return Directions[i++];
}
