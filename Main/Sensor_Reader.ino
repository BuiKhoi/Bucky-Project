void GetSensorStatus() { //Get all the sensor status
  for (int i = 0; i < 7; i++) {
    Line[i] = ReadLine(i);
  }
}

bool ReadLine(int index) { //Get the sensor status for each sensor
  int temp = analogRead(Sensors[index]);
  if (temp >= Sensor_HIGH) {
    return true;
  }
  else {
    return false;
  }
}

int CheckBarrie(int directions) {
  static bool first = true;
  StopAllMotor();
  static int did_direction = 0;
  int distance = 0;
  if (did_direction != 0) {
    if (directions == did_direction) {
      return 0;
    } else {
      static bool changed = false;
      if (directions == 1) {
        LineTurnLeft();
      } else {
        LineTurnRight();
      }
      if (changed) {
        for (int i=0; i<10; i++) {
          delay(1000);
        }
      } else {
        changed = true;
        did_direction *= -1;
      }
      return directions;
    }
  }
  for (int i = 0; i < 4; i++) {
    distance += GetDistance(1);
  }
  distance /= 4;
  bool barie = (distance < 25 && first);
  if (barie || first) {
    long long int srt = millis();
    while (GetDistance(1) <= 25) {
      delay(150);
    }
    if (millis() - srt >= 2000) {
      first = false;
      did_direction = directions;
      sys_start = millis();
    }
    return 0;
  }
}

double GetDistance(int index) { //Get the sonar distance with kalman filter
  unsigned long duration;
  double distance;
  digitalWrite(SonarTrig[index], LOW);
  delayMicroseconds(2);
  digitalWrite(SonarTrig[index], HIGH);
  delayMicroseconds(10);
  digitalWrite(SonarTrig[index], LOW);
  delayMicroseconds(5);

  duration = pulseIn(SonarEcho[index], HIGH, 15000);
  distance = (double)(duration / 2 / 29.412);
  if (distance == 0) return 400;

  switch (index) {
    case 0: {
        distance = Sonar00.updateEstimate(distance);
        break;
      }
    case 1: {
        distance = Sonar01.updateEstimate(distance);
        break;
      }
    case 2: {
        distance = Sonar02.updateEstimate(distance);
        break;
      }
  }
  return distance;
}

double GetMinimalist(double distance) { //Get the smallest value for the distance to a wall since we track two walls
  while (distance > 25) {
    distance -= 25;
  }
  return distance;
}
