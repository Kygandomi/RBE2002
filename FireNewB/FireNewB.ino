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
	zeroEncoders();
	leftM.attach(leftMPin, 1000, 2000);
	rightM.attach(rightMPin, 1000, 2000);
	pan.attach(panPin);
	tilt.attach(tiltPin);
	gas.attach(gasPin, 1000, 2000);
	pinMode(A0, INPUT);
}

void loop() {
	collectIMUData();
	pingAll();
	checkStop();
	checkSensors();
	switch(robotState){
		case ALIGN:
		 	alignWithWall();
		 	break;
		case FORWARD:
			driveStraight();
			break;
		case SENSOR:
			correct(correctR);
			break;
		case FLAME:
			if(checkFlameSensor())
                findFlame();
                break;
        case TURN:
           	turnRobot(turnRight);
            break;
        case STOP:
            while(1);
            break;
        default:
            break;
       }
}


