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
#include "Encoders.h"
#include "Flame.h"
#include "Servos.h"
#include "Navigation.h"

void setup() {
	Serial.begin(9600);

	IMUSetup();
	PingSetup();
	EncoderSetup();
	ServoSetup();
	Serial.println("SETUP");

	initialReadings();
	setDirection();
	Serial.println("START");

	goTo(FORWARD);
}

void loop() {

	collectIMUData();
	pingAll();

	switch(robotState){
		case FORWARD:
			if(checkStop()){
				startTurn();
				goTo(TURN);
			}
			if(checkForOpening())
				goTo(EXPLORE);
			if(checkCliff())
				goTo(BACKUP);
			driveStraight();
			break;
		case EXPLORE:
			if(distanceTraveled() > (goFarther? 30 : 15)){
				Serial.println("Reached the destination!");
				startTurnOpening();
				goTo(TURN);
			}
			if(!checkForOpening()){
				goTo(FORWARD);
			}
			driveStraight();
			break;
		case BACKUP:
			if(driveBackwards()){
				startTurn();
				goTo(TURN);
			}
			break;	
		case TURN:
			if(completeTurn())
				goTo(FORWARD);
			break;
	}
}
