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
			checkStop();
			checkForOpening();
			//checkSafety();
			driveStraight();
			break;
		case TURN:
			completeTurn();
			break;
		case ALIGN:
			adjustTurn();
			break;
		case REROUTE:
			startTurn();
			break;
		case EXPLORE:
			startTurnOpening();
			break;
		case FLAME:
			
			break;
	}
}



