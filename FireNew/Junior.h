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
#define startButton 37

#define LB 0
#define LF 1
#define MF 2 // middle front sensor
#define RF 3
#define RB 4

#define leftMPin 10
#define rightMPin 11
#define panPin 8 
#define tiltPin 9
#define gasPin 7
#define K 0.5

#define MIN_POWER 20

#define FAR_THRESH 50
#define FRONT_THRESH 20
#define NEAR_THRESH 10

#define ENCODER_TARGET 315

Servo leftM, rightM, pan, tilt, gas;

Encoder rightEnc(2, A0);
Encoder leftEnc(18, 19);

typedef enum State {
	FORWARD_TIMED,
	FORWARD,
	TURN,
	FLAME
};

State robotState = FORWARD;

boolean trackingLeft;
float targetHeading, initHeading, expectedHeading;
float heading;

long inTime;
int turnTicks;

void startTurn(boolean turnLeft);
void zeroEncoders();
void pingAll();
void collectIMUData();

void ServoSetup(){
	leftM.attach(leftMPin);
	rightM.attach(rightMPin);
}

void drive(int x, int y){
	x = (x>100)?100:(x<-100)?-100:x;
	y = (y>100)?100:(y<-100)?-100:y;

	if(x>0 && x<MIN_POWER)
		x = MIN_POWER;
	if(x<0 && x>-MIN_POWER)
		x = -MIN_POWER;
	if(y<0 && y>-MIN_POWER)
		y = -MIN_POWER;
	if(y>0 && y<MIN_POWER)
		y = MIN_POWER;


	int a = map(x, -100, 100, 1000, 2000);
	int b = map(y, -100, 100, 2000, 1000);

	leftM.writeMicroseconds(a);
	rightM.writeMicroseconds(b);
}

void initialReadings(){
	long initTime = millis();
	while(millis() - initTime < 3000){
		pingAll();
		collectIMUData();
	}
}

void goTo(State s){
	switch(s){
		case FORWARD_TIMED:
			zeroEncoders();
			inTime = millis();
			robotState = FORWARD_TIMED;
			break;
		case FORWARD:
			zeroEncoders();
			robotState = FORWARD;
			break;
		case TURN:
			robotState = TURN;
			break;
		case FLAME:
			robotState = FLAME;
			break;
		default:
			break;
	}
}
