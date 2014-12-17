// FireFight.ino
/* Written by Katie Gandomi, Alexander O'Brien, Yu-sen Wu, Shao Zhou */
#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>
#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>
#include <TimerOne.h>
#include <LiquidCrystal.h>
#include <WS2812.h>

#include "Junior.h"
#include "Pinglib.h"
#include "Ping.h"
#include "IMUlib.h"
#include "IMU.h"
#include "Encoders.h"
#include "Flame.h"
#include "Servos.h"
#include "Navigation.h"
#include "Light.h"

void setup() {
	//indicate program running
	LED.setOutput(LEDPIN);
	setLed(GREEN);

	//set up everything
	IMUSetup();
	PingSetup();
	EncoderSetup();
	ServoSetup();
	VectorSetup();

	//take some sensor readings, figure out which wall to follow
	initialReadings();
	setDirection();
	setFlameServo();

	//go!
	setLed(PURPLE);
	goTo(FORWARD);
}

void loop() {
	collectIMUData(); //always collect imu data
	pingAll(); //always ping ultrasonic sensors
	updateLed(); //make LED's flash

	switch(robotState){
		case FORWARD:
			if(checkStop()){ //don't hit a wall!
				startTurn();
				goTo(TURN);
			}
			if(checkCliff()) //don't go over a cliff!
				goTo(BACKUP);
			
			if(getSideDist() < FAR_THRESH){ //nothing to explore
				isOpening = false;
				encDiff = 0;
				isFirstDetect = false;
			}
			
			if(!isOpening) //Check for new areas to explore
				checkForOpening();
			
			if(isOpening){ //New areas?
				if(getEncAvg() != initEncAverage && getSideDist() > FAR_THRESH){
					encDiff = getEncAvg() - initEncAverage;
					encDetect = (initDist > FAR_THRESH && isFirstDetect)? 800 : 300;
				}
				if(encDiff > encDetect){
					startTurnOpening();
					goTo(TURN);
				}
			}
			
			if(!driveStraight()){ //always drive straight
				startTurn();
				goTo(TURN);
			}
			if(checkFlameSensor()) //look for fire!
				goTo(FORWARD);
			break;

		case BACKUP:
			if(driveBackwards()){ //if done driving backwards, turn and continue
				startTurn();
				goTo(TURN);
			}
			break;

		case TURN:
			if(completeTurn()) //finish the turn
				goTo(FORWARD);
			break;

		case FLAME:
			if(findFlame()) //if fire, put it out!
				goTo(PUT_OUT_FLAME);
			break;

		case PUT_OUT_FLAME:
			if(putOutFlame()) //if it's out, finish
				goTo(STOP);
			break;

		case STOP:
			//print the candle's position
			lcd.print("X: "); lcd.print(xDis);
			lcd.print("Y: "); lcd.print(yDis);
			while(1); //exit
			break;

		case PAN_SENSOR:
			if(checkStopFindFlame()) //if there really is fire, locate it
				goTo(FLAME);
			else{ //else go back to previous activity
				startTurn();
				goTo(TURN);
			}
			break;
	}
}
