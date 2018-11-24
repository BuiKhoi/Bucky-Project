#include <SimpleKalmanFilter.h>

const int SonarEcho[3] = {40, 38, 36};
const int SonarTrig[3] = {41, 39, 37};

SimpleKalmanFilter Sonar00(10, 10, 5);
SimpleKalmanFilter Sonar01(10, 10, 5);
SimpleKalmanFilter Sonar02(10, 10, 5);

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(SonarTrig[i], OUTPUT);
    pinMode(SonarEcho[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print(GetDistance(i));
    Serial.print("  ");
  }
  Serial.println();
}

double GetDistance(int index) {
  unsigned long duration;
  double distance;
  digitalWrite(SonarTrig[index], LOW);
  delayMicroseconds(2);
  digitalWrite(SonarTrig[index], HIGH);
  delayMicroseconds(5);
  digitalWrite(SonarTrig[index], LOW);

  duration = pulseIn(SonarEcho[index], HIGH, 15000);
  distance = (double)(duration / 2 / 29.412);

  if (distance == 0) return 400;

  switch (index) {
    case 0: {
        return Sonar00.updateEstimate(distance);
        break;
      }
    case 1: {
        return Sonar01.updateEstimate(distance);
        break;
      }
    case 2: {
        return Sonar02.updateEstimate(distance);
        break;
      }
  }
}

double GetMinimalist(double distance) { //Get the smallest value for the distance to a wall since we track two walls
  while (distance > 25) {
    distance -= 25;
  }
  return distance;
}
