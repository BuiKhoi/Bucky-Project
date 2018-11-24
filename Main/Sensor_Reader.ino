void GetSensorStatus() { //Get all the sensor status
  for (int i = 0; i < 7; i++) {
    Line[i] = ReadLine(i);
  }
}

bool ReadLine(int index) { //Get the sensor status for each sensor
  int temp = analogRead(Sensors[index]);
  if (temp <= Sensor_HIGH) {
    return true;
  }
  else {
    return false;
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
