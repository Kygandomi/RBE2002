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
	initHeading = heading;
	expectedHeading = initHeading;

	t = millis();
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
			//checkSafety();
			//checkForOpening();
			driveStraight();
			break;
		case TURN:
			if(isDoneTurning())
				goTo(FORWARD);
			break;
		case FLAME:
			
			break;
		default:
			break;
	}


	if(millis() - t > 500){
		Serial.println(heading);
		t = millis();
	}
}



