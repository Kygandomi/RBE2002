// FireFight.ino
#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>

#include "Junior.h"
#include "Pinglib.h"
#include "Ping.h"
#include "IMUlib.h"
#include "IMU.h"
#include "Encoders.h"
#include "Flame.h"
#include "Servos.h"
#include "Navigation.h"
#include "Extra.h"

void setup() {
	Serial.begin(9600);

	IMUSetup();
	PingSetup();
	EncoderSetup();
	ServoSetup();

	initialReadings();
	setDirection();
	setFlameServo();
	//Serial.println("Start");

	initHeading = yaw;

	Timer1.initialize(1000);
	Timer1.attachInterrupt(sov);

	//Serial.println("Ok lets go...");
	goTo(FORWARD);
}

void loop() {

	collectIMUData();
	pingAll();
	setCurrPing();
	Serial.print("left: ");
	Serial.println(leftEnc.read());
	Serial.print("right: ");
	Serial.println(rightEnc.read());

	/*switch(robotState){
		case FORWARD:
			checkStop();
			checkInitDist();
			checkCliff();
			//RESETER////////
			if(trackingLeft){
				if(cm[LB] < FAR_THRESH){
					isOpening = false;
					encDiff = 0;
					isFirstDetect = false;
				}
			}
			else{
				if(cm[RB] < FAR_THRESH){
					isOpening = false;
					encDiff = 0;
					isFirstDetect = false;
				}
			}
			///////////////
			if(!isOpening){
				checkForOpening();
			}
			if(isOpening){
				int currentEncAverage = (leftEnc.read() + rightEnc.read())/2;
				if(trackingLeft){
					if(currentEncAverage != initEncAverage && cm[LB] > FAR_THRESH){
						encDiff = currentEncAverage - initEncAverage;
						encDetect = 275;
						if(initDist > FAR_THRESH && isFirstDetect){
							encDetect = 800;
						}
					}
				}
				else{
					if(currentEncAverage != initEncAverage && cm[RB] > FAR_THRESH){
						encDiff = currentEncAverage - initEncAverage;
						encDetect = 275;
						if(initDist > FAR_THRESH && isFirstDetect){
							encDetect = 800;
						}
					}
				}

				if(encDiff > encDetect){
					startTurnOpening();
				}
			}
			//checkSafety();
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
			checkStopFindFlame();
			break;		
		default:
			break;
	}

	setPrevPing();*/
}
