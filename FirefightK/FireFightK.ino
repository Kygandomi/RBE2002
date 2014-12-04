// FireFight.ino
#include <Servo.h>

#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

#include "Junior.h"
#include "Ping.h"
#include "WheelEncoders.h"
#include "IMU.h"

// Added a comment for no reason
double angle = 0; 
boolean turnRight = true;
boolean flame = false;
boolean correctR = false; 

void setup() {
	Serial.begin(9600);
	//IMUSetup();
	PingSetup();
	zeroEncoders();
	leftM.attach(leftMPin, 1000, 2000);
	rightM.attach(rightMPin, 1000, 2000);
	pinMode(A0, INPUT);
}

void alignWithWall(){
 //right now sets the state to Forward
 robotState = FORWARD;  
}

boolean checkFlameSensor(){
  //checks Flame sensor and returns true if flame is nearby
  if(analogRead(A0) > flame){
  	return true;
  } 
  
  else{
  	robotState = FORWARD; 
  	return false; 
  }
}

void findFlame(){
 //routine for finding flame 
}

void checkSensors(){
	if(cm[LB] < 20 && cm[LB] != 0){
	    //routine for correcting if LB is close to wall
	    robotState = SENSOR;
	    correctR = true;
	}

	if(cm[RB] < 20 && cm[RB] != 0){
	   //routine for correcting if RB is close to wall
	   robotState = SENSOR; 
	   correctR = false;
	}

	else{
		robotState = FORWARD; 
	}
}

void correct(boolean x){

}

void loop() {
	pingAll();
	checkStop();
	checkSensors();
	switch(robotState){
		case ALIGN:
		 	alignWithWall(); //Firefight
		 	break;
		case FORWARD:
			driveStraight(); //Encoder
			break;
		case SENSOR:
			correct(correctR);
			break;
		case FLAME:
			if(checkFlameSensor())
                findFlame(); //Firefight
                break;
        case TURN:
           	turnRobot(turnRight); //Encoder
            break;
        case STOP:
            while(1);
            break;
        default:
            break;
       }
}


