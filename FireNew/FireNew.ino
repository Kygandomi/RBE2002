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

long t;

void setup() {
	Serial.begin(9600);

	IMUSetup();
	PingSetup();
	EncoderSetup();
	ServoSetup();

	initialReadings();
	dirTracking();

}

void loop() {

	collectIMUData();
	pingAll();

	switch(robotState){
		case FORWARD_TIMED:
			straightForABit();
			break;
		case FORWARD:
			if(isFirstCheck){
				if(trackingLeft){
					initDist = cm[LB];
				}
				else{
					initDist = cm[RB];
				}
				isFirstCheck = false;
			}
			checkStop();
			Serial.print("LB: ");
			Serial.print(cm[LB]);
			Serial.print(" RB: ");
			Serial.println(cm[RB]);
			checkForOpening();
			//checkSafety();
			driveStraight();
			break;
		case TURN:
			if(isDoneTurning()){
				goTo(FORWARD_TIMED);
			}
			break;
		case FLAME:
			
			break;
		default:
			break;
	}


}



