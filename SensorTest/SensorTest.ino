#define Sensor_HIGH  500

bool Line[7] = {false};
const int Sensors[7] = {A8, A9, A10, A11, A12, A13, A14};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(Sensors[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  GetSensorAnalog();
}

void GetSensorDigital() {
  GetSensorStatus();
  for (int i = 0; i < 7; i++) {
    Serial.print(Line[i]);
  }
  Serial.println();
}

void GetSensorAnalog() {
  for (int i = 0; i < 7; i++) {
    Serial.print(analogRead(Sensors[i]));
    Serial.print("  ");
  }

  Serial.println();
}

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
