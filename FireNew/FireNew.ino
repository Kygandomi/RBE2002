// FireFight.ino
#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

#include "Junior.h"
#include "Pinglib.h"
#include "Ping.h"
#include "IMUlib.h"
#include "IMU.h"
#include "WheelEncoders.h"
#include "Flame.h"

void setup() {
  Serial.begin(9600);
  IMUSetup();
  PingSetup();
  zeroEncoders();
  leftM.attach(leftMPin, 1000, 2000);
  rightM.attach(rightMPin, 1000, 2000);
  pinMode(A0, INPUT);

  long initTime = millis();
  while(millis() - initTime < 3000){
    pingAll();
  }
  dirTracking();

  initHeading = yaw;
}

void loop() {

  collectIMUData();
  pingAll();

  if(oldLB != cm[LB]){
    prevLB = oldLB;
    oldLB = cm[LB];
  }

  if(oldRB != cm[RB]){
    prevRB = oldRB;
    oldRB = cm[RB];
  }

  switch(robotState){
  case FORWARD:
    if(goForward){
      straightForABit();
    }
    else
      driveStraight();
    break;
  case TURN:
    if(isDoneTurning())
      robotState = FORWARD;
    else
      robotState = TURN; 
    break;
  case FLAME:
    if(checkFlameSensor()){
      
    }
    break;
  default:
    break;
  }


}



