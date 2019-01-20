#include <SimpleKalmanFilter.h>

#define Sensor_HIGH  500 //High level for optical sensor

int INITIAL_SPEED = 255;
#define INITIAL_SONAR_SPEED 150

SimpleKalmanFilter Sonar00(10, 10, 5);
SimpleKalmanFilter Sonar01(10, 10, 5);
SimpleKalmanFilter Sonar02(10, 10, 5);

const int MotorInput[2] = {10, 9};
const int MotorOutput[2] = {11, 8};

const int SonarEcho[3] = {40, 38, 36};
const int SonarTrig[3] = {41, 39, 37};

const int Sensors[7] = {A8, A9, A10, A11, A12, A13, A14};

int Directions[100] = {2, 0, 1, 0, -1};
//int Directions[100] = {2, 2, 0, 0, 2, 1, 0, 1, 2};
//int Directions[100] = {0, 1, 2, 1, 0, 2, 2, 0, 0};

int Motor[2] = {0};
bool Line[7] = {false};

int Mode = 0; //0 for line tracking, 1 for sonar routing

void(* SystemReset) (void) = 0;

long long int sys_start = 0;

void setup() {
  for (int i = 0; i < 2; i++) {
    pinMode(MotorInput[i], OUTPUT);
    pinMode(MotorOutput[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(SonarTrig[i], OUTPUT);
    pinMode(SonarEcho[i], INPUT);
  }

  for (int i = 0; i < 7; i++) {
    pinMode(Sensors[i], INPUT);
  }
  Serial.begin(9600);
  StopAllMotor();
  sys_start = millis();
  Serial.println("System started");
}

void loop() {
  FollowLine();
//    while (Mode == 0) {
//      FollowLine();
//    }
//  
//    while (Mode == 1) {
//      SonarWallRouting();
//      //    SonarRouting();
//    }

//  SonarWallRouting();
//    SonarRouting();
}
