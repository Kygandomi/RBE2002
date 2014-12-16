#include <Servo.h>
#include <Encoder.h>
#include <NewPing.h>

#define lFrontI 12 //left front 
#define lFrontO 13 
#define lBackI 28 //left back 
#define lBackO 29 
#define mFrontI 24//middle front
#define mFrontO 25
#define rBackI 26 //right back
#define rBackO 27
#define rFrontI 22//right front 
#define rFrontO 23 
#define flameSensor A1
#define startButton 37
#define cliffSensor A5

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 10
#define rightMPin 11
#define panPin 9 
#define tiltPin 8
#define gasPin 7
#define K 0.5

#define MIN_POWER 20

#define FAR_THRESH 30
#define FRONT_THRESH 13
#define NEAR_THRESH 10

#define ENCODER_TARGET 310

Servo leftM, rightM, pan, tilt, gas;
Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);

typedef enum State {
	FORWARD,
	TURN,
	REROUTE,
	EXPLORE,
	FLAME,
	PUT_OUT_FLAME,
	PAN_SENSOR,
	STOP,
	BACKUP
};
State nextState, robotState;

boolean trackingLeft;
boolean isOpening = false;
boolean isFirstDetect = false;
boolean isFirstOpen = true;

boolean isFlameFound = false;
boolean flameDetectedOnce = true;
boolean flameExists = false;
float heading;

float initDist;
float finalDist;
float endDist;
float initEncAverage; 
int encDiff;
int encDetect;
int turnTicks;
int accumError = 0;
int initBackUpEncAverage;

int highestReading; 
int highestEncAverage;
unsigned long initPanTime;
unsigned long initGasTime;
int flameStatus[3] = {0, 180, 180}; 

void startTurn();
void startTurnOpening();
void zeroEncoders();
void pingAll();
void collectIMUData();
void getInitDist();
void getFinalDist();
void setPrevPing();
void checkInitDist();
void setFlameServo();
int getEncAverage();
void drive(int, int);
void ServoSetup();
void goTo(State);

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000){
		pingAll();
		collectIMUData();
	}
}

void checkCliff(){
	if(analogRead(cliffSensor) > 800){
		initBackUpEncAverage = (leftEnc.read() + rightEnc.read())/2;
		goTo(BACKUP);
	}
}

void goTo(State s){
	robotState = s;
	switch(s){
		case FORWARD:
			setFlameServo();
			getInitDist();
			zeroEncoders();
			break;
		case TURN:
			zeroEncoders();
			break;
		case BACKUP:
			break;
		case PUT_OUT_FLAME:
			initGasTime = millis();
			break;		
		case REROUTE:
			break;
		case STOP:
			break;
		case PAN_SENSOR:
			initPanTime = millis();
			break;
		case EXPLORE:
			break;
		case FLAME:
			break;
	}
}

void then(State s){
	nextState = s;
}
