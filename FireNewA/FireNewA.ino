// FireFight.ino
#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

#include "JuniorA.h"
#include "PinglibA.h"
#include "PingA.h"
#include "IMUlibA.h"
#include "IMUA.h"
#include "WheelEncodersA.h"
#include "FlameA.h"

void setup() {
	Serial.begin(9600);

	IMUSetup();
	PingSetup();
	EncoderSetup();
	ServoSetup();

	initialReadings();
	dirTracking();
	setFlameServo();

	goTo(FORWARD);
}

void loop() {

	collectIMUData();
	pingAll();
	setCurrPing();
	Serial.print("IS FLAME FOUND: ");
	Serial.println(isFlameFound);
	Serial.print("IS FLAME DETECTED ONCE: ");
	Serial.println(flameDetectedOnce);
	Serial.print("cmLB: ");
	Serial.println(cm[LB]);
	//oneSensorCycle();

	switch(robotState){
		case FORWARD:
			checkStop();
			checkInitDist();
			checkCliff();
			//RESETER////////
				if(trackingLeft){
					if(cm[LB] < FAR_THRESH){
					checkOpeningFirst = false;
					encDiff = 0;
					isFirstDetect = false;
					}
				}
				else{
					if(cm[RB] < FAR_THRESH){
					checkOpeningFirst = false;
					encDiff = 0;
					isFirstDetect = false;
					}
				}
			///////////////
			if(!checkOpeningFirst){
				checkForOpening();
			}
			if(checkOpeningFirst){
				int currentEncAverage = (leftEnc.read() + rightEnc.read())/2;
				if(trackingLeft){
					if (currentEncAverage != initEncAverage && cm[LB] > FAR_THRESH){
						encDiff = currentEncAverage - initEncAverage;
						encDetect = 300;
						 if(initDist > FAR_THRESH && isFirstDetect){
						  encDetect = 600;
						  }
					}
				}
				else{
					if (currentEncAverage != initEncAverage && cm[RB] > FAR_THRESH){
						encDiff = currentEncAverage - initEncAverage;
						encDetect = 300;
						 if(initDist > FAR_THRESH && isFirstDetect){
						 encDetect = 600;
						 }
					}
				}

				Serial.println("encDiff ");
				Serial.println(encDiff);
				if(encDiff > encDetect){
					startTurnOpening();
				}
			}
			checkSafety();
			driveStraight();
			checkFlameSensor();
			break;
		case BACKUP:
			driveBackwards();
			break;	
		case TURN:
			completeTurn();
			break;
		case REROUTE:
			startTurn();
			break;
		case EXPLORE:
			startTurnOpening();
			break;
		case FLAME:
			if(findFlame()){
				goTo(PUT_OUT_FLAME);	
			}
			break;
		case PUT_OUT_FLAME:
			putOutFlame();
			break;
		case STOP:
			drive(0,0);
			break;
		case PAN_SENSOR:
			checkFlameFront();
			break;		
		default:
			break;
	}

	setPrevPing();
}



