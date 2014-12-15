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

#define ENCODER_TARGET 315
#define FLAME_THRESH 900

Servo leftM, rightM, pan, tilt, gas;
Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);

typedef enum State {
	FORWARD,
	TURN,
	EXPLORE,
	FLAME,
	PUT_OUT_FLAME,
	PAN_SENSOR,
	STOP,
	BACKUP
};
State robotState;

float heading;
int leftCM, rightCM;

bool trackingLeft;
bool goFarther;
int initDist;
int turnTicks;

bool isFlameFound = false;
bool flameExists = false;
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
void setFlameServo();
int getEncAverage();
void drive(int, int);

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 2000){
		pingAll();
		collectIMUData();
	}
}

bool checkCliff(){
	return (analogRead(cliffSensor) > 800);
}

void goTo(State s){
	Serial.print("GOTO");
	robotState = s;
	switch(s){
		case FORWARD:
			getInitDist();
			zeroEncoders();
			Serial.println(" FORWARD");
			break;
		case EXPLORE:
			zeroEncoders();
			Serial.println(" EXPLORE");
			break;
		case TURN:
			zeroEncoders();
			Serial.println(" TURN");
			break;
		case BACKUP:
			zeroEncoders();
			Serial.println(" BACKUP");
			break;
		case FLAME:
			break;
	}
}