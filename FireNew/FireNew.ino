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

  //IMUSetup();
  PingSetup();
  EncoderSetup();

  leftM.attach(leftMPin, 1000, 2000);
  rightM.attach(rightMPin, 1000, 2000);

  /*long initTime = millis();
  while(millis() - initTime < 3000){
    pingAll();
  }
  dirTracking();

  initHeading = yaw;*/
  prev_yaw = initHeading;
}

void loop() {

  //collectIMUData();
  pingAll();
  //driveStraight();

  // Serial.print( leftEnc.read() );
  // Serial.print("   ");
  // Serial.println( rightEnc.read() );

  //delay(200);

  // switch(robotState){
  // case FORWARD:
  //   if(goForward){
  //     straightForABit();
  //   }
  //   else
  //     driveStraight();
  //   break;
  // case TURN:
  //   if(isDoneTurning())
  //     robotState = FORWARD;
  //   else
  //     robotState = TURN; 
  //   break;
  // case FLAME:
  //   if(checkFlameSensor()){
      
  //   }
  //   break;
  // default:
  //   break;
  // }


}



